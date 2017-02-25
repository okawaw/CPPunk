//
//  CPP_SDL_BitmapDataFactory.h
//  Test
//
//  Created by Wade Okawa-Scannell on 9/17/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SDL_BitmapDataFactory_h
#define CPP_SDL_BitmapDataFactory_h

#include "CPP_BitmapDataFactoryIF.h"

class SDL_Renderer;

class CPP_SDL_BitmapDataFactory : public CPP_BitmapDataFactoryIF
{
public:
	CPP_SDL_BitmapDataFactory(SDL_Renderer* renderer=nullptr);
	
	virtual ~CPP_SDL_BitmapDataFactory() = default;
	CPP_SDL_BitmapDataFactory(const CPP_SDL_BitmapDataFactory&) = default;
	CPP_SDL_BitmapDataFactory(CPP_SDL_BitmapDataFactory&&) = default;
	CPP_SDL_BitmapDataFactory& operator=(const CPP_SDL_BitmapDataFactory&) = default;
	CPP_SDL_BitmapDataFactory& operator=(CPP_SDL_BitmapDataFactory&&) = default;
	
	virtual std::unique_ptr<CPP_BitmapDataIF> getBitmapData(const std::string& filename) const override;
	virtual std::unique_ptr<CPP_BitmapDataIF> getBitmapData(int width, int height, bool transparent=true, unsigned int fillColor=0xFFFFFFFFu) const override;
	
private:
	SDL_Renderer* const renderer;
};

#endif /* CPP_SDL_BitmapDataFactory_h */
