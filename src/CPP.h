#ifndef CPP_H_
#define CPP_H_

#include "ofBaseApp.h"

#include "CPPStateHandler.h"
#include "CPPBaseWorld.h"
#include "utils/CPPKey.h"

#include "ofCamera.h"
#include "ofTexture.h"

#include <string>

class CPP : public ofBaseApp
{
private:
	class CPPResourceManager
	{
	public:
		CPPResourceManager();
		~CPPResourceManager();

		ofTexture* useTexture( const std::string& key );
		void releaseTexture( const std::string& key );

		// < resourceName, < ofTexturePointer, retainCount > >
		std::map< std::string, std::pair< ofTexture*, unsigned int > > m_dataMap;
		ofTexture* m_pErrorTexture;
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

	static ofTexture* getTexture( const std::string& filename );
	static void releaseTexture( const std::string& filename );

	static CPPBaseWorld* getWorld();
	static void setWorld( CPPBaseWorld* newWorld );

	static bool getPaused();
	static void setPaused( const bool paused );

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

	static float distance( float x1, float y1, float x2, float y2 );
	static float distanceRects( float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2 );

	// Find the distance between a point and a rectangle. Returns 0 if the point is within the rectangle.
	static float distanceRectPoint( float pX, float pY, float rX, float rY, float rW, float rH );

private:
	static CPPKeys::id getKeyID( int key );

	static bool ms_bPaused;                            // If the game should stop updating/rendering.

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
