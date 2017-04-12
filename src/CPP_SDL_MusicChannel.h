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
	CPP_SDL_MusicChannel(const CPP_SDL_MusicChannel&) = default;
	CPP_SDL_MusicChannel(CPP_SDL_MusicChannel&&) = default;
	CPP_SDL_MusicChannel& operator=(const CPP_SDL_MusicChannel&) = default;
	CPP_SDL_MusicChannel& operator=(CPP_SDL_MusicChannel&&) = default;
	
	virtual void registerOnComplete(std::function<void()> onCompleteFunction) const override;
	virtual void unregisterOnComplete() const override;
	
	virtual std::experimental::optional<double> getPosition() const override;
	
	virtual bool stop() const override;
	
	virtual void setVolume(double value) const override;
	
	virtual void setPan(double value) const override;
	
private:
	
};

#endif /* CPP_SDL_MusicChannel_h */
