//
//  CPP_SDL_MusicChannel.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/8/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SDL_MusicChannel_h
#define CPP_SDL_MusicChannel_h

#include "CPP_SoundChannelIF.h"

class CPP_SDL_MusicChannel : public CPP_SoundChannelIF
{
public:
	CPP_SDL_MusicChannel() = default;
	virtual ~CPP_SDL_MusicChannel() = default;
	
	virtual void stop() const;
	
};

#endif /* CPP_SDL_MusicChannel_h */
