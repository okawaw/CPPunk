//
//  CPP_SDL_SoundManagerImpl.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/8/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SDL_SoundManagerImpl_h
#define CPP_SDL_SoundManagerImpl_h

#include "CPP_SoundManagerImplIF.h"

#include <functional>

class CPP_SDL_SoundChannel;

class CPP_SDL_SoundManagerImpl : public CPP_SoundManagerImplIF
{
	friend CPP_SDL_SoundChannel;
public:
	CPP_SDL_SoundManagerImpl();
	virtual ~CPP_SDL_SoundManagerImpl() = default;
	CPP_SDL_SoundManagerImpl(const CPP_SDL_SoundManagerImpl&) = default;
	CPP_SDL_SoundManagerImpl(CPP_SDL_SoundManagerImpl&&) = default;
	CPP_SDL_SoundManagerImpl& operator=(const CPP_SDL_SoundManagerImpl&) = default;
	CPP_SDL_SoundManagerImpl& operator=(CPP_SDL_SoundManagerImpl&&) = default;
	
	virtual void processSound() const override;
	
private:	
	static void registerOnComplete(int channel, std::function<void()> onCompleteFunction);
	static void unregisterOnComplete(int channel);
	
};

#endif /* CPP_SDL_SoundManagerImpl_h */
