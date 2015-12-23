#include "CPPEngine.h"

#include "CPP.h"

#include "ofAppGlutWindow.h"
#include "ofAppRunner.h"

void CPPEngine::init( CPPBaseWorld* world, unsigned int width, unsigned int height, bool fixed/* = false*/, unsigned int frameRate/* = 60*/ )
{
	ofAppGlutWindow window;
	ofSetupOpenGL( &window, width, height, OF_WINDOW ); // Set up the GL context
	
	CPP::initialize();
	CPP* cpp = CPP::getInstance();

	CPP::setWorld( world );

	CPP::setWidth( width );
	CPP::setHeight( height );

	CPP::setFixed( fixed );
	CPP::setTimeInFrames( fixed );

	if ( !fixed )
	{
		CPP::setAssignedFrameRate( 0 );
	}
	else
	{
		CPP::setAssignedFrameRate( frameRate );
	}
	

	ofRunApp( cpp ); // DOES NOT EXIT.
}
