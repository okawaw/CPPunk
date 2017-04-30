//
//  CPP_SDL_InputImpl.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 3/23/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SDL_InputImpl.h"

#include "CPP_Key.h"

#include <iostream>
#include <utility>

// TODO: Fix includes.
#include <SDL2/SDL.h>

CPP_Key translateKey(const SDL_Keycode key)
{
	CPP_Key ret;
	
	switch (key)
	{
		case SDLK_LEFT:
		{
			ret = CPP_Key::LEFT;
			break;
		}
		case SDLK_UP:
		{
			ret = CPP_Key::UP;
			break;
		}
		case SDLK_RIGHT:
		{
			ret = CPP_Key::RIGHT;
			break;
		}
		case SDLK_DOWN:
		{
			ret = CPP_Key::DOWN;
			break;
		}
		
		// TODO: SDLK_RETURN2?
		case SDLK_RETURN:
		{
			ret = CPP_Key::ENTER;
			break;
		}
		case SDLK_LGUI:
		case SDLK_RGUI:
		{
			ret = CPP_Key::COMMAND;
			break;
		}
		case SDLK_LCTRL:
		case SDLK_RCTRL:
		{
			ret = CPP_Key::CONTROL;
			break;
		}
		case SDLK_SPACE:
		// TODO: case SDLK_KP_SPACE:?
		{
			ret = CPP_Key::SPACE;
			break;
		}
		case SDLK_LSHIFT:
		case SDLK_RSHIFT:
		{
			ret = CPP_Key::SHIFT;
			break;
		}
		case SDLK_BACKSPACE:
		// TODO: case SDLK_KP_BACKSPACE:?
		{
			ret = CPP_Key::BACKSPACE;
			break;
		}
		case SDLK_CAPSLOCK:
		{
			ret = CPP_Key::CAPS_LOCK;
			break;
		}
		case SDLK_DELETE:
		{
			ret = CPP_Key::DELETE;
			break;
		}
		case SDLK_END:
		{
			ret = CPP_Key::END;
			break;
		}
		case SDLK_ESCAPE:
		{
			ret = CPP_Key::ESCAPE;
			break;
		}
		// TODO: SDLK_AC_HOME?
		case SDLK_HOME:
		{
			ret = CPP_Key::HOME;
			break;
		}
		case SDLK_INSERT:
		{
			ret = CPP_Key::INSERT;
			break;
		}
		case SDLK_TAB:
		// TODO: case SDLK_KP_TAB:?
		{
			ret = CPP_Key::TAB;
			break;
		}
		case SDLK_PAGEDOWN:
		{
			ret = CPP_Key::PAGE_DOWN;
			break;
		}
		case SDLK_PAGEUP:
		{
			ret = CPP_Key::PAGE_UP;
			break;
		}
		case SDLK_LEFTBRACKET:
		{
			ret = CPP_Key::LEFT_SQUARE_BRACKET;
			break;
		}
		case SDLK_RIGHTBRACKET:
		{
			ret = CPP_Key::RIGHT_SQUARE_BRACKET;
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
		case SDLK_g:
		{
			ret = CPP_Key::G;
			break;
		}
		case SDLK_h:
		{
			ret = CPP_Key::H;
			break;
		}
		case SDLK_i:
		{
			ret = CPP_Key::I;
			break;
		}
		case SDLK_j:
		{
			ret = CPP_Key::J;
			break;
		}
		case SDLK_k:
		{
			ret = CPP_Key::K;
			break;
		}
		case SDLK_l:
		{
			ret = CPP_Key::L;
			break;
		}
		case SDLK_m:
		{
			ret = CPP_Key::M;
			break;
		}
		case SDLK_n:
		{
			ret = CPP_Key::N;
			break;
		}
		case SDLK_o:
		{
			ret = CPP_Key::O;
			break;
		}
		case SDLK_p:
		{
			ret = CPP_Key::P;
			break;
		}
		case SDLK_q:
		{
			ret = CPP_Key::Q;
			break;
		}
		case SDLK_r:
		{
			ret = CPP_Key::R;
			break;
		}
		case SDLK_s:
		{
			ret = CPP_Key::S;
			break;
		}
		case SDLK_t:
		{
			ret = CPP_Key::T;
			break;
		}
		case SDLK_u:
		{
			ret = CPP_Key::U;
			break;
		}
		case SDLK_v:
		{
			ret = CPP_Key::V;
			break;
		}
		case SDLK_w:
		{
			ret = CPP_Key::W;
			break;
		}
		case SDLK_x:
		{
			ret = CPP_Key::X;
			break;
		}
		case SDLK_y:
		{
			ret = CPP_Key::Y;
			break;
		}
		case SDLK_z:
		{
			ret = CPP_Key::Z;
			break;
		}
		
		case SDLK_F1:
		{
			ret = CPP_Key::F1;
			break;
		}
		case SDLK_F2:
		{
			ret = CPP_Key::F2;
			break;
		}
		case SDLK_F3:
		{
			ret = CPP_Key::F3;
			break;
		}
		case SDLK_F4:
		{
			ret = CPP_Key::F4;
			break;
		}
		case SDLK_F5:
		{
			ret = CPP_Key::F5;
			break;
		}
		case SDLK_F6:
		{
			ret = CPP_Key::F6;
			break;
		}
		case SDLK_F7:
		{
			ret = CPP_Key::F7;
			break;
		}
		case SDLK_F8:
		{
			ret = CPP_Key::F8;
			break;
		}
		case SDLK_F9:
		{
			ret = CPP_Key::F9;
			break;
		}
		case SDLK_F10:
		{
			ret = CPP_Key::F10;
			break;
		}
		case SDLK_F11:
		{
			ret = CPP_Key::F11;
			break;
		}
		case SDLK_F12:
		{
			ret = CPP_Key::F12;
			break;
		}
		case SDLK_F13:
		{
			ret = CPP_Key::F13;
			break;
		}
		case SDLK_F14:
		{
			ret = CPP_Key::F14;
			break;
		}
		case SDLK_F15:
		{
			ret = CPP_Key::F15;
			break;
		}
		
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
		
		case SDLK_KP_0:
		{
			ret = CPP_Key::NUMPAD_0;
			break;
		}
		case SDLK_KP_1:
		{
			ret = CPP_Key::NUMPAD_1;
			break;
		}
		case SDLK_KP_2:
		{
			ret = CPP_Key::NUMPAD_2;
			break;
		}
		case SDLK_KP_3:
		{
			ret = CPP_Key::NUMPAD_3;
			break;
		}
		case SDLK_KP_4:
		{
			ret = CPP_Key::NUMPAD_4;
			break;
		}
		case SDLK_KP_5:
		{
			ret = CPP_Key::NUMPAD_5;
			break;
		}
		case SDLK_KP_6:
		{
			ret = CPP_Key::NUMPAD_6;
			break;
		}
		case SDLK_KP_7:
		{
			ret = CPP_Key::NUMPAD_7;
			break;
		}
		case SDLK_KP_8:
		{
			ret = CPP_Key::NUMPAD_8;
			break;
		}
		case SDLK_KP_9:
		{
			ret = CPP_Key::NUMPAD_9;
			break;
		}
		case SDLK_KP_PLUS:
		{
			ret = CPP_Key::NUMPAD_ADD;
			break;
		}
		case SDLK_KP_DECIMAL:
		{
			ret = CPP_Key::NUMPAD_DECIMAL;
			break;
		}
		case SDLK_KP_DIVIDE:
		{
			ret = CPP_Key::NUMPAD_DIVIDE;
			break;
		}
		case SDLK_KP_ENTER:
		{
			ret = CPP_Key::NUMPAD_ENTER;
			break;
		}
		case SDLK_KP_MULTIPLY:
		{
			ret = CPP_Key::NUMPAD_MULTIPLY;
			break;
		}
		case SDLK_KP_MINUS:
		{
			ret = CPP_Key::NUMPAD_SUBTRACT;
			break;
		}
		
		default:
		{
			std::cout << "Key is unsupported." << std::endl;
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
