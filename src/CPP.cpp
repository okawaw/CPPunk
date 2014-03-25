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
// TODO: Write squareDistance
float CPP::distance( float x1, float y1, float x2, float y2 )
{
	return sqrt( ( x2 - x1 ) * ( x2 - x1 ) + ( y2 - y1 ) * ( y2 - y1 ) );
}

float CPP::distanceRects( float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2 )
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
			return distance( x1, y1, ( x2 + w2 ), ( y2 + h2 ) );
		}
		return distance( x1, y1 + h1, x2 + w2, y2 );
	}
	if ( y1 > y2 )
	{
		return distance( x1 + w1, y1, x2, y2 + h2 );
	}
	return distance( x1 + w1, y1 + h1, x2, y2 );
}

float CPP::distanceRectPoint( float pX, float pY, float rX, float rY, float rW, float rH )
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
			return distance( pX, pY, rX + rW, rY + rH );
		}
		return distance( pX, pY, rX + rW, rY );
	}
	if ( pY > rY )
	{
		return distance( pX, pY, rX, rY + rH );
	}
	return distance( pX, pY, rX, rY );
}
