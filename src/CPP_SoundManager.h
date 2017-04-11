//
//  CPP_SoundManager.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/7/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SoundManager_h
#define CPP_SoundManager_h

#include "CPP_SoundManagerImplIF.h"

#include <cstddef>
#include <functional>
#include <memory>
#include <experimental/optional>
#include <unordered_map>

class CPP_Engine;
class CPP_Sfx;

enum class CPP_SfxType;

class CPP_SoundManager
{
	friend CPP_Engine; // TODO: Why is this a friend?
	friend CPP_Sfx;
public:
	CPP_SoundManager() = default;
	~CPP_SoundManager() = default;
	CPP_SoundManager(const CPP_SoundManager&) = default;
	CPP_SoundManager(CPP_SoundManager&&) = default;
	CPP_SoundManager& operator=(const CPP_SoundManager&) = default;
	CPP_SoundManager& operator=(CPP_SoundManager&&) = default;
	
	void setImpl(std::unique_ptr<CPP_SoundManagerImplIF> impl);
	
	void processSound() const;
	
	double getVolume(const std::experimental::optional<CPP_SfxType>& type) const;
	void setVolume(const std::experimental::optional<CPP_SfxType>& type, double volume);
	void resetVolume(const std::experimental::optional<CPP_SfxType>& type);

	double getPan(const std::experimental::optional<CPP_SfxType>& type) const;
	void setPan(const std::experimental::optional<CPP_SfxType>& type, double pan);
	void resetPan(const std::experimental::optional<CPP_SfxType>& type);
	
private:
	void addPlaying(CPP_Sfx& sfx);
	void removePlaying(const CPP_Sfx& sfx);
	
	std::unique_ptr<CPP_SoundManagerImplIF> impl;
	
	struct Hash
	{
		std::size_t operator()(const std::reference_wrapper<const CPP_Sfx>& sfx) const
		{
			return std::hash<const CPP_Sfx*>()(&sfx.get());
		}
	};
	
	struct Equality
	{
		bool operator()(const std::reference_wrapper<const CPP_Sfx>& lhs, const std::reference_wrapper<const CPP_Sfx>& rhs) const
		{
			return &lhs.get() == &rhs.get();
		}
	};
	
	std::unordered_map<std::experimental::optional<CPP_SfxType>, std::unordered_map<std::reference_wrapper<const CPP_Sfx>, const std::reference_wrapper<CPP_Sfx>, Hash, Equality> > typePlayingMap;
	std::unordered_map<std::experimental::optional<CPP_SfxType>, double> typeVolumeMap;
	std::unordered_map<std::experimental::optional<CPP_SfxType>, double> typePanMap;
};

#endif /* CPP_SoundManager_h */
