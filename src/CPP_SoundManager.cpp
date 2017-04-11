//
//  CPP_SoundManager.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/9/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_SoundManager.h"

#include "CPP.h"
#include "CPP_Sfx.h"

#include <utility>

void CPP_SoundManager::setImpl(std::unique_ptr<CPP_SoundManagerImplIF> _impl)
{
	impl = std::move(_impl);
}

void CPP_SoundManager::processSound() const
{
	if (impl)
	{
		impl->processSound();
	}
}

double CPP_SoundManager::getPan(const std::experimental::optional<CPP_SfxType>& type) const
{
	const auto typePanMapIterator = typePanMap.find(type);
	
	return (typePanMapIterator != typePanMap.cend()) ? typePanMapIterator->second : 0.0;
}

double CPP_SoundManager::getVolume(const std::experimental::optional<CPP_SfxType>& type) const
{
	const auto typeVolumeMapIterator = typeVolumeMap.find(type);
	
	return (typeVolumeMapIterator != typeVolumeMap.cend()) ? typeVolumeMapIterator->second : 1.0;
}

void CPP_SoundManager::setPan(const std::experimental::optional<CPP_SfxType>& type, const double pan)
{
	typePanMap[type] = CPP::clamp(pan, -1.0, 1.0);
	
	const auto typePlayingMapIterator = typePlayingMap.find(type);
	
	if (typePlayingMapIterator != typePlayingMap.end())
	{
		const auto& typePlayingInternalMap = typePlayingMapIterator->second;
		
		for (const auto& sfxPair : typePlayingInternalMap)
		{
			const auto& sfx = sfxPair.second;
			
			sfx.get().setPan(sfx.get().getPan());
		}
	}
}

void CPP_SoundManager::setVolume(const std::experimental::optional<CPP_SfxType>& type, const double volume)
{
	typeVolumeMap[type] = (volume < 0.0) ? 0.0 : volume;
	
	const auto typePlayingMapIterator = typePlayingMap.find(type);
	
	if (typePlayingMapIterator != typePlayingMap.end())
	{
		const auto& typePlayingInternalMap = typePlayingMapIterator->second;
		
		for (const auto& sfxPair : typePlayingInternalMap)
		{
			const auto& sfx = sfxPair.second;
			
			sfx.get().setVolume(sfx.get().getVolume());
		}
	}
}

void CPP_SoundManager::resetPan(const std::experimental::optional<CPP_SfxType>& type)
{
	typePanMap.erase(type);
}

void CPP_SoundManager::resetVolume(const std::experimental::optional<CPP_SfxType>& type)
{
	typeVolumeMap.erase(type);
}


void CPP_SoundManager::addPlaying(CPP_Sfx& sfx)
{
	typePlayingMap[sfx.getType()].emplace(std::cref(sfx), std::ref(sfx));
}

void CPP_SoundManager::removePlaying(const CPP_Sfx& sfx)
{
	const auto typePlayingMapIterator = typePlayingMap.find(sfx.getType());
	
	if (typePlayingMapIterator != typePlayingMap.end())
	{
		auto& typePlayingInternalMap = typePlayingMapIterator->second;

		typePlayingInternalMap.erase(std::cref(sfx));
		
		if (typePlayingInternalMap.empty())
		{
			typePlayingMap.erase(typePlayingMapIterator);
		}
	}
}
