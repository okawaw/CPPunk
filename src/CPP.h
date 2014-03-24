#ifndef CPP_H
#define CPP_H

#include "ofBaseApp.h"

#include "StateHandler.h"
#include "BaseWorld.h"

#include <string>

class CPP : public ofBaseApp
{
public:
	CPP();

	void setup();
	void update();
	void draw();

	void keyPressed( int key );
	void keyReleased( int key );
	void mouseMoved( int x, int y );
	void mouseDragged( int x, int y, int button );
	void mousePressed( int x, int y, int button );
	void mouseReleased( int x, int y, int button );
	void windowResized( int w, int h );
	void dragEvent( ofDragInfo dragInfo );
	void gotMessage( ofMessage msg );



	static void setWorld( BaseWorld* newWorld );
	static void setWidth( unsigned int width );
	static void setHeight( unsigned int height );

	static void setFrameRate( unsigned int frameRate );

private:
	static unsigned int m_width;                      // Width of the game.
	static unsigned int m_height;                     // Height of the game.
	static float m_halfWidth;                         // Half width of the game.
	static float m_halfHeight;                        // Half height of the game.

	static unsigned int m_frameRate;                  // Desired frame rate of the game.

	static StateHandler m_stateHandler;               // StateHandler for the game.
};

#endif
