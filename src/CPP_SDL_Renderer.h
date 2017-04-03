//
//  CPP_SDL_Renderer.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/2/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SDL_Renderer_h
#define CPP_SDL_Renderer_h

#include "CPP_RendererIF.h"

class SDL_Renderer;

class CPP_SDL_Renderer : public CPP_RendererIF
{
public:
	CPP_SDL_Renderer(SDL_Renderer* renderer=nullptr);
	virtual ~CPP_SDL_Renderer() = default;
		
	virtual void render(std::function<void()> renderFunction) const override;
	
private:
	SDL_Renderer* const renderer;
};

#endif /* CPP_SDL_Renderer_h */
