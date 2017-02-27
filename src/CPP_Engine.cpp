//
//  CPP_Engine.cpp
//  Test
//
//  Created by Wade Okawa-Scannell on 9/18/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_Engine.h"

#include "CPP_BitmapDataFactoryIF.h"
#include "CPP_World.h"

#include <random>
#include <thread>
#include <utility>

CPP_Engine::CPP_Engine(const unsigned int width, const unsigned int height, const double frameRate, const bool fixed) :
  paused{false}
, maxElapsed{0.0333}
, maxFrameSkip{5u}
, tickRate{4u}
, running{false}
, frameListSum{std::chrono::steady_clock::duration::zero()}
{
	// Global game properties.
	cpp.width = width;
	cpp.height = height;
	cpp.halfWidth = static_cast<double>(width) / 2.0;
	cpp.halfHeight = static_cast<double>(height) / 2.0;
	cpp.assignedFrameTime = std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>{1.0 / frameRate});
	cpp.assignedFrameRate = frameRate;
	cpp.fixed = fixed;
	cpp.timeInFrames = fixed;
	
	// Global game objects.
	cpp.engine = this;
	// TODO: Screen?
	cpp.bounds.x = 0.0;
	cpp.bounds.y = 0.0;
	cpp.width = static_cast<double>(width);
	cpp.height = static_cast<double>(height);
	cpp.world = std::make_shared<CPP_World>(cpp); // TODO: Set this to a blank world.
	// cpp.camera = cpp._world->camera; // TODO: Put all this in once CPP_World is implemented.
	// Draw.resetTarget();
	
	// Miscellaneous startup stuff.
	if (cpp.getRandomSeed() == std::minstd_rand0::default_seed)
	{
		cpp.randomizeSeed();
	}
	cpp._time = CPP::getTimer();
}

void CPP_Engine::start()
{
	running = true;
	
	// Switch worlds.
	if (cpp.gotoWorld)
	{
		checkWorld();
	}
	
	// Game start.
	init();
	
	
	// Start game loop.
	
	while(running)
	{
		gameLoop();
	}
}

void CPP_Engine::end()
{
	running = false;
}

void CPP_Engine::init()
{
}

void CPP_Engine::gameLoop()
{
	if (cpp.isFixed())
	{
		// Fixed framerate.
		// TODO: Implement this better.
		std::this_thread::sleep_for(cpp.assignedFrameTime);
		fixedFramerateGameLoop();
	}
	else
	{
		// Nonfixed framerate.
		framerateIndependentGameLoop();
	}
}

void CPP_Engine::framerateIndependentGameLoop()
{
	// TODO: Finish this.
	if (!paused)
	{
		update();
	}
	if (!paused)
	{
		render();
	}
}

void CPP_Engine::fixedFramerateGameLoop()
{
	// TODO: Finish this.
	if (!paused)
	{
		update();
	}
	if (!paused)
	{
		render();
	}
}

void CPP_Engine::update()
{
	cpp.world->updateLists();
	
	if (cpp.gotoWorld)
	{
		checkWorld();
	}
	// TODO: Tween stuff.
	//if (cpp.tweener.active() && cpp.tweener._tween)
	//{
	//	cpp.tweener.updateTweens();
	//}
	if (cpp.world->isActive())
	{
		// TODO: Tween stuff.
		//if (cpp.world->_tween)
		//{
		//	cpp.world->updateTweens();
		//}
		cpp.world->update();
	}
	cpp.world->updateLists(false);
}

void CPP_Engine::render()
{
	// Timing stuff.
	if (frameLast == std::chrono::steady_clock::time_point{})
	{
		frameLast = CPP::getTimer();
	}
	
	// Render loop.
	if (cpp.world->isVisible())
	{
		cpp.world->render();
	}
	
	// More timing stuff.
	const auto t = CPP::getTimer();
	frameList.emplace(t - frameLast);
	frameListSum += frameList.back();
	
	if (frameList.size() > 120u)
	{
		frameListSum -= frameList.front();
		frameList.pop();
	}
	
	cpp.frameTime = frameListSum / frameList.size();
	cpp.frameRate = 1.0 / std::chrono::duration<double>{cpp.frameTime}.count();
	frameLast = t;
}

void CPP_Engine::focusGained()
{
}

void CPP_Engine::focusLost()
{
}

void CPP_Engine::setBitmapDataFactory(std::unique_ptr<CPP_BitmapDataFactoryIF> bitmapDataFactory)
{
	cpp.bitmapDataFactory = std::move(bitmapDataFactory);
}

void CPP_Engine::setInput(std::unique_ptr<CPP_Input> input)
{
	cpp.input = std::move(input);
}

void CPP_Engine::checkWorld()
{
	if (!cpp.gotoWorld)
	{
		return;
	}
	cpp.world->end();
	cpp.world->updateLists();
	// TODO: Tween stuff.
	//if (cpp.world && cpp.world->isAutoClear() && cpp.world->tween)
	//{
		
	//}
	cpp.world = std::move(cpp.gotoWorld);
	cpp.camera = cpp.world->getCamera();
	cpp.world->updateLists();
	cpp.world->begin();
	cpp.world->updateLists();
}
