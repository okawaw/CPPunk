//
//  CPP_SDL_SoundChannel.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/8/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SDL_SoundChannel_h
#define CPP_SDL_SoundChannel_h

#include "CPP_SoundChannelIF.h"

class CPP_SDL_SoundChannel : public CPP_SoundChannelIF
{
public:
	CPP_SDL_SoundChannel(unsigned int soundID, int channel);
	virtual ~CPP_SDL_SoundChannel() = default;
	CPP_SDL_SoundChannel(const CPP_SDL_SoundChannel&) = default;
	CPP_SDL_SoundChannel(CPP_SDL_SoundChannel&&) = default;
	CPP_SDL_SoundChannel& operator=(const CPP_SDL_SoundChannel&) = default;
	CPP_SDL_SoundChannel& operator=(CPP_SDL_SoundChannel&&) = default;
	
	virtual void registerOnComplete(std::function<void()> onCompleteFunction) const override;
	virtual void unregisterOnComplete() const override;
	
	virtual std::experimental::optional<double> getPosition() const override;
	
	virtual void stop() const override;
	
	virtual void setVolume(double value) const override;
	
	virtual void setPan(double value) const override;
	
private:
	unsigned int soundID;
	int channel;
};

#endif /* CPP_SDL_SoundChannel_h */
