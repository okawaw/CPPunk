#include "CPPStateHandler.h"

//#include "Globals.h"
//#include "Game.h"
//#include "GameState.h"
//#include "TitleState.h"

CPPStateHandler::CPPStateHandler() :
  m_pCurWorld( 0 )
{
	// title World is first World to load
	//m_pCurState = new TitleState();
}

CPPStateHandler::~CPPStateHandler()
{
	delete m_pCurWorld;
}

// Changes World to a brand new object.
void CPPStateHandler::changeWorld( CPPBaseWorld* newWorld )
{
	delete m_pCurWorld;
	m_pCurWorld = newWorld;
	m_pCurWorld->setup();
}

// All callbacks.

// TODO: Not necessary?
void CPPStateHandler::setup()
{
}

void CPPStateHandler::update()
{
	// game state update loop
	if ( m_pCurWorld )
	{
		m_pCurWorld->update();
	}
}

void CPPStateHandler::draw()
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->draw();
	}
}

void CPPStateHandler::keyPressed( int key )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->keyPressed( key );
	}
}

void CPPStateHandler::keyReleased( int key )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->keyReleased( key );
	}
}

void CPPStateHandler::mouseMoved( int x, int y )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->mouseMoved( x, y );
	}
}

void CPPStateHandler::mouseDragged( int x, int y, int button )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->mouseDragged( x, y, button );
	}
}

void CPPStateHandler::mousePressed( int x, int y, int button )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->mousePressed( x, y, button );
	}
}

void CPPStateHandler::mouseReleased( int x, int y, int button )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->mouseReleased( x, y, button );
	}
}

void CPPStateHandler::windowResized( int w, int h )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->windowResized( w, h );
	}
}

void CPPStateHandler::dragEvent( ofDragInfo dragInfo )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->dragEvent( dragInfo );
	}
}

void CPPStateHandler::gotMessage( ofMessage msg )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->gotMessage( msg );
	}
}

/*
void StateHandler::resize( int width, int height )
{
	// set window size
	game->getCamera()->setWindowWidth( width );
	game->getCamera()->setWindowHeight( height );

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
	glFrustum(
		-game->getCamera()->getFrustumHalfWidth(),
		game->getCamera()->getFrustumHalfWidth(),
		-game->getCamera()->getFrustumHalfHeight(),
		game->getCamera()->getFrustumHalfHeight(),
		game->getCamera()->getFrustumNear(),
		game->getCamera()->getFrustumFar());

    glMatrixMode(GL_MODELVIEW);
}

void StateHandler::mouseMotion( int x, int y )
{
	m_pCurState->mouseMotion( x, y );
}
*/
