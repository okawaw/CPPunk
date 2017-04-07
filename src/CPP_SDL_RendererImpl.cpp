//
//  CPP_SDL_RendererImpl.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/2/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_RendererImpl.h"

#include <utility>

// TODO: Fix includes.
#include <SDL2/SDL.h>

CPP_SDL_RendererImpl::CPP_SDL_RendererImpl(SDL_Renderer& renderer, std::function<void()> renderFunction) :
  renderer{renderer}
, renderFunction{std::move(renderFunction)}
{
}

void CPP_SDL_RendererImpl::render() const
{
	SDL_RenderClear(&renderer);
	
	if (renderFunction)
	{
		renderFunction();
	}
	
	SDL_RenderPresent(&renderer);
}
