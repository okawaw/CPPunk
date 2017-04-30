//
//  CPP_SDL_Music.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/7/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_Music.h"

#include "CPP_SDL_SoundManagerImpl.h"
#include "CPP_SoundChannelIF.h"

#include <iostream>

#include <SDL2_mixer/SDL_mixer.h>

CPP_SDL_Music::CPP_SDL_Music(const std::string& filename) :
  music{Mix_LoadMUS(filename.c_str()), Mix_FreeMusic}
{
	if (!music)
	{
		std::cerr << "Couldn't load \"" << filename << "\" into music." << std::endl;
	}
}

std::unique_ptr<CPP_SoundChannelIF> CPP_SDL_Music::play(const double startTime, const double pan, const double volume) const
{
	if (startTime != 0.0)
	{
		std::cerr << "Playing with a non-zero start time is unsupported for music." << std::endl;
	}
	
	if (pan != 0.0)
	{
		std::cerr << "Pan is unsupported for music." << std::endl;
	}
	
	if (music)
	{
		return CPP_SDL_SoundManagerImpl::playMusic(*music, volume);
	}
	else
	{
		std::cerr << "Music had nothing loaded." << std::endl;
		
		return nullptr;
	}
}

std::experimental::optional<double> CPP_SDL_Music::getLength() const
{
	return std::experimental::nullopt;
}
