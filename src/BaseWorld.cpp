#include "BaseWorld.h"

BaseWorld::BaseWorld()
{
}


BaseWorld::~BaseWorld()
{
	for ( std::set< BaseEntity*, BaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		delete *i;
	}	
}

void BaseWorld::setup()
{
}

void BaseWorld::update()
{
	for ( std::set< BaseEntity*, BaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		( *i )->update();
	}
}

void BaseWorld::draw()
{
	for ( std::set< BaseEntity*, BaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		( *i )->draw();
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

void BaseWorld::addEntity( BaseEntity* entity, bool quiet/* = false*/ )
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

BaseEntity* BaseWorld::removeEntity( BaseEntity* entity, bool quiet/* = false*/ )
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

void BaseWorld::updateEntityLayer( BaseEntity* entity, int layer )
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

BaseEntity* BaseWorld::collideRect( BaseEntityTypes::id type, float rX, float rY, float rWidth, float rHeight, const BaseEntity* except/* = NULL*/ ) const
{
	for ( std::set< BaseEntity*, BaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		BaseEntity* const e = ( *i );

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

void BaseWorld::collideRectInto( BaseEntityTypes::id type, float rX, float rY, float rWidth, float rHeight, std::vector< BaseEntity* >& into, const BaseEntity* except/* = NULL*/ ) const
{
	for ( std::set< BaseEntity*, BaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		BaseEntity* const e = ( *i );

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
