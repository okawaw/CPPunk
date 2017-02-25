//
//  CPP_SDL_BitmapData.cpp
//  Test
//
//  Created by Wade Okawa-Scannell on 9/2/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_BitmapData.h"

#include "CPP_Point.h"

// TODO: Fix these includes.
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>

// TODO: Figure out how to deal with transparent property.

CPP_SDL_BitmapData::CPP_SDL_BitmapData(const std::string& filename, SDL_Renderer* const _renderer, const bool _transparent) :
  renderer{_renderer}
, transparent{_transparent}
, surface{IMG_Load(filename.c_str()), SDL_FreeSurface} // TODO: Fix this. Use transparent.
, texture{SDL_CreateTextureFromSurface(renderer, surface.get()), SDL_DestroyTexture}
{
	// TODO: Throw an error if the file couldn't be loaded.
}

// TODO: Finish this constructor version.
CPP_SDL_BitmapData::CPP_SDL_BitmapData(const int width, const int height, SDL_Renderer* const _renderer, const bool _transparent, const unsigned int fillColor) :
  renderer{_renderer}
, transparent{_transparent}
, surface{nullptr, SDL_FreeSurface}
, texture{nullptr, SDL_DestroyTexture}
{
}

int CPP_SDL_BitmapData::getHeight() const
{
	return surface->h;
}

int CPP_SDL_BitmapData::getWidth() const
{
	return surface->w;
}

CPP_Rectangle CPP_SDL_BitmapData::getRect() const
{
	return {0.0, 0.0, static_cast<double>(getWidth()), static_cast<double>(getHeight())};
}

bool CPP_SDL_BitmapData::isTransparent() const
{
	return transparent;
}

void CPP_SDL_BitmapData::render(const CPP_Point& destPoint, const std::experimental::optional<CPP_Rectangle>& clipRect) const
{
	SDL_Rect srcRect;
	
	if (clipRect)
	{
		srcRect.x = static_cast<int>(clipRect->x);
		srcRect.y = static_cast<int>(clipRect->y);
		srcRect.w = static_cast<int>(clipRect->width);
		srcRect.h = static_cast<int>(clipRect->height);
	}
	else
	{
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = getWidth();
		srcRect.h = getHeight();
	}
	
	SDL_Rect destRect;
	destRect.x = static_cast<int>(destPoint.x);
	destRect.y = static_cast<int>(destPoint.y);
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	
	SDL_RenderCopy(renderer, texture.get(), &srcRect, &destRect);
}

void CPP_SDL_BitmapData::lock()
{
}

void CPP_SDL_BitmapData::unlock()
{
}

