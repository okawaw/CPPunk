#ifndef CPP_H_
#define CPP_H_

#include "ofBaseApp.h"

#include "CPPStateHandler.h"
#include "CPPBaseWorld.h"
#include "utils/CPPKey.h"

#include "ofCamera.h"
#include "ofImage.h"

#include <string>

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
}

class CPP : public ofBaseApp
{
private:
	friend class CPPBitmapData;

	class CPPResourceManager
	{
	public:
		CPPResourceManager();
		~CPPResourceManager();

		ofImage* useTexture( const std::string& key );
		void releaseTexture( const std::string& key );

		// < resourceName, < ofImagePointer, retainCount > >
		std::map< std::string, std::pair< ofImage*, unsigned int > > m_dataMap;
		ofImage* m_pErrorTexture;
	};

public:
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
	static CPPKeys::id getKeyID( int key );

	static bool ms_bPaused;                            // If the game should stop updating/rendering.

	static bool ms_bFixed;                             // If the game is running at a fixed framerate.
	static bool ms_bTimeInFrames;                      // If times should be given in frames (as opposed to seconds).
	                                                   // Default is true in fixed timestep mode and false in variable timestep mode.

	static unsigned int ms_width;                      // Width of the game.
	static unsigned int ms_height;                     // Height of the game.
	static float ms_halfWidth;                         // Half width of the game.
	static float ms_halfHeight;                        // Half height of the game.

	static unsigned int ms_assignedFrameRate;          // Desired frame rate of the game.

	static CPPResourceManager ms_resourceManager;      // ResourceManager for the game.

	static CPPStateHandler ms_stateHandler;            // StateHandler for the game.

	static ofCamera ms_camera;                         // Camera for the game.
};

#endif
