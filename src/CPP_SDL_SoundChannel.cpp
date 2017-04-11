//
//  CPP_SDL_SoundChannel.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/8/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_SoundChannel.h"

#include "CPP_SDL_SoundManagerImpl.h"

#include <SDL2_mixer/SDL_mixer.h>

CPP_SDL_SoundChannel::CPP_SDL_SoundChannel(const int channel) :
  channel{channel}
{
}

void CPP_SDL_SoundChannel::registerOnComplete(std::function<void()> onCompleteFunction) const
{
	CPP_SDL_SoundManagerImpl::registerOnComplete(channel, std::move(onCompleteFunction));
}

void CPP_SDL_SoundChannel::unregisterOnComplete() const
{
	CPP_SDL_SoundManagerImpl::unregisterOnComplete(channel);
}

std::experimental::optional<double> CPP_SDL_SoundChannel::getPosition() const
{
	return std::experimental::nullopt;
}

bool CPP_SDL_SoundChannel::stop() const
{
	// TODO: Call a function to CPP_SDL_SoundManagerImpl to do this.
	Mix_HaltChannel(channel);
	
	// TODO: Don't always return true. Return false if the sound was not playing.
	return true;
}

void CPP_SDL_SoundChannel::setVolume(const double value) const
{
	// TODO: Call a function to CPP_SDL_SoundManagerImpl to do this.
	Mix_Volume(channel, static_cast<int>(MIX_MAX_VOLUME * value));
}

void CPP_SDL_SoundChannel::setPan(const double value) const
{
	// TODO: Call a function to CPP_SDL_SoundManagerImpl to do this.
	const auto left = static_cast<int>(127.0 * (1.0 - value));
	Mix_SetPanning(channel, left, 254 - left);
}
