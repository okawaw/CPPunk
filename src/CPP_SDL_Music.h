//
//  CPP_SDL_Music.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/7/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SDL_Music_h
#define CPP_SDL_Music_h

#include "CPP_SoundIF.h"

#include <memory>
#include <string>

struct _Mix_Music;

class CPP_SDL_Music : public CPP_SoundIF
{
public:
	CPP_SDL_Music(const std::string& filename);
	virtual ~CPP_SDL_Music() = default;
	
	virtual std::unique_ptr<CPP_SoundChannelIF> play(double startTime=0.0, double pan=0.0, double volume=1.0) const override;
	
private:
	std::unique_ptr<_Mix_Music, void(*)(_Mix_Music*)> music;
	
};

#endif /* CPP_SDL_Music_h */
