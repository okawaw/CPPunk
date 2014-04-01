#ifndef CPP_ENGINE_H_
#define CPP_ENGINE_H_

#include "CPPBaseWorld.h"

class CPPEngine
{
public:
	static void init( CPPBaseWorld* world, unsigned int width, unsigned int height, unsigned int frameRate = 60 );
};

#endif
