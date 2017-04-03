//
//  CPP_SDL_Engine.cpp
//  Test
//
//  Created by Wade Okawa-Scannell on 11/20/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_Engine.h"

#include "CPP_SDL_BitmapDataFactory.h"
#include "CPP_SDL_Renderer.h"

#include <utility>

// TODO: Fix includes.
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

CPP_SDL_Engine::CPP_SDL_Engine(std::string title, const unsigned int width, const unsigned int height, const double frameRate, bool fixed) :
  CPP_Engine{std::move(title), width, height, frameRate, fixed}
, window{nullptr, SDL_DestroyWindow}
, renderer{nullptr, SDL_DestroyRenderer}
{
}

void CPP_SDL_Engine::init()
{
	CPP_Engine::init();
	
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	window.reset(SDL_CreateWindow(cpp.getTitle().c_str(), 0, 0, static_cast<int>(cpp.getWidth()), static_cast<int>(cpp.getHeight()), SDL_WINDOW_SHOWN));
	renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	
	CPP_Engine::renderer = std::make_unique<CPP_SDL_Renderer>(renderer.get());
	setBitmapDataFactory(std::make_unique<CPP_SDL_BitmapDataFactory>(renderer.get()));
}

void CPP_SDL_Engine::gameLoop()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			end();
		}
	}
	
	CPP_Engine::gameLoop();
}
