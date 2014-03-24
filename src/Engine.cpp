#include "Engine.h"

#include "CPP.h"

#include "ofAppGlutWindow.h"
#include "ofAppRunner.h"

void Engine::init( BaseWorld* world, unsigned int width, unsigned int height, unsigned int frameRate/* = 60*/ )
{
	ofAppGlutWindow window;
	ofSetupOpenGL( &window, width, height, OF_WINDOW ); // Set up the GL context
	
	CPP* cpp = new CPP();

	CPP::setWorld( world );

	CPP::setWidth( width );
	CPP::setHeight( height );

	CPP::setFrameRate( frameRate );

	ofRunApp( cpp ); // DOES NOT EXIT.
}
