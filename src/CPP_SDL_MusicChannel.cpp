//
//  CPP_SDL_MusicChannel.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/8/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_MusicChannel.h"

#include "CPP_SDL_SoundManagerImpl.h"

#include <iostream>
#include <utility>

#include <SDL2_mixer/SDL_mixer.h>

CPP_SDL_MusicChannel::CPP_SDL_MusicChannel(const unsigned int musicID) :
  musicID{musicID}
{
}

void CPP_SDL_MusicChannel::registerOnComplete(std::function<void()> onCompleteFunction) const
{
	CPP_SDL_SoundManagerImpl::registerOnCompleteMusic(musicID, std::move(onCompleteFunction));
}

void CPP_SDL_MusicChannel::unregisterOnComplete() const
{
	CPP_SDL_SoundManagerImpl::unregisterOnCompleteMusic(musicID);
}

std::experimental::optional<double> CPP_SDL_MusicChannel::getPosition() const
{
	return std::experimental::nullopt;
}

void CPP_SDL_MusicChannel::stop() const
{
	CPP_SDL_SoundManagerImpl::stopMusic(musicID);
}

void CPP_SDL_MusicChannel::setVolume(const double value) const
{
	CPP_SDL_SoundManagerImpl::setMusicVolume(musicID, value);
}

void CPP_SDL_MusicChannel::setPan(const double value) const
{
	std::cerr << "Pan is unsupported for music." << std::endl;
}
