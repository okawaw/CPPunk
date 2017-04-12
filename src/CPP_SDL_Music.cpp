//
//  CPP_SDL_Music.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/7/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_Music.h"

#include "CPP_SDL_MusicChannel.h"

#include <iostream>

#include <SDL2_mixer/SDL_mixer.h>

CPP_SDL_Music::CPP_SDL_Music(const std::string& filename) :
  music{Mix_LoadMUS(filename.c_str()), Mix_FreeMusic}
{
	// TODO: Throw an error if the file couldn't be loaded.
}

std::unique_ptr<CPP_SoundChannelIF> CPP_SDL_Music::play(const double startTime, const double pan, const double volume) const
{
	// TODO: Don't do any of this directly in here. Call the CPP_SDL_SoundManagerImpl to do this. Returns a channel that contains the sound ID.
	const auto success = Mix_PlayMusic(music.get(), 0);
	
	if (success == -1)
	{
		return nullptr;
	}
	
	Mix_VolumeMusic(static_cast<int>((static_cast<double>(MIX_MAX_VOLUME) / 2.0) * volume));
	
	// TODO: Remove this.
	std::cout << "Music playing." << std::endl;
	return std::make_unique<CPP_SDL_MusicChannel>();
}

std::experimental::optional<double> CPP_SDL_Music::getLength() const
{
	return std::experimental::nullopt;
}
