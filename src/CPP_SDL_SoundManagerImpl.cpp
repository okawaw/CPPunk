//
//  CPP_SDL_SoundManagerImpl.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/8/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_SoundManagerImpl.h"

#include <iostream>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>

#include <SDL2_mixer/SDL_mixer.h>


// TODO: Sunday:
//       Make queuing happen as integer values--basically, which channels completed.
//       Registering no longer needs a lock since accessing the callbacks will always happen on the main thread.
//       I need to figure out how to differentiate different instances of the same channel ID.
//       The problem is we don't know the channel ID until we start playing.
//
// Give each SDL sound an ID so we know each one even if they are different sounds on the same channel.

namespace
{
	struct StaticData
	{
		std::mutex lockSound;
		std::unordered_map<int, std::queue<std::function<void()> > > onCompleteFunctionMapSound;
		std::vector<int> completedSoundChannelsToQueue;
		std::vector<int> completedSoundChannelsToExecute;
		
		std::mutex lockMusic;
		std::queue<std::function<void()> > onCompleteFunctionQueueMusic;
		unsigned int numberOfMusicCompletesToQueue;
		unsigned int numberOfMusicCompletesToExecute;
	};

	std::unique_ptr<StaticData> staticData;
}

CPP_SDL_SoundManagerImpl::CPP_SDL_SoundManagerImpl()
{
	if (!staticData)
	{
		staticData.reset(new StaticData{});
		
		Mix_ChannelFinished([](const int channel)
		{
			std::lock_guard<std::mutex> lockGuard{staticData->lockSound};
			
			staticData->completedSoundChannelsToQueue.emplace_back(channel);
		});
		
		Mix_HookMusicFinished([]()
		{
			std::lock_guard<std::mutex> lockGuard{staticData->lockMusic};
			
			++staticData->numberOfMusicCompletesToQueue;
		});
	}
}

void CPP_SDL_SoundManagerImpl::processSound() const
{
	{
		std::lock_guard<std::mutex> lockGuard{staticData->lockSound};
		
		staticData->completedSoundChannelsToQueue.swap(staticData->completedSoundChannelsToExecute);
	}
	
	{
		std::lock_guard<std::mutex> lockGuard{staticData->lockMusic};
		
		staticData->numberOfMusicCompletesToExecute = staticData->numberOfMusicCompletesToQueue;
		staticData->numberOfMusicCompletesToQueue = 0u;
	}
	
	for (const auto& completedSoundChannel : staticData->completedSoundChannelsToExecute)
	{
		const auto onCompleteFunctionMapSoundIterator = staticData->onCompleteFunctionMapSound.find(completedSoundChannel);
		
		if (onCompleteFunctionMapSoundIterator != staticData->onCompleteFunctionMapSound.end())
		{
			auto& onCompleteFunctionMapSoundQueue = onCompleteFunctionMapSoundIterator->second;

			if (!onCompleteFunctionMapSoundQueue.empty())
			{
				const auto& onCompleteFunctionToExecute = onCompleteFunctionMapSoundQueue.front();
				
				if (onCompleteFunctionToExecute)
				{
					onCompleteFunctionToExecute();
				}
				
				onCompleteFunctionMapSoundQueue.pop();
				
				if (onCompleteFunctionMapSoundQueue.empty())
				{
					staticData->onCompleteFunctionMapSound.erase(onCompleteFunctionMapSoundIterator);
				}
			}
			else
			{
				std::cerr << "Channel " << completedSoundChannel << " completed but had no corresponding onComplete to execute." << std::endl;
			}
		}
		else
		{
			std::cerr << "Channel " << completedSoundChannel << " completed but had no corresponding onComplete to execute." << std::endl;
		}
	}
	
	staticData->completedSoundChannelsToExecute.clear();
	
	while (staticData->numberOfMusicCompletesToExecute)
	{
		if (!staticData->onCompleteFunctionQueueMusic.empty())
		{
			const auto& onCompleteFunctionToExecute = staticData->onCompleteFunctionQueueMusic.front();
			
			if (onCompleteFunctionToExecute)
			{
				onCompleteFunctionToExecute();
			}
			
			staticData->onCompleteFunctionQueueMusic.pop();
		}
		else
		{
			std::cerr << "Music completed but had no corresponding onComplete to execute." << std::endl;
		}
		
		--staticData->numberOfMusicCompletesToExecute;
	}
}

void CPP_SDL_SoundManagerImpl::registerOnCompleteSound(const int channel, std::function<void()> onCompleteFunction)
{
	staticData->onCompleteFunctionMapSound[channel].emplace(std::move(onCompleteFunction));
}

void CPP_SDL_SoundManagerImpl::unregisterOnCompleteSound(const int channel)
{
	const auto onCompleteFunctionMapSoundIterator = staticData->onCompleteFunctionMapSound.find(channel);
	
	if (onCompleteFunctionMapSoundIterator != staticData->onCompleteFunctionMapSound.end())
	{
		auto& onCompleteFunctionMapSoundQueue = onCompleteFunctionMapSoundIterator->second;
		
		if (!onCompleteFunctionMapSoundQueue.empty() && onCompleteFunctionMapSoundQueue.back())
		{
			onCompleteFunctionMapSoundQueue.back() = nullptr;
		}
		else
		{
			std::cerr << "Channel " << channel << " was unregistered but had no corresponding onComplete to clear." << std::endl;
		}
	}
	else
	{
		std::cerr << "Channel " << channel << " was unregistered but had no corresponding onComplete to clear." << std::endl;
	}
}

void CPP_SDL_SoundManagerImpl::registerOnCompleteMusic(std::function<void()> onCompleteFunction)
{
	staticData->onCompleteFunctionQueueMusic.emplace(std::move(onCompleteFunction));
}

void CPP_SDL_SoundManagerImpl::unregisterOnCompleteMusic()
{
	if (!staticData->onCompleteFunctionQueueMusic.empty() && staticData->onCompleteFunctionQueueMusic.back())
	{
		staticData->onCompleteFunctionQueueMusic.back() = nullptr;
	}
	else
	{
		std::cerr << "Music was unregistered but had no corresponding onComplete to clear." << std::endl;
	}
}
