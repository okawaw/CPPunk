#include "CPP.h"

#include "CPPBaseWorld.h"
#include "CPPStateHandler.h"
#include "utils/CPPInput.h"
#include "graphics/utils/CPPTextResourceManager.h"
#include "graphics/utils/CPPBitmapDataResourceManager.h"

#include "ofAppRunner.h"
#include "ofUtils.h"

#include <math.h> // trunc // CPPUtil
#include <sstream> // split // CPPUtil
#include <stdlib.h>

static const int CAMERA_Z = 100;

static const std::string VERSION = "1.0.0";       // The CPPunk major version.

bool CPP::ms_bPaused = false;                     // If the game should stop updating/rendering.

bool CPP::ms_bFixed;                              // If the game is running at a fixed framerate
bool CPP::ms_bTimeInFrames;                       // If times should be given in frames (as opposed to seconds).
                                                  // Default is true in fixed timestep mode and false in variable timestep mode.

unsigned int CPP::ms_width;                       // Width of the game.
unsigned int CPP::ms_height;                      // Height of the game.
float CPP::ms_halfWidth;                          // Half width of the game.
float CPP::ms_halfHeight;                         // Half height of the game.

unsigned int CPP::ms_assignedFrameRate;           // Desired frame rate of the game.

//CPPStateHandler CPP::ms_stateHandler;             // Static state handler. TODO: should be absorbed by CPP.

CPP* CPP::ms_pInstance = NULL;

ofCamera CPP::ms_camera;                          // Camera for the game.

void CPP::initialize()
{
	if ( !ms_pInstance )
	{
		ms_pInstance = new CPP();
	}
}

CPP* CPP::getInstance()
{
	return ms_pInstance;
}

CPP::CPP() :
  ofBaseApp()
{
	// Create "globals"
	CPPBitmapDataResourceManager::initialize();
	CPPTextResourceManager::initialize();
	CPPStateHandler::initialize();
}

CPP::~CPP()
{
	// Tear down "globals"
	CPPStateHandler::destroy();
	CPPTextResourceManager::destroy();
	CPPBitmapDataResourceManager::destroy();
}

//--------------------------------------------------------------
void CPP::setup()
{
	// Set world camera to orthographic mode.
	ms_camera.enableOrtho();

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR < 8
	// Move camera's top left position to (0, 0) by default.
	ms_camera.setPosition( 0, ms_height, CAMERA_Z );                            // IMPORTANT! Camera's y position must be sum of position and screen height.
	// Flip camera's y values to prevent mirroring.
	ms_camera.setScale( 1, -1, 1 );
#else
	// Move camera's top left position to (0, 0) by default.
	ms_camera.setPosition( 0, 0, CAMERA_Z );
	// Set VFlip to true to make origin in top left corner.
	ms_camera.setVFlip( true );
#endif
}

//--------------------------------------------------------------
void CPP::update()
{
	if ( !ms_bPaused )
	{
		CPPStateHandler::getInstance()->update();
	}

	CPPInput::update();
}

//--------------------------------------------------------------
void CPP::draw()
{
	ms_camera.begin();

	if ( !ms_bPaused )                         // TODO: pausing the render results in nothing being drawn...fix this...
	{
		CPPStateHandler::getInstance()->draw();
	}

	ms_camera.end();
}

//--------------------------------------------------------------
void CPP::keyPressed( int key )
{
	CPPInput::onKeyDown( key );
	CPPStateHandler::getInstance()->keyPressed( key ); // TODO: possibly remove this and subsequent calls.
}

//--------------------------------------------------------------
void CPP::keyReleased( int key )
{
	CPPInput::onKeyUp( key );
	CPPStateHandler::getInstance()->keyReleased( key ); // TODO: possibly remove this and subsequent calls.
}

//--------------------------------------------------------------
void CPP::mouseMoved( int x, int y )
{
	CPPStateHandler::getInstance()->mouseMoved( x, y );
}

//--------------------------------------------------------------
void CPP::mouseDragged( int x, int y, int button )
{
	CPPStateHandler::getInstance()->mouseDragged( x, y, button );
}

//--------------------------------------------------------------
void CPP::mousePressed( int x, int y, int button )
{
	CPPStateHandler::getInstance()->mousePressed( x, y, button );
}

//--------------------------------------------------------------
void CPP::mouseReleased( int x, int y, int button )
{
	CPPStateHandler::getInstance()->mouseReleased( x, y, button );
}

//--------------------------------------------------------------
void CPP::windowResized( int w, int h )
{
	// HACK: Somehow prevent resizing.
	ofSetWindowShape( ms_width, ms_height );

	CPPStateHandler::getInstance()->windowResized( w, h );
}

//--------------------------------------------------------------
void CPP::gotMessage( ofMessage msg )
{
	CPPStateHandler::getInstance()->gotMessage( msg );
}

//--------------------------------------------------------------
void CPP::dragEvent( ofDragInfo dragInfo )
{ 
	CPPStateHandler::getInstance()->dragEvent( dragInfo );
}

CPPBaseWorld* CPP::getWorld() { return CPPStateHandler::getInstance()->getWorld(); }

void CPP::setWorld( CPPBaseWorld* newWorld )
{
	// CPPStateHandler::getInstance()->changeWorld( newWorld );       // old TODO: REMOVE
	CPPStateHandler::getInstance()->setWorld( newWorld );
}

bool CPP::getPaused() { return ms_bPaused; }
void CPP::setPaused( const bool paused ) { ms_bPaused = paused; }

bool CPP::getFixed() { return ms_bFixed; }
void CPP::setFixed( const bool fixed ) { ms_bFixed = fixed; }

bool CPP::getTimeInFrames() { return ms_bTimeInFrames; }
void CPP::setTimeInFrames( const bool timeInFrames ) { ms_bTimeInFrames = timeInFrames; }

unsigned int CPP::getWidth() { return ms_width; }
unsigned int CPP::getHeight() { return ms_height; }
float CPP::getHalfWidth() { return ms_halfWidth; }
float CPP::getHalfHeight() { return ms_halfHeight; }

void CPP::setWidth( unsigned int width )
{
	ms_width = width;
	ms_halfWidth = width / 2.0;
}

void CPP::setHeight( unsigned int height )
{
	ms_height = height;
	ms_halfHeight = height / 2.0;
}

unsigned int CPP::getAssignedFrameRate() { return ms_assignedFrameRate; }

void CPP::setAssignedFrameRate( unsigned int frameRate )
{
	ms_assignedFrameRate = frameRate;
	ofSetFrameRate( frameRate );
}

float CPP::getFrameRate() { return ofGetFrameRate(); }

double CPP::getElapsed() { return ofGetLastFrameTime(); }

float CPP::getCameraX()
{
	return ms_camera.getPosition().x;
}

float CPP::getCameraY()
{
	return ms_camera.getPosition().y - ms_height;
}

void CPP::setCameraX( float x )
{
	ms_camera.setPosition( x, ms_camera.getPosition().y, CAMERA_Z );
}

void CPP::setCameraY( float y )
{
	ms_camera.setPosition( ms_camera.getPosition().x, y + ms_height, CAMERA_Z );
}

void CPP::setCameraPos( float x, float y )
{
	ms_camera.setPosition( x, y + ms_height, CAMERA_Z );
}

// TODO: Write squareDistance
float CPPUtil::distance( float x1, float y1, float x2, float y2 )
{
	return sqrt( ( x2 - x1 ) * ( x2 - x1 ) + ( y2 - y1 ) * ( y2 - y1 ) );
}

float CPPUtil::distanceRects( float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2 )
{
	if ( x1 < x2 + w2 && x2 < x1 + w1 )
	{
		if ( y1 < y2 + h2 && y2 < y1 + h1 )
		{
			return 0;
		}
		if ( y1 > y2 )
		{
			return y1 - ( y2 + h2 );
		}
		return y2 - (y1 + h1);
	}
	if ( y1 < y2 + h2 && y2 < y1 + h1 )
	{
		if ( x1 > x2 )
		{
			return x1 - ( x2 + w2 );
		}
		return x2 - ( x1 + w1 );
	}
	if ( x1 > x2 )
	{
		if ( y1 > y2 )
		{
			return CPPUtil::distance( x1, y1, ( x2 + w2 ), ( y2 + h2 ) );
		}
		return CPPUtil::distance( x1, y1 + h1, x2 + w2, y2 );
	}
	if ( y1 > y2 )
	{
		return CPPUtil::distance( x1 + w1, y1, x2, y2 + h2 );
	}
	return CPPUtil::distance( x1 + w1, y1 + h1, x2, y2 );
}

float CPPUtil::distanceRectPoint( float pX, float pY, float rX, float rY, float rW, float rH )
{
	if ( pX >= rX && pX <= rX + rW )
	{
		if ( pY >= rY && pY <= rY + rH )
		{
			return 0;
		}
		if ( pY > rY )
		{
			return pY - ( rY + rH );
		}
		return rY - pY;
	}
	if ( pY >= rY && pY <= rY + rH )
	{
		if ( pX > rX )
		{
			return pX - ( rX + rW );
		}
		return rX - pX;
	}
	if ( pX > rX )
	{
		if ( pY > rY )
		{
			return CPPUtil::distance( pX, pY, rX + rW, rY + rH );
		}
		return CPPUtil::distance( pX, pY, rX + rW, rY );
	}
	if ( pY > rY )
	{
		return CPPUtil::distance( pX, pY, rX, rY + rH );
	}
	return CPPUtil::distance( pX, pY, rX, rY );
}

void CPPUtil::alphaOver( unsigned char r1, unsigned char g1, unsigned char b1, unsigned char a1,
                         unsigned char r2, unsigned char g2, unsigned char b2, unsigned char a2,
                         unsigned char& resR, unsigned char& resG, unsigned char& resB, unsigned char& resA )
{
	resR = ( ( r1 * a1 * 255 ) + ( ( r2 * a2 ) * ( 255 - a1 ) ) ) / 65025;
	resG = ( ( g1 * a1 * 255 ) + ( ( g2 * a2 ) * ( 255 - a1 ) ) ) / 65025;
	resB = ( ( b1 * a1 * 255 ) + ( ( b2 * a2 ) * ( 255 - a1 ) ) ) / 65025;
	resA = ( ( a1 * 255 ) + ( a2 * ( 255 - a1 ) ) ) / 255;
}

void CPPUtil::split( const std::string& s, char delimiter, std::vector< std::string >& elements )
{
	std::stringstream ss( s );
	std::string item;
	while ( std::getline( ss, item, delimiter ) )
	{
		elements.push_back( item );
	}
}

float CPPUtil::trunc( float f )
{
	return ( f >= 0 ) ? floor( f ) : ceil( f );
}
