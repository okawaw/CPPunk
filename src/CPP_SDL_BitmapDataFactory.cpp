//
//  CPP_SDL_BitmapDataFactory.cpp
//  Test
//
//  Created by Wade Okawa-Scannell on 9/17/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_BitmapDataFactory.h"

#include "CPP_SDL_BitmapData.h"

#include <utility>

CPP_SDL_BitmapDataFactory::CPP_SDL_BitmapDataFactory(SDL_Renderer* const _renderer) :
  renderer{_renderer}
{
}

std::unique_ptr<CPP_BitmapDataIF> CPP_SDL_BitmapDataFactory::getBitmapData(const std::string& filename) const
{
	// TODO: Do I need "transparent" somewhere in here?
	return std::make_unique<CPP_SDL_BitmapData>(filename, renderer);
}

std::unique_ptr<CPP_BitmapDataIF> CPP_SDL_BitmapDataFactory::getBitmapData(const int width, const int height, const bool transparent, const unsigned int fillColor) const
{
	return std::make_unique<CPP_SDL_BitmapData>(width, height, renderer, transparent, fillColor);
}
