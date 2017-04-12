//
//  CPP_Sfx.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/6/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_Sfx_h
#define CPP_Sfx_h

#include "CPP.h"
#include "CPP_SoundIF.h"
#include "CPP_SoundChannelIF.h"

#include <functional>
#include <memory>
#include <experimental/optional>

enum class CPP_SfxType;

class CPP_Sfx
{
public:
	CPP_Sfx(CPP& cpp, std::unique_ptr<CPP_SoundIF> sound, std::function<void()> complete=nullptr, std::experimental::optional<CPP_SfxType> type=std::experimental::nullopt);
	~CPP_Sfx() = default;
	CPP_Sfx(const CPP_Sfx&) = default;
	CPP_Sfx(CPP_Sfx&&) = default;
	CPP_Sfx& operator=(const CPP_Sfx&) = default;
	CPP_Sfx& operator=(CPP_Sfx&&) = default;
	
	std::function<void()> getComplete() const;
	void setComplete(const std::function<void()>& value);
	
	void play(double vol=1.0, double pan=0.0);
	
	void loop(double vol=1.0, double pan=0.0);
	
	bool stop();
	
	void resume();
	
	double getVolume() const;
	void setVolume(double value);
	
	double getPan() const;
	void setPan(double value);
	
	std::experimental::optional<CPP_SfxType> getType() const;
	void setType(const std::experimental::optional<CPP_SfxType> value);
	
	bool isPlaying() const;
	
	std::experimental::optional<double> getPosition() const;
	
	std::experimental::optional<double> getLength() const;
	
private:	
	void onComplete();
	
	void addPlaying();
	void removePlaying() const;
	
	CPP& cpp;
	
	std::experimental::optional<CPP_SfxType> type;
	double vol;
	double pan;
	double filteredVol;
	double filteredPan;
	std::unique_ptr<CPP_SoundIF> sound; // TODO: Make this a shared_ptr.
	std::unique_ptr<CPP_SoundChannelIF> channel;
	double position;
	bool looping;
	
	std::function<void()> complete;
};

#endif /* CPP_Sfx_h */
