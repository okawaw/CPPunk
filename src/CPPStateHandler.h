#ifndef CPP_STATE_HANDLER_H_
#define CPP_STATE_HANDLER_H_

#include "CPPBaseWorld.h"
//#include "GameState.h"
//#include "StateDefs.h"

#include "ofEvents.h"

class CPPStateHandler
{
public:
	CPPStateHandler();
	~CPPStateHandler();

	CPPBaseWorld* getWorld() const;
	void setWorld( CPPBaseWorld* const newWorld );

	// changes state and frees memory                       // TODO: REMOVE
	//void changeWorld( CPPBaseWorld* newWorld );

	// Callback functions
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

private:
	void checkWorld();

	/*static*/ CPPBaseWorld* m_pCurWorld;      // Current World object pointer.

	CPPBaseWorld* m_pGoto;                     // World to switch to.
};

#endif
