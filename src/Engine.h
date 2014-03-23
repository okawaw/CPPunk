#ifndef ENGINE_H
#define ENGINE_H

#include "BaseWorld.h"

class Engine
{
public:
	static void init( BaseWorld* world, unsigned int width, unsigned int height, unsigned int frameRate = 60 );
};

#endif
