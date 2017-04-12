//
//  CPP_SDL_Sound.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/7/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_Sound.h"

#include "CPP_SDL_SoundChannel.h"

#include <iostream>

#include <SDL2_mixer/SDL_mixer.h>

CPP_SDL_Sound::CPP_SDL_Sound(const std::string& filename) :
  chunk{Mix_LoadWAV(filename.c_str()), Mix_FreeChunk}
{
	// TODO: Throw an error if the file couldn't be loaded.
}

std::unique_ptr<CPP_SoundChannelIF> CPP_SDL_Sound::play(const double startTime, const double pan, const double volume) const
{
	// TODO: Don't do any of this directly in here. Call the CPP_SDL_SoundManagerImpl to do this. Returns a channel that contains the sound ID.
	const auto channel = Mix_PlayChannel(-1, chunk.get(), 0);
	
	if (channel == -1)
	{
		return nullptr;
	}
	
	Mix_Volume(channel, static_cast<int>(static_cast<double>(MIX_MAX_VOLUME) * volume));
	const auto left = static_cast<int>(127.0 * (1.0 - pan));
	Mix_SetPanning(channel, left, 254 - left);
	
	// TODO: Remove this.
	std::cout << "Sound playing on channel: " << channel << std::endl;
	return std::make_unique<CPP_SDL_SoundChannel>(channel);
}

std::experimental::optional<double> CPP_SDL_Sound::getLength() const
{
	return std::experimental::nullopt;
}
