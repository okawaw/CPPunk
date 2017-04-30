//
//  CPP_Sfx.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/7/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_Sfx.h"

#include "CPP.h"

#include <algorithm>
#include <utility>

CPP_Sfx::CPP_Sfx(CPP& cpp, std::unique_ptr<CPP_SoundIF> sound, std::function<void()> complete, std::experimental::optional<CPP_SfxType> type) :
  cpp{cpp}
, type{std::move(type)}
, vol{1.0}
, pan{0.0}
, filteredVol{1.0}
, filteredPan{0.0}
, sound{std::move(sound)}
, position{0.0}
, looping{false}
, complete{std::move(complete)}
{
}

CPP_Sfx::~CPP_Sfx()
{
	stop();
}

void CPP_Sfx::play(const double _vol, const double _pan)
{
	if (channel)
	{
		stop();
	}
	
	pan = CPP::clamp(_pan, -1.0, 1.0);
	vol = (_vol < 0.0) ? 0.0 : _vol;
	filteredPan = CPP::clamp(pan + cpp.soundManager.getPan(type), -1.0, 1.0);
	filteredVol = std::max(0.0, vol * cpp.soundManager.getVolume(type));
	
	channel = sound->play(0.0, filteredPan, filteredVol);
	
	if (channel)
	{
		addPlaying();
		channel->registerOnComplete([this]()
		{
			onComplete();
		});
	}
	
	looping = false;
	position = 0.0;
}

std::function<void()> CPP_Sfx::getComplete() const
{
	return complete;
}

void CPP_Sfx::setComplete(const std::function<void()>& value)
{
	complete = value;
}

void CPP_Sfx::loop(const double _vol, const double _pan)
{
	play(_vol, _pan);
	looping = true;
}

bool CPP_Sfx::stop()
{
	if (!channel)
	{
		return false;
	}
	
	removePlaying();
	
	position = channel->getPosition().value_or(0.0);
	
	channel->unregisterOnComplete();
	channel->stop();
	channel.reset();
	
	return true;
}

// TODO: Reset unique_ptr vs. assignment operator.
// TODO: Null check for sound in each function.
// TODO: Make the ordering of val and pan consistent.
// TODO: Change all const CPP& cpp to non-const.

void CPP_Sfx::resume()
{
	channel = sound->play(position, filteredPan, filteredVol);
	
	if (channel)
	{
		addPlaying();
		channel->registerOnComplete([this]()
		{
			onComplete();
		});
	}
	
	position = 0.0;
}

double CPP_Sfx::getVolume() const
{
	return vol;
}

void CPP_Sfx::setVolume(const double value)
{
	if (!channel)
	{
		return;
	}
	
	const auto _value = (value < 0.0) ? 0.0 : value;
	vol = _value;
	
	auto _filteredVol = _value * cpp.soundManager.getVolume(type);
	_filteredVol = (_filteredVol < 0.0) ? 0.0 : _filteredVol;
	
	if (_filteredVol == filteredVol)
	{
		return;
	}
	
	filteredVol = _filteredVol;
	
	channel->setVolume(filteredVol);
}

double CPP_Sfx::getPan() const
{
	return pan;
}

void CPP_Sfx::setPan(const double value)
{
	if (!channel)
	{
		return;
	}
	
	const auto _value = CPP::clamp(value, -1.0, 1.0);
	pan = _value;
	
	const auto _filteredPan = CPP::clamp(_value + cpp.soundManager.getPan(type), -1.0, 1.0);
	
	if (_filteredPan == filteredPan)
	{
		return;
	}
	
	filteredPan = _filteredPan;
	
	channel->setPan(filteredPan);
}

std::experimental::optional<CPP_SfxType> CPP_Sfx::getType() const
{
	return type;
}

void CPP_Sfx::setType(const std::experimental::optional<CPP_SfxType> value)
{
	if (type == value)
	{
		return;
	}
	
	if (channel)
	{
		removePlaying();
		type = value;
		addPlaying();
		// Reset, in case type has different global settings.
		setPan(getPan());
		setVolume(getVolume());
	}
	else
	{
		type = value;
	}
}

bool CPP_Sfx::isPlaying() const
{
	return channel != nullptr;
}

std::experimental::optional<double> CPP_Sfx::getPosition() const
{
	if (channel)
	{
		const auto value = channel->getPosition();
		
		if (value)
		{
			return {*value / 1000.0};
		}
		else
		{
			return std::experimental::nullopt;
		}
	}
	else
	{
		return {position / 1000.0};
	}
}

std::experimental::optional<double> CPP_Sfx::getLength() const
{
	const auto value = sound->getLength();
	
	if (value)
	{
		return {*value / 1000.0};
	}
	else
	{
		return std::experimental::nullopt;
	}
}

void CPP_Sfx::onComplete()
{
	if (looping)
	{
		loop(vol, pan);
	}
	else
	{
		stop();
	}
	
	position = 0.0;
	
	if (complete)
	{
		complete();
	}
}

void CPP_Sfx::addPlaying()
{
	cpp.soundManager.addPlaying(*this);
}

void CPP_Sfx::removePlaying() const
{
	cpp.soundManager.removePlaying(*this);
}
