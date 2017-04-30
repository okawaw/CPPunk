//
//  CPP_SDL_SoundManagerImpl.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/8/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_SoundManagerImpl.h"

#include "CPP_SDL_MusicChannel.h"
#include "CPP_SDL_SoundChannel.h"

#include <iostream>
#include <mutex>
#include <experimental/optional>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <SDL2_mixer/SDL_mixer.h>

namespace
{
	struct StaticData
	{
		StaticData(const unsigned int channels) :
		  channels{channels}
		, nextSoundID{0u}
		, nextMusicID{0u}
		{
			for (auto i = 0u; i < channels; ++i)
			{
				availableChannels.push(static_cast<int>(i));
			}
		}
		
		// Sound data.
		const unsigned int channels;
		std::stack<int> availableChannels;
		std::unordered_map<int, unsigned int> channelLookup;
		
		std::mutex soundMutex;
		
		unsigned int nextSoundID;
		std::unordered_set<unsigned int> soundsPlaying;
		
		std::unordered_map<unsigned int, std::function<void()> > onCompleteSoundFunctions;
		std::unordered_set<unsigned int> completedSoundsToQueue;
		std::unordered_set<unsigned int> completedSoundsToExecute;
		
		// Music data.
		std::mutex musicMutex;
		
		unsigned int nextMusicID;
		std::experimental::optional<unsigned int> musicPlaying;
		
		std::unordered_map<unsigned int, std::function<void()> > onCompleteMusicFunctions;
		std::unordered_set<unsigned int> completedMusicToQueue;
		std::unordered_set<unsigned int> completedMusicToExecute;
	};

	std::unique_ptr<StaticData> staticData;
	
	void setSoundVolume(const int channel, const double value)
	{
		Mix_Volume(channel, static_cast<int>(static_cast<double>(MIX_MAX_VOLUME) * value));
	}
	
	void setSoundPan(const int channel, const double value)
	{
		const auto left = static_cast<int>(127.0 * (1.0 - value));
		Mix_SetPanning(channel, left, 254 - left);
	}
	
	void setMusicVolume(const double value)
	{
		Mix_VolumeMusic(static_cast<int>((static_cast<double>(MIX_MAX_VOLUME) / 2.0) * value));
	}
}

CPP_SDL_SoundManagerImpl::CPP_SDL_SoundManagerImpl(const unsigned int channels)
{
	if (!staticData)
	{
		staticData.reset(new StaticData{channels});
		
		Mix_ChannelFinished([](const int channel)
		{
			std::lock_guard<std::mutex> lockGuard{staticData->soundMutex};
			
			const auto channelLookupIterator = staticData->channelLookup.find(channel);
			
			if (channelLookupIterator != staticData->channelLookup.end())
			{
				const auto& soundID = channelLookupIterator->second;
				
				staticData->completedSoundsToQueue.emplace(soundID);
				
				staticData->soundsPlaying.erase(soundID);
				
				staticData->channelLookup.erase(channelLookupIterator);
			}
			else
			{
				std::cerr << "No sound ID found for completed channel " << channel << "." << std::endl;
			}
			
			staticData->availableChannels.push(channel);
		});
		
		Mix_HookMusicFinished([]()
		{
			std::lock_guard<std::mutex> lockGuard{staticData->musicMutex};
			
			if (staticData->musicPlaying)
			{
				staticData->completedMusicToQueue.emplace(*staticData->musicPlaying);
				
				staticData->musicPlaying = std::experimental::nullopt;
			}
			else
			{
				std::cerr << "No music ID found for completed music." << std::endl;
			}
		});
	}
}

void CPP_SDL_SoundManagerImpl::processSound() const
{
	{
		std::lock_guard<std::mutex> lockGuard{staticData->soundMutex};
		
		staticData->completedSoundsToQueue.swap(staticData->completedSoundsToExecute);
	}
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->musicMutex};
		
		staticData->completedMusicToQueue.swap(staticData->completedMusicToExecute);
	}
	
	for (const auto& completedSoundID : staticData->completedSoundsToExecute)
	{
		const auto onCompleteSoundFunctionsIterator = staticData->onCompleteSoundFunctions.find(completedSoundID);
		
		if (onCompleteSoundFunctionsIterator != staticData->onCompleteSoundFunctions.end())
		{
			const auto& onCompleteSoundFunction = onCompleteSoundFunctionsIterator->second;
			
			if (onCompleteSoundFunction)
			{
				onCompleteSoundFunction();
			}
			
			staticData->onCompleteSoundFunctions.erase(onCompleteSoundFunctionsIterator);
		}
	}
	
	staticData->completedSoundsToExecute.clear();
	
	for (const auto& completedMusicID : staticData->completedMusicToExecute)
	{
		const auto onCompleteMusicFunctionsIterator = staticData->onCompleteMusicFunctions.find(completedMusicID);
		
		if (onCompleteMusicFunctionsIterator != staticData->onCompleteMusicFunctions.end())
		{
			const auto& onCompleteMusicFunction = onCompleteMusicFunctionsIterator->second;
			
			if (onCompleteMusicFunction)
			{
				onCompleteMusicFunction();
			}
			
			staticData->onCompleteMusicFunctions.erase(onCompleteMusicFunctionsIterator);
		}
	}
	
	staticData->completedMusicToExecute.clear();
}

std::unique_ptr<CPP_SoundChannelIF> CPP_SDL_SoundManagerImpl::playSound(Mix_Chunk& chunk, const double volume, const double pan)
{	
	std::experimental::optional<unsigned int> soundID;
	std::experimental::optional<int> channel;
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->soundMutex};
		
		if (!staticData->availableChannels.empty())
		{
			for (auto i = 0u; !soundID && i < (staticData->soundsPlaying.size() + staticData->completedSoundsToQueue.size() + staticData->completedSoundsToExecute.size() + 1u); ++i, ++staticData->nextSoundID)
			{
				const auto unused = staticData->completedSoundsToQueue.find(staticData->nextSoundID) == staticData->completedSoundsToQueue.end() && staticData->completedSoundsToExecute.find(staticData->nextSoundID) == staticData->completedSoundsToExecute.end();
				
				if (unused)
				{
					const auto emplaceResults = staticData->soundsPlaying.emplace(staticData->nextSoundID);
					
					const auto& emplaceSuccess = emplaceResults.second;
					if (emplaceSuccess)
					{
						soundID.emplace(staticData->nextSoundID);
					}
				}
			}
			
			if (soundID)
			{
				channel.emplace(staticData->availableChannels.top());
				staticData->availableChannels.pop();
				
				staticData->channelLookup[*channel] = *soundID;
			}
		}
	}

	bool success = false;
	
	if (channel)
	{
		::setSoundVolume(*channel, volume);

		::setSoundPan(*channel, pan);
		
		const auto playResult = Mix_PlayChannel(*channel, &chunk, 0);
		
		if (playResult == *channel)
		{
			success = true;
		}
		else
		{
			std::cerr << "Couldn't play sound on channel " << *channel << "." << std::endl;
			
			{
				std::lock_guard<std::mutex> lockGuard{staticData->soundMutex};
				
				staticData->soundsPlaying.erase(*soundID);
				
				staticData->availableChannels.push(*channel);
				
				staticData->channelLookup.erase(*channel);
			}
		}
	}
	else
	{
		std::cerr << "No available channels to play sound on." << std::endl;
	}
	
	if (success)
	{
		return std::make_unique<CPP_SDL_SoundChannel>(*soundID, *channel);
	}
	else
	{
		return nullptr;
	}
}

void CPP_SDL_SoundManagerImpl::setSoundVolume(const unsigned int soundID, const int channel, const double value)
{
	auto playing = false;
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->soundMutex};
		
		if (staticData->soundsPlaying.find(soundID) != staticData->soundsPlaying.end())
		{
			playing = true;
		}
	}
	
	if (playing)
	{
		::setSoundVolume(channel, value);
	}
}

void CPP_SDL_SoundManagerImpl::setSoundPan(const unsigned int soundID, const int channel, const double value)
{
	auto playing = false;
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->soundMutex};
		
		if (staticData->soundsPlaying.find(soundID) != staticData->soundsPlaying.end())
		{
			playing = true;
		}
	}
	
	if (playing)
	{
		::setSoundPan(channel, value);
	}
}

void CPP_SDL_SoundManagerImpl::stopSound(const unsigned int soundID, const int channel)
{
	auto playing = false;
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->soundMutex};

		if (staticData->soundsPlaying.find(soundID) != staticData->soundsPlaying.end())
		{
			playing = true;
		}
	}
	
	if (playing)
	{
		Mix_HaltChannel(channel);
	}
}

void CPP_SDL_SoundManagerImpl::registerOnCompleteSound(const unsigned int soundID, std::function<void()> onCompleteFunction)
{
	if (staticData->completedSoundsToExecute.find(soundID) != staticData->completedSoundsToExecute.end())
	{
		// This sound's callback is already queued to execute.
		return;
	}
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->soundMutex};
		
		if (staticData->soundsPlaying.find(soundID) == staticData->soundsPlaying.end() &&
			staticData->completedSoundsToQueue.find(soundID) == staticData->completedSoundsToQueue.end())
		{
			// This sound is not currently playing.
			return;
		}
	}

	staticData->onCompleteSoundFunctions[soundID] = std::move(onCompleteFunction);
}

void CPP_SDL_SoundManagerImpl::unregisterOnCompleteSound(const unsigned int soundID)
{
	if (staticData->completedSoundsToExecute.find(soundID) != staticData->completedSoundsToExecute.end())
	{
		// This sound's callback is already queued to execute.
		return;
	}
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->soundMutex};
		
		if (staticData->soundsPlaying.find(soundID) == staticData->soundsPlaying.end() &&
			staticData->completedSoundsToQueue.find(soundID) == staticData->completedSoundsToQueue.end())
		{
			// This sound is not currently playing.
			return;
		}
	}
	
	const auto onCompleteSoundFunctionsIterator = staticData->onCompleteSoundFunctions.find(soundID);
	
	if (onCompleteSoundFunctionsIterator != staticData->onCompleteSoundFunctions.end())
	{
		staticData->onCompleteSoundFunctions.erase(onCompleteSoundFunctionsIterator);
	}
	else
	{
		std::cerr << "Sound " << soundID << " was unregistered but had no corresponding onComplete to clear." << std::endl;
	}
}

std::unique_ptr<CPP_SoundChannelIF> CPP_SDL_SoundManagerImpl::playMusic(_Mix_Music& music, const double volume)
{	
	std::experimental::optional<unsigned int> musicID;
	bool availableChannel = false;
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->musicMutex};
		
		if (!staticData->musicPlaying)
		{
			for (auto i = 0u; !musicID && i < (staticData->completedMusicToQueue.size() + staticData->completedMusicToExecute.size() + 1u); ++i, ++staticData->nextMusicID)
			{
				const auto unused = staticData->completedMusicToQueue.find(staticData->nextMusicID) == staticData->completedMusicToQueue.end() && staticData->completedMusicToExecute.find(staticData->nextMusicID) == staticData->completedMusicToExecute.end();
				
				if (unused)
				{
					staticData->musicPlaying.emplace(staticData->nextMusicID);

					musicID.emplace(staticData->nextMusicID);
				}
			}
			
			if (musicID)
			{
				availableChannel = true;
			}
		}
	}
	
	bool success = false;
	
	if (availableChannel)
	{
		::setMusicVolume(volume);
		
		const auto playResult = Mix_PlayMusic(&music, 0);

		if (!playResult)
		{
			success = true;
		}
		else
		{
			std::cerr << "Couldn't play music." << std::endl;
			
			{
				std::lock_guard<std::mutex> lockGuard{staticData->musicMutex};
				
				staticData->musicPlaying = std::experimental::nullopt;
			}
		}
	}
	else
	{
		std::cerr << "No available channels to play music on." << std::endl;
	}
	
	if (success)
	{
		return std::make_unique<CPP_SDL_MusicChannel>(*musicID);
	}
	else
	{
		return nullptr;
	}
}

void CPP_SDL_SoundManagerImpl::setMusicVolume(const unsigned int musicID, const double value)
{
	auto playing = false;
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->musicMutex};
		
		if (staticData->musicPlaying && *staticData->musicPlaying == musicID)
		{
			playing = true;
		}
	}
	
	if (playing)
	{
		::setMusicVolume(value);
	}
}

void CPP_SDL_SoundManagerImpl::stopMusic(const unsigned int musicID)
{
	auto playing = false;
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->musicMutex};
		
		if (staticData->musicPlaying && *staticData->musicPlaying == musicID)
		{
			playing = true;
		}
	}

	if (playing)
	{
		Mix_HaltMusic();
	}
}

void CPP_SDL_SoundManagerImpl::registerOnCompleteMusic(const unsigned int musicID, std::function<void()> onCompleteFunction)
{
	if (staticData->completedMusicToExecute.find(musicID) != staticData->completedMusicToExecute.end())
	{
		// This music's callback is already queued to execute.
		return;
	}
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->musicMutex};
		
		if (!(staticData->musicPlaying && *staticData->musicPlaying == musicID) &&
			staticData->completedMusicToQueue.find(musicID) == staticData->completedMusicToQueue.end())
		{
			// This music is not currently playing.
			return;
		}
	}
	
	staticData->onCompleteMusicFunctions[musicID] = std::move(onCompleteFunction);
}

void CPP_SDL_SoundManagerImpl::unregisterOnCompleteMusic(const unsigned int musicID)
{
	if (staticData->completedMusicToExecute.find(musicID) != staticData->completedMusicToExecute.end())
	{
		// This music's callback is already queued to execute.
		return;
	}
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->musicMutex};
		
		if (!(staticData->musicPlaying && *staticData->musicPlaying == musicID) &&
			staticData->completedMusicToQueue.find(musicID) == staticData->completedMusicToQueue.end())
		{
			// This music is not currently playing.
			return;
		}
	}
	
	const auto onCompleteMusicFunctionsIterator = staticData->onCompleteMusicFunctions.find(musicID);
	
	if (onCompleteMusicFunctionsIterator != staticData->onCompleteMusicFunctions.end())
	{
		staticData->onCompleteMusicFunctions.erase(onCompleteMusicFunctionsIterator);
	}
	else
	{
		std::cerr << "Music " << musicID << " was unregistered but had no corresponding onComplete to clear." << std::endl;
	}
}
