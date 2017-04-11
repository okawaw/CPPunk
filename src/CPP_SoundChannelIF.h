//
//  CPP_SoundChannelIF.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/7/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SoundChannelIF_h
#define CPP_SoundChannelIF_h

#include <functional>
#include <experimental/optional>

class CPP_SoundChannelIF
{
public:
	CPP_SoundChannelIF() = default;
	virtual ~CPP_SoundChannelIF() = default;
	CPP_SoundChannelIF(const CPP_SoundChannelIF&) = default;
	CPP_SoundChannelIF(CPP_SoundChannelIF&&) = default;
	CPP_SoundChannelIF& operator=(const CPP_SoundChannelIF&) = default;
	CPP_SoundChannelIF& operator=(CPP_SoundChannelIF&&) = default;
	
	virtual void registerOnComplete(std::function<void()> onCompleteFunction) const = 0;
	virtual void unregisterOnComplete() const = 0;
	
	virtual std::experimental::optional<double> getPosition() const = 0;
	
	virtual bool stop() const = 0;
	
	virtual void setVolume(double value) const = 0;
	
	virtual void setPan(double value) const = 0;
	
};

#endif /* CPP_SoundChannelIF_h */
