//
//  CPP_SDL_MusicChannel.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/8/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_MusicChannel.h"

#include "CPP_SDL_SoundManagerImpl.h"

#include <SDL2_mixer/SDL_mixer.h>

void CPP_SDL_MusicChannel::registerOnComplete(std::function<void()> onCompleteFunction) const
{
	CPP_SDL_SoundManagerImpl::registerOnCompleteMusic(std::move(onCompleteFunction));
}

void CPP_SDL_MusicChannel::unregisterOnComplete() const
{
	CPP_SDL_SoundManagerImpl::unregisterOnCompleteMusic();
}

std::experimental::optional<double> CPP_SDL_MusicChannel::getPosition() const
{
	return std::experimental::nullopt;
}

bool CPP_SDL_MusicChannel::stop() const
{
	// TODO: Call a function to CPP_SDL_SoundManagerImpl to do this.
	Mix_HaltMusic();
	
	// TODO: Don't always return true. Return false if the sound was not playing.
	return true;
}

void CPP_SDL_MusicChannel::setVolume(double value) const
{
	// TODO: Call a function to CPP_SDL_SoundManagerImpl to do this.
	Mix_VolumeMusic(static_cast<int>((static_cast<double>(MIX_MAX_VOLUME) / 2.0) * value));
}

void CPP_SDL_MusicChannel::setPan(double value) const
{
	// TODO: Unavailable?
}
