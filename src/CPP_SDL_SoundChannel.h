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
	CPP_SDL_SoundChannel(int channel);
	virtual ~CPP_SDL_SoundChannel() = default;
	CPP_SDL_SoundChannel(const CPP_SDL_SoundChannel&) = default;
	CPP_SDL_SoundChannel(CPP_SDL_SoundChannel&&) = default;
	CPP_SDL_SoundChannel& operator=(const CPP_SDL_SoundChannel&) = default;
	CPP_SDL_SoundChannel& operator=(CPP_SDL_SoundChannel&&) = default;
	
	virtual void registerOnComplete(std::function<void()> onCompleteFunction) const override;
	virtual void unregisterOnComplete() const override;
	
	virtual std::experimental::optional<double> getPosition() const override;
	
	virtual bool stop() const override;
	
	virtual void setVolume(double value) const override;
	
	virtual void setPan(double value) const override;
	
private:
	int channel;
	// TODO: Add a sound ID to this class that is assigned by the CPP_SDL_SoundManager.
};

#endif /* CPP_SDL_SoundChannel_h */
