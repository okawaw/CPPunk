//
//  CPP_Engine.h
//  Test
//
//  Created by Wade Okawa-Scannell on 9/18/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_Engine_h
#define CPP_Engine_h

#include "CPP.h"

#include <chrono>
#include <memory>
#include <queue>

class CPP_BitmapDataFactoryIF;
class CPP_Input;

class CPP_Engine
{
public:
	CPP_Engine(unsigned int width, unsigned int height, double frameRate=60.0, bool fixed=false);
	virtual ~CPP_Engine() = default;
	
	bool paused;
	
	std::chrono::steady_clock::duration maxElapsed;
	
	unsigned int maxFrameSkip;
	
	std::chrono::steady_clock::duration tickRate;
	
	void start();
	
	void end();
	
	virtual void init();
	
	virtual void gameLoop();
	
	virtual void update();
	
	// TODO: virtual void debugUpdate();
	
	virtual void render();
	
	virtual void focusGained();
	
	virtual void focusLost();
	
	//virtual void

protected:
	void setBitmapDataFactory(std::unique_ptr<CPP_BitmapDataFactoryIF> bitmapDataFactory);
	void setInput(std::unique_ptr<CPP_Input> input);
	
	CPP cpp;
	
private:
	void framerateIndependentGameLoop();
	void fixedFramerateGameLoop();
	
	void checkWorld();
	
	bool running;
	
	// Timing information.
	std::chrono::steady_clock::duration delta;
	std::chrono::steady_clock::time_point last;
	std::chrono::steady_clock::duration skip;
	std::chrono::steady_clock::time_point timerPrev;
	
	// Debug timing information.
	std::chrono::steady_clock::time_point flashTime;
	
	// Framerate tracking.
	std::chrono::steady_clock::time_point frameLast; // Should be set to 0 initially, or something equivalent. Don't default construct!
	std::chrono::steady_clock::duration frameListSum; // Should be set to be equal to the frameLast if the frameList is empty. Don't default construct!
	std::queue<std::chrono::steady_clock::duration> frameList;
	
};

#endif /* CPP_Engine_h */
