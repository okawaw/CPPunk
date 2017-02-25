//
//  CPP_SDL_Engine.h
//  Test
//
//  Created by Wade Okawa-Scannell on 9/18/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SDL_Engine_h
#define CPP_SDL_Engine_h

#include "CPP_Engine.h"

#include <memory>
#include <string>

class SDL_Renderer;
class SDL_Window;

class CPP_SDL_Engine : public CPP_Engine
{
public:
	CPP_SDL_Engine(std::string name, unsigned int width, unsigned int height, double frameRate=60.0, bool fixed=false);
	virtual ~CPP_SDL_Engine() = default;
	// TODO: Other constructors?
	
	virtual void init() override;
	
	virtual void gameLoop() override;
	
protected:
	std::string name;
	std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
	std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;
};

#endif /* CPP_SDL_Engine_h */
