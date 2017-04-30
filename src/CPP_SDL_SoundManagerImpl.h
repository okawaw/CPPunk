//
//  CPP_SDL_SoundManagerImpl.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/8/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SDL_SoundManagerImpl_h
#define CPP_SDL_SoundManagerImpl_h

#include "CPP_SoundManagerImplIF.h"

#include <functional>
#include <memory>

class CPP_SDL_Sound;
class CPP_SDL_SoundChannel;
class CPP_SDL_Music;
class CPP_SDL_MusicChannel;
class CPP_SoundChannelIF;

class Mix_Chunk;
class _Mix_Music;

class CPP_SDL_SoundManagerImpl : public CPP_SoundManagerImplIF
{
	friend CPP_SDL_Sound;
	friend CPP_SDL_SoundChannel;
	friend CPP_SDL_Music;
	friend CPP_SDL_MusicChannel;
public:
	CPP_SDL_SoundManagerImpl(unsigned int channels);
	virtual ~CPP_SDL_SoundManagerImpl() = default;
	CPP_SDL_SoundManagerImpl(const CPP_SDL_SoundManagerImpl&) = default;
	CPP_SDL_SoundManagerImpl(CPP_SDL_SoundManagerImpl&&) = default;
	CPP_SDL_SoundManagerImpl& operator=(const CPP_SDL_SoundManagerImpl&) = default;
	CPP_SDL_SoundManagerImpl& operator=(CPP_SDL_SoundManagerImpl&&) = default;
	
	virtual void processSound() const override;
	
private:
	static std::unique_ptr<CPP_SoundChannelIF> playSound(Mix_Chunk& chunk, double volume, double pan);
	static void setSoundVolume(unsigned int soundID, int channel, double value);
	static void setSoundPan(unsigned int soundID, int channel, double value);
	static void stopSound(unsigned int soundID, int channel);
	static void registerOnCompleteSound(unsigned int soundID, std::function<void()> onCompleteFunction);
	static void unregisterOnCompleteSound(unsigned int soundID);
	
	static std::unique_ptr<CPP_SoundChannelIF> playMusic(_Mix_Music& music, double volume);
	static void setMusicVolume(unsigned int musicID, double value);
	static void stopMusic(unsigned int musicID);
	static void registerOnCompleteMusic(unsigned int musicID, std::function<void()> onCompleteFunction);
	static void unregisterOnCompleteMusic(unsigned int musicID);
};

#endif /* CPP_SDL_SoundManagerImpl_h */
