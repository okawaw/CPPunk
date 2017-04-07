//
//  CPP_SDL_InputImpl.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 3/23/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_InputImpl.h"

#include "CPP_Key.h"

#include <utility>

// TODO: Fix includes.
#include <SDL2/SDL.h>

CPP_Key translateKey(const SDL_Keycode key)
{
	CPP_Key ret;
	
	switch (key)
	{
		case SDLK_0:
		{
			ret = CPP_Key::DIGIT_0;
			break;
		}
		case SDLK_1:
		{
			ret = CPP_Key::DIGIT_1;
			break;
		}
		case SDLK_2:
		{
			ret = CPP_Key::DIGIT_2;
			break;
		}
		case SDLK_3:
		{
			ret = CPP_Key::DIGIT_3;
			break;
		}
		case SDLK_4:
		{
			ret = CPP_Key::DIGIT_4;
			break;
		}
		case SDLK_5:
		{
			ret = CPP_Key::DIGIT_5;
			break;
		}
		case SDLK_6:
		{
			ret = CPP_Key::DIGIT_6;
			break;
		}
		case SDLK_7:
		{
			ret = CPP_Key::DIGIT_7;
			break;
		}
		case SDLK_8:
		{
			ret = CPP_Key::DIGIT_8;
			break;
		}
		case SDLK_9:
		{
			ret = CPP_Key::DIGIT_9;
			break;
		}
		case SDLK_a:
		{
			ret = CPP_Key::A;
			break;
		}
		case SDLK_b:
		{
			ret = CPP_Key::B;
			break;
		}
		case SDLK_c:
		{
			ret = CPP_Key::C;
			break;
		}
		case SDLK_d:
		{
			ret = CPP_Key::D;
			break;
		}
		case SDLK_e:
		{
			ret = CPP_Key::E;
			break;
		}
		case SDLK_f:
		{
			ret = CPP_Key::F;
			break;
		}
		default:
		{
			ret = CPP_Key::ANY;
			break;
		}
	}
	
	return ret;
}

CPP_SDL_InputImpl::CPP_SDL_InputImpl()
{
}

void CPP_SDL_InputImpl::processInput() const
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
			{
				if (onQuitFunction)
				{
					onQuitFunction();
				}
				
				break;
			}
			case SDL_KEYDOWN:
			{
				if (onKeyDownFunction)
				{
					onKeyDownFunction(translateKey(e.key.keysym.sym));
				}
				
				break;
			}
			case SDL_KEYUP:
			{
				if (onKeyUpFunction)
				{
					onKeyUpFunction(translateKey(e.key.keysym.sym));
				}
				
				break;
			}
		}
	}
}

void CPP_SDL_InputImpl::registerOnKeyDown(std::function<void(CPP_Key key)> _onKeyDownFunction)
{
	onKeyDownFunction = std::move(_onKeyDownFunction);
}

void CPP_SDL_InputImpl::registerOnKeyUp(std::function<void(CPP_Key key)> _onKeyUpFunction)
{
	onKeyUpFunction = std::move(_onKeyUpFunction);
}

void CPP_SDL_InputImpl::registerOnQuit(std::function<void()> _onQuitFunction)
{
	onQuitFunction = std::move(_onQuitFunction);
}
