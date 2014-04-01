#include "CPPBaseWorld.h"

CPPBaseWorld::CPPBaseWorld()
{
}


CPPBaseWorld::~CPPBaseWorld()
{
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		delete *i;
	}	
}

void CPPBaseWorld::setup()
{
}

void CPPBaseWorld::update()
{
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		( *i )->update();
	}
}

void CPPBaseWorld::draw()
{
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		( *i )->draw();
	}
}

void CPPBaseWorld::keyPressed( int key )
{
}

void CPPBaseWorld::keyReleased( int key )
{
}

void CPPBaseWorld::mouseMoved( int x, int y )
{
}

void CPPBaseWorld::mouseDragged( int x, int y, int button )
{
}

void CPPBaseWorld::mousePressed( int x, int y, int button )
{
}

void CPPBaseWorld::mouseReleased( int x, int y, int button )
{
}

void CPPBaseWorld::windowResized( int w, int h )
{
}

void CPPBaseWorld::dragEvent( ofDragInfo dragInfo )
{
}

void CPPBaseWorld::gotMessage( ofMessage msg )
{
}

void CPPBaseWorld::addEntity( CPPBaseEntity* entity, bool quiet/* = false*/ )
{
	if ( m_entities.insert( entity ).second == false )
	{
		std::cout << "ERROR: the entity is already in this World." << std::endl;
		return;
	}

	entity->setWorld( this );

	if ( !quiet )
	{
		entity->added();
	}
}

CPPBaseEntity* CPPBaseWorld::removeEntity( CPPBaseEntity* entity, bool quiet/* = false*/ )
{
	if ( m_entities.erase( entity ) != 1 )
	{
		std::cout << "ERROR: this Entity is not in this World." << std::endl;
		return NULL;
	}

	entity->setWorld( NULL );

	if ( !quiet )
	{
		entity->removed();
	}

	return entity;
}

void CPPBaseWorld::updateEntityLayer( CPPBaseEntity* entity, int layer )
{
	if ( m_entities.erase( entity ) != 1 )
	{
		std::cout << "ERROR: this Entity is not in this World." << std::endl;
		return;
	}

	entity->setWorld( NULL );
	entity->setLayer( layer );
	entity->setWorld( this );
	m_entities.insert( entity );
}

CPPBaseEntity* CPPBaseWorld::collideRect( BaseEntityTypes::id type, float rX, float rY, float rWidth, float rHeight, const CPPBaseEntity* except/* = NULL*/ ) const
{
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		CPPBaseEntity* const e = ( *i );

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

void CPPBaseWorld::collideRectInto( BaseEntityTypes::id type, float rX, float rY, float rWidth, float rHeight, std::vector< CPPBaseEntity* >& into, const CPPBaseEntity* except/* = NULL*/ ) const
{
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		CPPBaseEntity* const e = ( *i );

		if ( e->getType() == type )
		{
			if ( e->isCollidable() && e->collideRect( e->getPosX(), e->getPosY(), rX, rY, rWidth, rHeight ) )
			{
				if ( except )
				{
					if ( e != except )
					{
						into.push_back( e );
					}
				}
				else
				{
					into.push_back( e );
				}
			}
		}
	}
}
