#include "BaseWorld.h"

BaseWorld::BaseWorld()
{
}


BaseWorld::~BaseWorld()
{
	for ( unsigned int i = 0; i < m_entities.size(); ++i )
	{
		delete m_entities[ i ];
	}
}

void BaseWorld::setup()
{
}

void BaseWorld::update()
{
	for ( unsigned int i = 0; i < m_entities.size(); ++i )
	{
		m_entities[ i ]->update();
	}
}

void BaseWorld::draw()
{
	for ( unsigned int i = 0; i < m_entities.size(); ++i )
	{
		m_entities[ i ]->draw();
	}
}

void BaseWorld::keyPressed( int key )
{
}

void BaseWorld::keyReleased( int key )
{
}

void BaseWorld::mouseMoved( int x, int y )
{
}

void BaseWorld::mouseDragged( int x, int y, int button )
{
}

void BaseWorld::mousePressed( int x, int y, int button )
{
}

void BaseWorld::mouseReleased( int x, int y, int button )
{
}

void BaseWorld::windowResized( int w, int h )
{
}

void BaseWorld::dragEvent( ofDragInfo dragInfo )
{
}

void BaseWorld::gotMessage( ofMessage msg )
{
}

void BaseWorld::addEntity( BaseEntity* entity )
{
	m_entities.push_back( entity );
	entity->setWorld( this );
	entity->added();
}

BaseEntity* BaseWorld::collideRect( BaseEntityTypes::id type, float rX, float rY, float rWidth, float rHeight, BaseEntity* except/* = NULL*/ )
{
	for ( unsigned int i = 0; i < m_entities.size(); ++i )
	{
		BaseEntity* const e = m_entities[ i ];

		if ( e->getType() == type )
		{
			if ( e->isCollidable() && e->collideRect( e->getPosX(), e->getPosY(), rX, rY, rWidth, rHeight ) )
			{
				if ( except )
				{
					if ( e != except )
					{
						return e;
					}
				}
				else
				{
					return e;
				}
			}
		}
	}
	return NULL;
}

void BaseWorld::collideRectInto( BaseEntityTypes::id type, float rX, float rY, float rWidth, float rHeight, std::vector< BaseEntity* > into )
{
	for ( unsigned int i = 0; i < m_entities.size(); ++i )
	{
		BaseEntity* const e = m_entities[ i ];

		if ( e->getType() == type )
		{
			if ( e->isCollidable() && e->collideRect( e->getPosX(), e->getPosY(), rX, rY, rWidth, rHeight ) )
			{
				into.push_back( e );
			}
		}
	}
}
