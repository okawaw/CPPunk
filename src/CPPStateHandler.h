#ifndef CPP_STATE_HANDLER_H_
#define CPP_STATE_HANDLER_H_

#include "ofEvents.h"

class CPPBaseWorld;

class CPPStateHandler // TODO: Make it a private class of CPP
{
	friend class CPP; // TODO: ACTUALLY ^^ Make it a private class (maybe not a singleton anymore) that only CPP can create and own. Then make CPP a singleton. No more static functions or variables. Or remove entirely.
private:
	CPPStateHandler();
	~CPPStateHandler();

	static void initialize();
	static void destroy();
	static CPPStateHandler* getInstance();

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

	void checkWorld();

	CPPBaseWorld* m_pCurWorld;                 // Current World object pointer.
	CPPBaseWorld* m_pGoto;                     // World to switch to.

	static CPPStateHandler* ms_pInstance;

	CPPStateHandler( const CPPStateHandler& );
	CPPStateHandler& operator=( const CPPStateHandler& );
};

#endif
