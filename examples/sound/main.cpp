//
//  main.cpp
//  Test
//
//  Created by Wade Okawa-Scannell on 4/30/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP.h"
#include "CPP_Key.h"
#include "CPP_SDL_Engine.h"
#include "CPP_SDL_Music.h"
#include "CPP_SDL_Sound.h"
#include "CPP_Sfx.h"
#include "CPP_World.h"

#include <iostream>
#include <memory>

class MyWorld : public CPP_World
{
public:
	MyWorld(CPP& cpp) :
	CPP_World{cpp}
	, sound{cpp, std::make_unique<CPP_SDL_Sound>("sound.wav")}
	, music{cpp, std::make_unique<CPP_SDL_Music>("music.wav")}
	{
	}
	
	virtual ~MyWorld() = default;
	
	virtual void update() override
	{
		if (cpp.pressed(CPP_Key::S))
		{
			if (cpp.check(CPP_Key::SHIFT))
			{
				sound.loop();
			}
			else
			{
				sound.play();
			}
		}
		if (cpp.pressed(CPP_Key::M))
		{
			if (cpp.check(CPP_Key::SHIFT))
			{
				music.loop();
			}
			else
			{
				music.play();
			}
		}
	}
	
private:
	CPP_Sfx sound;
	CPP_Sfx music;
};

class MyEngine : public CPP_SDL_Engine
{
public:
	MyEngine(const unsigned int width, const unsigned int height, const double frameRate=60.0, const bool fixed=false) :
	CPP_SDL_Engine{"Sound", width, height, frameRate, fixed}
	{
	}
	
	virtual ~MyEngine() = default;
	
	virtual void init() override
	{
		CPP_SDL_Engine::init();
		
		cpp.setWorld(std::make_shared<MyWorld>(cpp));
	}
};

int main(int argc, const char* argv[])
{
	std::cout << "This sample requires any two WAV files named \"sound.wav\" and \"music.wav\"." << std::endl;
	std::cout << "Press <S> to play sound. Press <M> to play music. Hold <SHIFT> when pressing <P> or <M> to loop sound or music." << std::endl;
	
	MyEngine engine(640u, 480);
	engine.start();
	
	return 0;
}
