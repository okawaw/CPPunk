//
//  CPP_SDL_Sound.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/7/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SDL_Sound_h
#define CPP_SDL_Sound_h

#include "CPP_SoundIF.h"

#include <string>

class Mix_Chunk;

class CPP_SDL_Sound : public CPP_SoundIF
{
public:
	CPP_SDL_Sound(const std::string& filename);
	virtual ~CPP_SDL_Sound() = default;
	CPP_SDL_Sound(const CPP_SDL_Sound&) = default;
	CPP_SDL_Sound(CPP_SDL_Sound&&) = default;
	CPP_SDL_Sound& operator=(const CPP_SDL_Sound&) = default;
	CPP_SDL_Sound& operator=(CPP_SDL_Sound&&) = default;
	
	virtual std::unique_ptr<CPP_SoundChannelIF> play(double startTime=0.0, double pan=0.0, double volume=1.0) const override;
		
	virtual std::experimental::optional<double> getLength() const override;
	
private:
	std::unique_ptr<Mix_Chunk, void(*)(Mix_Chunk*)> chunk;
	
};

#endif /* CPP_SDL_Sound_h */
