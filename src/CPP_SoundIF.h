//
//  CPP_SoundIF.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/6/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SoundIF_h
#define CPP_SoundIF_h

#include <memory>
#include <experimental/optional>

class CPP_SoundChannelIF;

class CPP_SoundIF
{
public:
	CPP_SoundIF() = default;
	virtual ~CPP_SoundIF() = default;
	CPP_SoundIF(const CPP_SoundIF&) = default;
	CPP_SoundIF(CPP_SoundIF&&) = default;
	CPP_SoundIF& operator=(const CPP_SoundIF&) = default;
	CPP_SoundIF& operator=(CPP_SoundIF&&) = default;
	
	virtual std::unique_ptr<CPP_SoundChannelIF> play(double startTime=0.0, double pan=0.0, double volume=1.0) const = 0;
		
	virtual std::experimental::optional<double> getLength() const = 0;
	
};

#endif /* CPP_SoundIF_h */
