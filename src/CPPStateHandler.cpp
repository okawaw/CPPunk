#include "CPPStateHandler.h"

#include "CPPBaseWorld.h"

#include <stdlib.h>

CPPStateHandler* CPPStateHandler::ms_pInstance = NULL;

CPPStateHandler::CPPStateHandler() :
  m_pCurWorld( NULL )
, m_pGoto( NULL )
{
}

CPPStateHandler::~CPPStateHandler()
{
	if ( m_pCurWorld && m_pCurWorld->isAutoCleanup() )
	{
		delete m_pCurWorld;
	}
}

void CPPStateHandler::initialize()
{
	if ( !ms_pInstance )
	{
		ms_pInstance = new CPPStateHandler();
	}
}

void CPPStateHandler::destroy()
{
	delete ms_pInstance;
	ms_pInstance = NULL;
}

CPPStateHandler* CPPStateHandler::getInstance()
{
	return ms_pInstance;
}

CPPBaseWorld* CPPStateHandler::getWorld() const { return m_pCurWorld; }
void CPPStateHandler::setWorld( CPPBaseWorld* const newWorld )
{
	// ms_stateHandler.changeWorld( newWorld );       // old         TODO: REMOVE
	if ( m_pGoto )
	{
		if ( m_pGoto == newWorld )
		{
			return;
		}
	}
	else
	{
		if ( m_pCurWorld == newWorld )
		{
			return;
		}
	}

	m_pGoto = newWorld;
}

/*                                                                      TODO: REMOVE
// Changes World to a brand new object.
void CPPStateHandler::changeWorld( CPPBaseWorld* newWorld )
{
	// TODO: change worlds at the end of the frame.
	// TODO: make cleanup optional.
	delete m_pCurWorld;
	m_pCurWorld = newWorld;
	m_pCurWorld->setup();
}
*/

// All callbacks.

// TODO: Not necessary?
void CPPStateHandler::setup()
{
}

void CPPStateHandler::update()
{
	if ( m_pCurWorld )
	{
		m_pCurWorld->updateLists();
	}

	if ( m_pGoto )
	{
		checkWorld();
	}

	if ( m_pCurWorld )
	{
		if ( m_pCurWorld->isActive() )
		{
			m_pCurWorld->update();
		}

		m_pCurWorld->updateLists( false );
	}
}

void CPPStateHandler::draw()
{
	if ( m_pCurWorld )
	{
		if ( m_pCurWorld->isVisible() )
		{
			m_pCurWorld->draw();
		}
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

void CPPStateHandler::checkWorld()
{
	if ( !m_pGoto )
	{
		return;
	}

	if ( m_pCurWorld )
	{
		m_pCurWorld->end();
		m_pCurWorld->updateLists();

		if ( m_pCurWorld->isAutoCleanup() )
		{
			delete m_pCurWorld;
		}
	}

	m_pCurWorld = m_pGoto;
	m_pGoto = NULL;

	m_pCurWorld->updateLists();                              // TODO: NULL check?
	m_pCurWorld->begin();
	m_pCurWorld->setup();
	m_pCurWorld->updateLists();
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
