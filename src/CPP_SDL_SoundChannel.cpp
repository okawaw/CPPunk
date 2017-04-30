//
//  CPP_SDL_SoundChannel.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/8/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_SoundChannel.h"

#include "CPP_SDL_SoundManagerImpl.h"

#include <utility>

#include <SDL2_mixer/SDL_mixer.h>

CPP_SDL_SoundChannel::CPP_SDL_SoundChannel(const unsigned int soundID, const int channel) :
  soundID{soundID}
, channel{channel}
{
}

void CPP_SDL_SoundChannel::registerOnComplete(std::function<void()> onCompleteFunction) const
{
	CPP_SDL_SoundManagerImpl::registerOnCompleteSound(soundID, std::move(onCompleteFunction));
}

void CPP_SDL_SoundChannel::unregisterOnComplete() const
{
	CPP_SDL_SoundManagerImpl::unregisterOnCompleteSound(soundID);
}

std::experimental::optional<double> CPP_SDL_SoundChannel::getPosition() const
{
	return std::experimental::nullopt;
}

void CPP_SDL_SoundChannel::stop() const
{
	CPP_SDL_SoundManagerImpl::stopSound(soundID, channel);
}

void CPP_SDL_SoundChannel::setVolume(const double value) const
{
	CPP_SDL_SoundManagerImpl::setSoundVolume(soundID, channel, value);
}

void CPP_SDL_SoundChannel::setPan(const double value) const
{
	CPP_SDL_SoundManagerImpl::setSoundPan(soundID, channel, value);
}
