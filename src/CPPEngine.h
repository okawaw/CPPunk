#ifndef CPP_ENGINE_H_
#define CPP_ENGINE_H_

#include "CPPBaseWorld.h"

class CPPEngine
{
public:
	// Defines startup information about your game.
	static void init( CPPBaseWorld* world, unsigned int width, unsigned int height, bool fixed = false, unsigned int frameRate = 60 );
};

#endif
