#ifndef CPP_H_
#define CPP_H_

#include "ofBaseApp.h"

#include "CPPStateHandler.h"
#include "CPPBaseWorld.h"
#include "utils/CPPKey.h"

#include "ofCamera.h"

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



	static void setWorld( CPPBaseWorld* newWorld );

	static unsigned int getWidth();
	static unsigned int getHeight();
	static float getHalfWidth();
	static float getHalfHeight();
	static void setWidth( unsigned int width );
	static void setHeight( unsigned int height );

	static void setFrameRate( unsigned int frameRate );

	static float getCameraX();
	static float getCameraY();
	static void setCameraX( float x );
	static void setCameraY( float y );
	static void setCameraPos( float x, float y );

	static float distance( float x1, float y1, float x2, float y2 );
	static float distanceRects( float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2 );

	// Find the distance between a point and a rectangle. Returns 0 if the point is within the rectangle.
	static float distanceRectPoint( float pX, float pY, float rX, float rY, float rW, float rH );

private:
	static CPPKeys::id getKeyID( int key );

	static unsigned int ms_width;                      // Width of the game.
	static unsigned int ms_height;                     // Height of the game.
	static float ms_halfWidth;                         // Half width of the game.
	static float ms_halfHeight;                        // Half height of the game.

	static unsigned int ms_frameRate;                  // Desired frame rate of the game.

	static CPPStateHandler ms_stateHandler;            // StateHandler for the game.

	static ofCamera ms_camera;                         // Camera for the game.
};

#endif
