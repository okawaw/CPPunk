#include "CPP.h"

#include "ofAppRunner.h"

static const std::string VERSION = "1.0.0";       // The CPPunk major version.

unsigned int CPP::m_width;                        // Width of the game.
unsigned int CPP::m_height;                       // Height of the game.
float CPP::m_halfWidth;                           // Half width of the game.
float CPP::m_halfHeight;                          // Half height of the game.

unsigned int CPP::m_frameRate;                    // Desired frame rate of the game.

StateHandler CPP::m_stateHandler;                 // Static state handler.

CPP::CPP()
{
}

//--------------------------------------------------------------
void CPP::setup()
{
}

//--------------------------------------------------------------
void CPP::update()
{
	m_stateHandler.update();
}

//--------------------------------------------------------------
void CPP::draw()
{
	m_stateHandler.draw();
}

//--------------------------------------------------------------
void CPP::keyPressed( int key )
{
	m_stateHandler.keyPressed( key );
}

//--------------------------------------------------------------
void CPP::keyReleased( int key )
{
	m_stateHandler.keyReleased( key );
}

//--------------------------------------------------------------
void CPP::mouseMoved( int x, int y )
{
	m_stateHandler.mouseMoved( x, y );
}

//--------------------------------------------------------------
void CPP::mouseDragged( int x, int y, int button )
{
	m_stateHandler.mouseDragged( x, y, button );
}

//--------------------------------------------------------------
void CPP::mousePressed( int x, int y, int button )
{
	m_stateHandler.mousePressed( x, y, button );
}

//--------------------------------------------------------------
void CPP::mouseReleased( int x, int y, int button )
{
	m_stateHandler.mouseReleased( x, y, button );
}

//--------------------------------------------------------------
void CPP::windowResized( int w, int h )
{
	m_stateHandler.windowResized( w, h );
}

//--------------------------------------------------------------
void CPP::gotMessage( ofMessage msg )
{
	m_stateHandler.gotMessage( msg );
}

//--------------------------------------------------------------
void CPP::dragEvent( ofDragInfo dragInfo )
{ 
	m_stateHandler.dragEvent( dragInfo );
}

void CPP::setWorld( BaseWorld* newWorld )
{
	m_stateHandler.changeWorld( newWorld );
}

void CPP::setWidth( unsigned int width )
{
	m_width = width;
	m_halfWidth = width / 2.0;
}

void CPP::setHeight( unsigned int height )
{
	m_height = height;
	m_halfHeight = height / 2.0;
}

void CPP::setFrameRate( unsigned int frameRate )
{
	m_frameRate = frameRate;
	ofSetFrameRate( frameRate );
}