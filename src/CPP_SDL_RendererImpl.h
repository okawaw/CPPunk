//
//  CPP_SDL_RendererImpl.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/2/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SDL_RendererImpl_h
#define CPP_SDL_RendererImpl_h

#include "CPP_RendererImplIF.h"

#include <functional>

class SDL_Renderer;

class CPP_SDL_RendererImpl : public CPP_RendererImplIF
{
public:
	CPP_SDL_RendererImpl(SDL_Renderer& renderer, std::function<void()> renderFunction);
	virtual ~CPP_SDL_RendererImpl() = default;
	CPP_SDL_RendererImpl(const CPP_SDL_RendererImpl&) = default;
	CPP_SDL_RendererImpl(CPP_SDL_RendererImpl&&) = default;
	CPP_SDL_RendererImpl& operator=(const CPP_SDL_RendererImpl&) = default;
	CPP_SDL_RendererImpl& operator=(CPP_SDL_RendererImpl&&) = default;
	
	virtual void render() const override;
	
private:
	SDL_Renderer& renderer;
	std::function<void()> renderFunction;
};

#endif /* CPP_SDL_RendererImpl_h */
