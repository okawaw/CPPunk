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
#include <utility>

CPP_Engine::CPP_Engine(std::string title, const unsigned int width, const unsigned int height, const double frameRate, const bool fixed) :
  paused{false}
, maxElapsed{std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>{1.0 / 30.0})}
, maxFrameSkip{5u}
, tickRate{std::chrono::milliseconds{4u}}
, running{false}
, delta{std::chrono::steady_clock::duration::zero()}
, last{}
, skip{std::chrono::steady_clock::duration::zero()}
, timerPrev{}
, flashTime{}
, frameLast{}
, frameListSum{std::chrono::steady_clock::duration::zero()}
, frameList{}
{
	// Global game properties.
	cpp.title = std::move(title);
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
	if (cpp.isFixed())
	{
		skip = cpp.assignedFrameTime * (maxFrameSkip + 1u);
	}
	
	{
		const auto time = CPP::getTimer();
		last = time;
		timerPrev = time;
	}
	
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
	cpp.input.processInput();
	cpp.soundManager.processSound();
	
	if (cpp.isFixed())
	{
		fixedFramerateGameLoop();
	}
	else
	{
		framerateIndependentGameLoop();
	}
}

void CPP_Engine::framerateIndependentGameLoop()
{
	// Execute at the assigned framerate.
	const auto time0 = CPP::getTimer();
	if ((time0 - timerPrev) < cpp.assignedFrameTime)
	{
		return;
	}
	
	timerPrev = time0;
	
	// Update timer.
	const auto time1 = CPP::getTimer();
	const auto gameTime = time1;
	cpp.flashTime = time1 - flashTime;
	const auto updateTime = time1;
	cpp.elapsed = (time1 - last);
	if (cpp.elapsed > maxElapsed)
	{
		cpp.elapsed = maxElapsed;
	}
	
	cpp.elapsed = std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>{cpp.elapsed} * cpp.rate);
	last = time1;
	
	// TODO: Update console.
	
	// Update loop.
	if (!paused)
	{
		update();
	}
	
	// Update input.
	cpp.input.update();
	
	// Update timer.
	const auto time2 = CPP::getTimer();
	const auto renderTime = time2;
	cpp.updateTime = time2 - updateTime;
	
	// Render loop.
	if (!paused)
	{
		if (rendererImpl)
		{
			rendererImpl->render();
		}
	}
	
	// Update timer.
	const auto time3 = CPP::getTimer();
	flashTime = time3;
	cpp.renderTime = time3 - renderTime;
	cpp.gameTime = time3 - gameTime;
}

void CPP_Engine::fixedFramerateGameLoop()
{
	// Execute at the assigned tick rate.
	const auto time0 = CPP::getTimer();
	if ((time0 - timerPrev) < tickRate)
	{
		return;
	}
	
	// Update timer.
	const auto time1 = CPP::getTimer();
	delta += (time1 - last);
	last = time1;
	
	// Quit if a frame hasn't passed.
	if (delta < cpp.assignedFrameTime)
	{
		return;
	}
	
	// Update timer.
	const auto gameTime = time1;
	cpp.flashTime = time1 - flashTime;
	
	// TODO: Update console.
	
	// Update loop.
	if (delta > skip)
	{
		delta = skip;
	}
	while (delta >= cpp.assignedFrameTime)
	{
		cpp.elapsed = std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>{cpp.assignedFrameTime} * cpp.rate);
		
		// Update timer.
		const auto updateTime = time1;
		delta -= cpp.assignedFrameTime;
		
		// Update loop.
		if (!paused)
		{
			update();
		}
		
		// Update input.
		cpp.input.update();
		
		// Update timer.
		const auto time3 = CPP::getTimer();
		cpp.updateTime = time3 - updateTime;
	}
	
	const auto time4 = CPP::getTimer();
	const auto renderTime = time4;
	
	// Render loop.
	if (!paused)
	{
		if (rendererImpl)
		{
			rendererImpl->render();
		}
	}
	
	// Update timer.
	const auto time5 = CPP::getTimer();
	flashTime = time5;
	cpp.renderTime = time5 - renderTime;
	cpp.gameTime = time5 - gameTime;
	
	timerPrev = CPP::getTimer();
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

void CPP_Engine::setInput(std::unique_ptr<CPP_InputImplIF> input)
{
	cpp.input.setImpl(std::move(input));
}

void CPP_Engine::setSoundManager(std::unique_ptr<CPP_SoundManagerImplIF> soundManager)
{
	cpp.soundManager.setImpl(std::move(soundManager));
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
