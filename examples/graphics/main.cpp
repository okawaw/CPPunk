//
//  main.cpp
//  Test
//
//  Created by Wade Okawa-Scannell on 4/30/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP.h"
#include "CPP_Entity.h"
#include "CPP_Image.h"
#include "CPP_SDL_Engine.h"
#include "CPP_World.h"

#include <iostream>
#include <memory>
#include <utility>

class MyWorld : public CPP_World
{
public:
	MyWorld(CPP& cpp) :
	CPP_World{cpp}
	{
		auto image = std::make_shared<CPP_Image>(cpp.getBitmapData("graphic.png"));
		auto entity = std::make_shared<CPP_Entity>(cpp, 0.0, 0.0, std::move(image));
		
		add(std::move(entity));
	}
	
	virtual ~MyWorld() = default;
};

class MyEngine : public CPP_SDL_Engine
{
public:
	MyEngine(const unsigned int width, const unsigned int height, const double frameRate=60.0, const bool fixed=false) :
	CPP_SDL_Engine{"Graphics", width, height, frameRate, fixed}
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
	std::cout << "This sample requires any PNG file named \"graphic.png\"." << std::endl;
	
	MyEngine engine(640u, 480);
	engine.start();
	
	return 0;
}
