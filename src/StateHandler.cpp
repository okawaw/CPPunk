#include "StateHandler.h"

//#include "Globals.h"
//#include "Game.h"
//#include "GameState.h"
//#include "TitleState.h"

StateHandler::StateHandler() :
  m_pCurWorld( 0 )
{
	// title World is first World to load
	//m_pCurState = new TitleState();
}

StateHandler::~StateHandler()
{
	delete m_pCurWorld;
}

// Changes World to a brand new object.
void StateHandler::changeWorld( BaseWorld* newWorld )
{
	delete m_pCurWorld;
	m_pCurWorld = newWorld;
	m_pCurWorld->setup();
}

// All callbacks.

// TODO: Not necessary?
void StateHandler::setup()
{
}

void StateHandler::update()
{
	// game state update loop
	if ( m_pCurWorld )
	{
		m_pCurWorld->update();
	}
}

void StateHandler::draw()
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->draw();
	}
}

void StateHandler::keyPressed( int key )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->keyPressed( key );
	}
}

void StateHandler::keyReleased( int key )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->keyReleased( key );
	}
}

void StateHandler::mouseMoved( int x, int y )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->mouseMoved( x, y );
	}
}

void StateHandler::mouseDragged( int x, int y, int button )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->mouseDragged( x, y, button );
	}
}

void StateHandler::mousePressed( int x, int y, int button )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->mousePressed( x, y, button );
	}
}

void StateHandler::mouseReleased( int x, int y, int button )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->mouseReleased( x, y, button );
	}
}

void StateHandler::windowResized( int w, int h )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->windowResized( w, h );
	}
}

void StateHandler::dragEvent( ofDragInfo dragInfo )
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->dragEvent( dragInfo );
	}
}

void StateHandler::gotMessage( ofMessage msg )
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
