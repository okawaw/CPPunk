//
//  CPP_SDL_Music.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/7/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//
/*
#include "CPP_SDL_Music.h"

#include "CPP_SDL_MusicChannel.h"

#include <SDL2_mixer/SDL_mixer.h>

CPP_SDL_Music::CPP_SDL_Music(const std::string& filename) :
  music{Mix_LoadMUS(filename.c_str()), Mix_FreeMusic}
{
}
#include <iostream>
#include <thread>
std::unique_ptr<CPP_SoundChannelIF> CPP_SDL_Music::play() const
{
//	std::cout << "Main thread: " << std::this_thread::get_id() << std::endl;
	Mix_PlayMusic(music.get(), 0);
	return std::make_unique<CPP_SDL_MusicChannel>();
//	Mix_ChannelFinished([](int channel)
//						{
//							std::cout << "Callback thread: " << std::this_thread::get_id() << std::endl;
//							std::cout << channel << std::endl;
//						});
}
*/
