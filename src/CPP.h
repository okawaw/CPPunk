#ifndef CPP_H_
#define CPP_H_

#include "ofBaseApp.h"

#include "ofCamera.h"

#include <string> // CPPUtil
#include <vector> // CPPUtil

class CPPBaseWorld;

namespace CPPUtil
{
	float distance( float x1, float y1, float x2, float y2 );
	float distanceRects( float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2 );

	// Find the distance between a point and a rectangle. Returns 0 if the point is within the rectangle.
	float distanceRectPoint( float pX, float pY, float rX, float rY, float rW, float rH );

	// Compute the resulting RGBA pixel of pixel 1 over pixel 2 with the result
	// stored in the components of res.
	void alphaOver( unsigned char r1, unsigned char g1, unsigned char b1, unsigned char a1,
	                unsigned char r2, unsigned char g2, unsigned char b2, unsigned char a2,
	                unsigned char& resR, unsigned char& resG, unsigned char& resB, unsigned char& resA );

	void split( const std::string& s, char delimiter, std::vector< std::string >& elements );

	float trunc( float f );
}

// TODO: Make the CPP class a singleton with an "instance" that is
//       invoked when static calls are made. No static members are
//       necessary.

class CPP : public ofBaseApp
{
public:
	static void initialize();  // TODO: add CPPEngine functionality
	static CPP* getInstance(); // TODO: remove

public:
	CPP();
	~CPP();

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

	static CPPBaseWorld* getWorld();
	static void setWorld( CPPBaseWorld* newWorld );

	static bool getPaused();
	static void setPaused( const bool paused );

	static bool getFixed();
	static void setFixed( const bool fixed );

	static bool getTimeInFrames();
	static void setTimeInFrames( const bool timeInFrames );

	static unsigned int getWidth();
	static unsigned int getHeight();
	static float getHalfWidth();
	static float getHalfHeight();
	static void setWidth( unsigned int width );
	static void setHeight( unsigned int height );

	static unsigned int getAssignedFrameRate();
	static void setAssignedFrameRate( unsigned int frameRate );
	static float getFrameRate();

	// Time elapsed since the last frame (in seconds).
	static double getElapsed();

	static float getCameraX();
	static float getCameraY();
	static void setCameraX( float x );
	static void setCameraY( float y );
	static void setCameraPos( float x, float y );

private:
	static bool ms_bPaused;                            // If the game should stop updating/rendering.

	static bool ms_bFixed;                             // If the game is running at a fixed framerate.
	static bool ms_bTimeInFrames;                      // If times should be given in frames (as opposed to seconds).
	                                                   // Default is true in fixed timestep mode and false in variable timestep mode.

	static unsigned int ms_width;                      // Width of the game.
	static unsigned int ms_height;                     // Height of the game.
	static float ms_halfWidth;                         // Half width of the game.
	static float ms_halfHeight;                        // Half height of the game.

	static unsigned int ms_assignedFrameRate;          // Desired frame rate of the game.

	//static CPPStateHandler ms_stateHandler;            // StateHandler for the game. TODO: should be absorbed by CPP.

	static ofCamera ms_camera;                         // Camera for the game.

	static CPP* ms_pInstance;

	CPP( const CPP& );
	CPP& operator=( const CPP& );
};

#endif
