//
//  CPP_SDL_Sound.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/7/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_Sound.h"

#include "CPP_SDL_SoundManagerImpl.h"
#include "CPP_SoundChannelIF.h"

#include <iostream>

#include <SDL2_mixer/SDL_mixer.h>

CPP_SDL_Sound::CPP_SDL_Sound(const std::string& filename) :
  chunk{Mix_LoadWAV(filename.c_str()), Mix_FreeChunk}
{
	if (!chunk)
	{
		std::cerr << "Couldn't load \"" << filename << "\" into sound." << std::endl;
	}
}

std::unique_ptr<CPP_SoundChannelIF> CPP_SDL_Sound::play(const double startTime, const double pan, const double volume) const
{
	if (startTime != 0.0)
	{
		std::cerr << "Playing with a non-zero start time is unsupported for sounds." << std::endl;
	}
	
	if (chunk)
	{
		return CPP_SDL_SoundManagerImpl::playSound(*chunk, volume, pan);
	}
	else
	{
		std::cerr << "Sound had nothing loaded." << std::endl;
		
		return nullptr;
	}
}

std::experimental::optional<double> CPP_SDL_Sound::getLength() const
{
	return std::experimental::nullopt;
}
