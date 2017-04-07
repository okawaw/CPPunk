//
//  CPP_SDL_Input.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 3/22/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SDL_Input_h
#define CPP_SDL_Input_h

#include "CPP_InputImplIF.h"

class CPP_SDL_InputImpl : public CPP_InputImplIF
{
public:
	CPP_SDL_InputImpl();
	virtual ~CPP_SDL_InputImpl() = default;
	CPP_SDL_InputImpl(const CPP_SDL_InputImpl&) = default;
	CPP_SDL_InputImpl(CPP_SDL_InputImpl&&) = default;
	CPP_SDL_InputImpl& operator=(const CPP_SDL_InputImpl&) = default;
	CPP_SDL_InputImpl& operator=(CPP_SDL_InputImpl&&) = default;
	
	virtual void processInput() const override;
	
	virtual void registerOnKeyDown(std::function<void(CPP_Key key)> onKeyDownFunction) override;
	virtual void registerOnKeyUp(std::function<void(CPP_Key key)> onKeyUpFunction) override;
	
	void registerOnQuit(std::function<void()> onQuitFunction);

private:
	std::function<void(CPP_Key)> onKeyDownFunction;
	std::function<void(CPP_Key)> onKeyUpFunction;
	std::function<void()> onQuitFunction;
};

#endif /* CPP_SDL_Input_h */
