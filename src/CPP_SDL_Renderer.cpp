//
//  CPP_SDL_Renderer.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/2/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_Renderer.h"

// TODO: Fix includes.
#include <SDL2/SDL.h>

CPP_SDL_Renderer::CPP_SDL_Renderer(SDL_Renderer* const renderer) :
  renderer{renderer}
{
}

void CPP_SDL_Renderer::render(std::function<void()> renderFunction) const
{
	SDL_RenderClear(renderer);
	
	renderFunction();
	
	SDL_RenderPresent(renderer);
}
