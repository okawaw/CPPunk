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
		std::mutex lock;
		std::unordered_map<int, std::queue<std::function<void()> > > onCompleteFunctionMap;
		std::vector<int> completedChannelsToQueue;
		std::vector<int> completedChannelsToExecute;
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
			std::lock_guard<std::mutex> l(staticData->lock);
			
			staticData->completedChannelsToQueue.emplace_back(channel);
		});
	}
}

void CPP_SDL_SoundManagerImpl::processSound() const
{
	{
		std::lock_guard<std::mutex> l(staticData->lock);
		
		staticData->completedChannelsToQueue.swap(staticData->completedChannelsToExecute);
	}
	
	for (const auto& completedChannel : staticData->completedChannelsToExecute)
	{
		const auto onCompleteFunctionMapIterator = staticData->onCompleteFunctionMap.find(completedChannel);
		
		if (onCompleteFunctionMapIterator != staticData->onCompleteFunctionMap.end() && !onCompleteFunctionMapIterator->second.empty())
		{
			auto& onCompleteFunctionMapQueue = onCompleteFunctionMapIterator->second;

			if (!onCompleteFunctionMapQueue.empty())
			{
				const auto& onCompleteFunctionToExecute = onCompleteFunctionMapQueue.front();
				
				if (onCompleteFunctionToExecute)
				{
					onCompleteFunctionToExecute();
				}
				
				onCompleteFunctionMapQueue.pop();
				
				if (onCompleteFunctionMapQueue.empty())
				{
					staticData->onCompleteFunctionMap.erase(onCompleteFunctionMapIterator);
				}
			}
		}
		else // TODO: Remove this.
		{
			std::cerr << "Channel " << completedChannel << " completed but had no corresponding onComplete to execute." << std::endl;
		}
	}
	
	staticData->completedChannelsToExecute.clear();
}

void CPP_SDL_SoundManagerImpl::registerOnComplete(const int channel, std::function<void()> onCompleteFunction)
{
	staticData->onCompleteFunctionMap[channel].emplace(std::move(onCompleteFunction));
}

void CPP_SDL_SoundManagerImpl::unregisterOnComplete(const int channel)
{
	const auto onCompleteFunctionMapIterator = staticData->onCompleteFunctionMap.find(channel);
	
	if (onCompleteFunctionMapIterator != staticData->onCompleteFunctionMap.end())
	{
		auto& onCompleteFunctionMapQueue = onCompleteFunctionMapIterator->second;
		
		if (!onCompleteFunctionMapQueue.empty())
		{
			onCompleteFunctionMapQueue.back() = nullptr;
		}
	}
	else // TODO: Remove this.
	{
		std::cerr << "Channel " << channel << " was unregistered but had no corresponding onComplete to clear." << std::endl;
	}
}
