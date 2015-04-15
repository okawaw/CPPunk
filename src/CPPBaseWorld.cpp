#include "CPPBaseWorld.h"

#include "CPP.h"

#include <algorithm>
#include <float.h>
#include <iostream>
#include <stdlib.h>

// Calculates the squared distance between two rectangles.
static float squareRects( float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2 );
// Calculates the squared distance between two points.
static float squarePoints( float x1, float y1, float x2, float y2 );
// Calculates the squared distance between a rectangle and a point.
static float squarePointRect( float px, float py, float rx, float ry, float rw, float rh );

CPPBaseEntity::EntityKey CPPBaseWorld::m_entityKey;

bool CPPBaseWorld::isActive() const { return m_bActive; }
void CPPBaseWorld::setActive( const bool active ) { m_bActive = active; }

bool CPPBaseWorld::isVisible() const { return m_bVisible; }
void CPPBaseWorld::setVisible( const bool visible ) { m_bVisible = visible; }

CPPBaseWorld::CPPBaseWorld( bool autoCleanup/* = false */ ) :
  m_bActive( true )
, m_bVisible( true )
, m_bAutoCleanup( autoCleanup )
{
}

CPPBaseWorld::~CPPBaseWorld()
{
	// Will clean up all Entities in the World at destruction that are flagged for auto cleanup.
	// If the entities shouldn't be destroyed, they should be removed beforehand.
	// Statically allocated Entities will always be cleaned up, but if Entities are dynamically
	// allocated and not flagged for auto cleanup, they should be cleaned up somewhere else.
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		if ( ( *i )->isAutoCleanup() )
		{
			delete *i;
		}
	}	
}

void CPPBaseWorld::begin()
{
}

void CPPBaseWorld::end()
{
}

void CPPBaseWorld::setup()
{
}

void CPPBaseWorld::update()
{
	// Update all the entities.
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		// If they are inactive, do nothing.
		if ( ( *i )->isActive() )
		{
			( *i )->update();
		}
		// Update the Graphic if it is active.
		if ( ( *i )->getGraphic() && ( *i )->getGraphic()->isActive() )
		{
			( *i )->getGraphic()->update();
		}
	}
}

void CPPBaseWorld::draw()
{
	// Render the Entities in order of depth.
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		if ( ( *i )->isVisible() )
		{
			( *i )->draw();
		}
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

bool CPPBaseWorld::isAutoCleanup() const { return m_bAutoCleanup; }

void CPPBaseWorld::updateEntityLayer( CPPBaseEntity* entity, int layer )
{
	if ( m_entities.erase( entity ) != 1 )
	{
		std::cerr << "ERROR: this Entity is not in this World." << std::endl;
		return;
	}

	entity->setWorld( NULL, m_entityKey );
	entity->setLayer( layer );
	entity->setWorld( this, m_entityKey );
	m_entities.insert( entity );
}

CPPBaseEntity* CPPBaseWorld::add( CPPBaseEntity* e )
{
	m_add.push_back( e );
	return e;
}

CPPBaseEntity* CPPBaseWorld::remove( CPPBaseEntity* e )
{
	m_remove.push_back( e );
	return e;
}

void CPPBaseWorld::removeAll()
{
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		m_remove.push_back( *i );
	}
}

void CPPBaseWorld::addList( std::vector< CPPBaseEntity* >& list )
{
	for ( std::vector< CPPBaseEntity* >::const_iterator i = list.begin(); i != list.end(); ++i )
	{
		add( *i );
	}
}

void CPPBaseWorld::removeList( std::vector< CPPBaseEntity* >& list )
{
	for ( std::vector< CPPBaseEntity* >::const_iterator i = list.begin(); i != list.end(); ++i )
	{
		remove( *i );
	}
}

CPPBaseEntity* CPPBaseWorld::collideRect( unsigned int type, float rX, float rY, float rWidth, float rHeight, const CPPBaseEntity* except/* = NULL*/ ) const
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

CPPBaseEntity* CPPBaseWorld::collidePoint( unsigned int type, float pX, float pY, const CPPBaseEntity* except/* = NULL*/ ) const
{
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		CPPBaseEntity* e = ( *i );

		if ( e->getType() == type )
		{
			if ( e->isCollidable() && e->collidePoint( e->getPosX(), e->getPosY(), pX, pY ) )
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

CPPBaseEntity* CPPBaseWorld::collideLine( unsigned int type, int fromX, int fromY, int toX, int toY, int& pX, int& pY, unsigned int precision/* = 1*/, const CPPBaseEntity* except/* = NULL*/ ) const
{
	// If the distance is less than precision, do the short sweep.
	if ( precision < 1 )
	{
		precision = 1;
	}
	if ( CPPUtil::distance( fromX, fromY, toX, toY ) < precision )
	{
		if ( fromX == toX && fromY == toY )
		{
			pX = toX;
			pY = toY;
			return collidePoint( type, toX, toY, except );
		}
		return collideLine( type, fromX, fromY, toX, toY, pX, pY, 1, except );
	}

	// Get information about the line we're about to raycast.
	int xDelta = std::abs( toX - fromX );
	int yDelta = std::abs( toY - fromY );
	float xSign = ( toX > fromX ) ? precision : -( ( int )precision );
	float ySign = ( toY > fromY ) ? precision : -( ( int )precision );
	float x = fromX;
	float y = fromY;
	CPPBaseEntity* e;

	// Do a raycast from the start point to the end point.
	if ( xDelta > yDelta )
	{
		ySign *= yDelta / xDelta;

		if ( xSign > 0 )
		{
			while ( x < toX )
			{
				if ( ( e = collidePoint( type, x, y, except ) ) ) // This function's scope does not worry about except, the other functions handle it.
				{
					if ( precision < 2 )
					{
						pX = x - xSign;
						pY = y - ySign;

						return e;
					}
					return collideLine( type, x - xSign, y - ySign, toX, toY, pX, pY, 1, except );
				}
				x += xSign;
				y += ySign;
			}
		}
		else
		{
			while ( x > toX )
			{
				if ( ( e = collidePoint( type, x, y, except ) ) ) // This function's scope does not worry about except, the other functions handle it.
				{
					if ( precision < 2 )
					{
						pX = x - xSign;
						pY = y - ySign;

						return e;
					}
					return collideLine( type, x - xSign, y - ySign, toX, toY, pX, pY, 1, except );
				}
				x += xSign;
				y += ySign;
			}
		}
	}
	else
	{
		xSign *= xDelta / yDelta;

		if ( ySign > 0 )
		{
			while ( y < toY )
			{
				if ( ( e = collidePoint( type, x, y, except ) ) ) // This function's scope does not worry about except, the other functions handle it.
				{
					if ( precision < 2 )
					{
						pX = x - xSign;
						pY = y - ySign;

						return e;
					}
					return collideLine( type, x - xSign, y - ySign, toX, toY, pX, pY, 1, except );
				}
				x += xSign;
				y += ySign;
			}
		}
		else
		{
			while ( y > toY )
			{
				if ( ( e = collidePoint( type, x, y, except ) ) ) // This function's scope does not worry about except, the other functions handle it.
				{
					if ( precision < 2 )
					{
						pX = x - xSign;
						pY = y - ySign;

						return e;
					}
					return collideLine( type, x - xSign, y - ySign, toX, toY, pX, pY, 1, except );
				}
				x += xSign;
				y += ySign;
			}
		}
	}

	// Check the last position.
	if ( precision > 1 )
	{
		if ( collidePoint( type, toX, toY, except ) )
		{
			return collideLine( type, x - xSign, y - ySign, toX, toY, pX, pY, 1, except );
		}
	}

	// No collision, return the end point.
	pX = toX;
	pY = toY;

	return NULL;
}

CPPBaseEntity* CPPBaseWorld::collideLine( unsigned int type, int fromX, int fromY, int toX, int toY, unsigned int precision/* = 1*/, const CPPBaseEntity* except/* = NULL*/ ) const
{
	// If the distance is less than precision, do the short sweep.
	if ( precision < 1 )
	{
		precision = 1;
	}
	if ( CPPUtil::distance( fromX, fromY, toX, toY ) < precision )
	{
		return collidePoint( type, fromX, toY, except );
	}

	// Get information about the line we're about to raycast.
	int xDelta = std::abs( toX - fromX );
	int yDelta = std::abs( toY - fromY );

	float xSign = ( toX > fromX ) ? precision : -( ( int )precision );
	float ySign = ( toY > fromY ) ? precision : -( ( int )precision );
	float x = fromX;
	float y = fromY;
	CPPBaseEntity* e;

	// Do a raycast from the start point to the end point.
	if ( xDelta > yDelta )
	{
		ySign *= yDelta / xDelta;

		if ( xSign > 0 )
		{
			while ( x < toX )
			{
				if ( ( e = collidePoint( type, x, y, except ) ) ) // This function's scope does not worry about except, the other functions handle it.
				{
					return e;
				}
				x += xSign;
				y += ySign;
			}
		}
		else
		{
			while ( x > toX )
			{
				if ( ( e = collidePoint( type, x, y, except ) ) ) // This function's scope does not worry about except, the other functions handle it.
				{
					return e;
				}
				x += xSign;
				y += ySign;
			}
		}
	}
	else
	{
		xSign *= xDelta / yDelta;

		if ( ySign > 0 )
		{
			while ( y < toY )
			{
				if ( ( e = collidePoint( type, x, y, except ) ) ) // This function's scope does not worry about except, the other functions handle it.
				{
					return e;
				}
				x += xSign;
				y += ySign;
			}
		}
		else
		{
			while ( y > toY )
			{
				if ( ( e = collidePoint( type, x, y, except ) ) ) // This function's scope does not worry about except, the other functions handle it.
				{
					return e;
				}
				x += xSign;
				y += ySign;
			}
		}
	}

	// Check the last position.
	if ( precision > 1 )
	{
		return collidePoint( type, toX, toY, except );
	}

	// No collision, return null.
	return NULL;
}

void CPPBaseWorld::collideRectInto( unsigned int type, float rX, float rY, float rWidth, float rHeight, std::vector< CPPBaseEntity* >& into, const CPPBaseEntity* except/* = NULL*/ ) const
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

void CPPBaseWorld::collidePointInto( unsigned int type, float pX, float pY, std::vector< CPPBaseEntity* >& into, const CPPBaseEntity* except/* = NULL*/ ) const
{
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		CPPBaseEntity* const e = ( *i );

		if ( e->getType() == type )
		{
			if ( e->isCollidable() && e->collidePoint( e->getPosX(), e->getPosY(), pX, pY ) )
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

CPPBaseEntity* CPPBaseWorld::nearestToRect( unsigned int type, float x, float y, float width, float height, const CPPBaseEntity* except/* = NULL*/ ) const
{
	float nearDist = FLT_MAX;
	float dist;
	CPPBaseEntity* n = NULL;

	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		CPPBaseEntity* const e = ( *i );

		if ( e->getType() == type )
		{
			if ( except )
			{
				if ( e != except )
				{
					dist = squareRects( x, y, width, height, e->getPosX() - e->getOriginX(), e->getPosY() - e->getOriginY(), e->getWidth(), e->getHeight() );
				
					if ( dist < nearDist )
					{
						nearDist = dist;
						n = e;
					}
				}
			}
			else
			{
				dist = squareRects( x, y, width, height, e->getPosX() - e->getOriginX(), e->getPosY() - e->getOriginY(), e->getWidth(), e->getHeight() );

				if ( dist < nearDist )
				{
					nearDist = dist;
					n = e;
				}
			}
		}
	}
	return n;
}

CPPBaseEntity* CPPBaseWorld::nearestToEntity( unsigned int type, const CPPBaseEntity* e, bool useHitboxes/* = false*/, CPPBaseEntity* except/* = NULL*/ ) const
{
	if ( useHitboxes )
	{
		return nearestToRect( type, e->getPosX() - e->getOriginX(), e->getPosY() - e->getOriginY(), e->getWidth(), e->getHeight(), e );
	}

	float nearDist = FLT_MAX;
	float dist;
	float x = e->getPosX() - e->getOriginX();
	float y = e->getPosY() - e->getOriginY();
	CPPBaseEntity* n = NULL;

	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		CPPBaseEntity* const en = ( *i );

		if ( en->getType() == type )
		{
			if ( en != e )
			{
				if ( except )
				{
					if ( en != except )
					{
						dist = ( x - en->getPosX() ) * (x - en->getPosX() ) + ( y - en->getPosY() ) * ( y - en->getPosY() );
				
						if ( dist < nearDist )
						{
							nearDist = dist;
							n = en;
						}
					}
				}
				else
				{
					dist = ( x - en->getPosX() ) * (x - en->getPosX() ) + ( y - en->getPosY() ) * ( y - en->getPosY() );
				
					if ( dist < nearDist )
					{
						nearDist = dist;
						n = en;
					}
				}
			}
		}
	}
	return n;
}

CPPBaseEntity* CPPBaseWorld::nearestToPoint( unsigned int type, float x, float y, bool useHitBoxes/* = false*/, CPPBaseEntity* except/* = NULL*/ ) const
{
	float nearDist = FLT_MAX;
	float dist;
	CPPBaseEntity* n = NULL;

	if ( useHitBoxes )
	{
		for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
		{
			CPPBaseEntity* const e = ( *i );

			if ( e->getType() == type )
			{
				if ( except )
				{
					if ( e != except )
					{
						dist = squarePointRect( x, y, e->getPosX() - e->getOriginX(), e->getPosY() - e->getOriginY(), e->getWidth(), e->getHeight() );

						if ( dist < nearDist )
						{
							nearDist = dist;
							n = e;
						}
					}
				}
				else
				{
					dist = squarePointRect( x, y, e->getPosX() - e->getOriginX(), e->getPosY() - e->getOriginY(), e->getWidth(), e->getHeight() );

					if ( dist < nearDist )
					{
						nearDist = dist;
						n = e;
					}
				}
			}
		}
		return n;
	}

	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		CPPBaseEntity* const e = ( *i );

		if ( e->getType() == type )
		{
			if ( except )
			{
				if ( e != except )
				{
					dist = (x - e->getPosX() ) * (x - e->getPosX() ) + ( y - e->getPosY() ) * ( y - e->getPosY() );

					if ( dist < nearDist )
					{
						nearDist = dist;
						n = e;
					}
				}
			}
			else
			{
				dist = ( x - e->getPosX() ) * ( x - e->getPosX() ) + ( y - e->getPosY() ) * ( y - e->getPosY() );

				if ( dist < nearDist )
				{
					nearDist = dist;
					n = e;
				}
			}
		}
	}
	return n;
}

unsigned int CPPBaseWorld::count() const
{
	return m_entities.size();
}

unsigned int CPPBaseWorld::typeCount( unsigned int type ) const
{
	unsigned int n = 0;

	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		if ( ( *i )->getType() == type )
		{
			++n;
		}
	}
	return n;
}

CPPBaseEntity* CPPBaseWorld::farthest() const
{
	if ( m_entities.size() == 0 )
	{
		return NULL;
	}

	return *( m_entities.begin() );
}

CPPBaseEntity* CPPBaseWorld::nearest() const
{
	if ( m_entities.size() == 0 )
	{
		return NULL;
	}

	return *( m_entities.rbegin() );
}

int CPPBaseWorld::layerFarthest() const
{
	if ( m_entities.size() == 0 )
	{
		return 0;
	}

	return ( *( m_entities.begin() ) )->getLayer();
}

int CPPBaseWorld::layerNearest() const
{
	if ( m_entities.size() == 0 )
	{
		return 0;
	}

	return ( *( m_entities.rbegin() ) )->getLayer();
}

void CPPBaseWorld::getType( unsigned int type, std::vector< CPPBaseEntity* >& into ) const
{
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		if ( ( *i )->getType() == type )
		{
			into.push_back( *i );
		}
	}
}

void CPPBaseWorld::getLayer( int layer, std::vector< CPPBaseEntity* >& into ) const
{
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		if ( ( *i )->getLayer() == layer )
		{
			into.push_back( *i );
		}
	}
}

void CPPBaseWorld::getAll( std::vector< CPPBaseEntity* >& into ) const
{
	for ( std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp >::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		into.push_back( *i );
	}
}

void CPPBaseWorld::updateLists( bool shouldAdd/* = true*/ )
{
	// Remove Entities.
	if ( !m_remove.empty() )
	{
		for ( std::vector< CPPBaseEntity* >::iterator i = m_remove.begin(); i != m_remove.end(); ++i )
		{
			CPPBaseEntity* const e = ( *i );

			if ( !e->getWorld() )
			{
				std::vector< CPPBaseEntity* >::iterator j = std::find( m_add.begin(), m_add.end(), e );

				if ( j != m_add.end() )
				{
					m_add.erase( j );
				}

				continue;
			}

			if ( e->getWorld() != this )
			{
				continue;
			}

			e->removed();
			e->setWorld( NULL, m_entityKey );

			m_entities.erase( e );

			if ( e->isAutoCleanup() )
			{
				delete e;
			}
		}
		m_remove.clear();
	}

	// Add Entities.
	if ( shouldAdd && !m_add.empty() )
	{
		for ( std::vector< CPPBaseEntity* >::iterator i = m_add.begin(); i != m_add.end(); ++i )
		{
			CPPBaseEntity* const e = ( *i );

			if ( e->getWorld() )
			{
				continue;
			}

			m_entities.insert( e );

			e->setWorld( this, m_entityKey );
			e->added();
		}
		m_add.clear();
	}
}

static float squareRects( float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2 )
{
	if ( x1 < ( x2 + w2 ) && x2 < ( x1 + w1 ) )
	{
		if ( y1 < ( y2 + h2 ) && y2 < ( y1 + h1 ) )
		{
			return 0;
		}

		if ( y1 > y2 )
		{
			return ( y1 - ( y2 + h2 ) ) * ( y1 - ( y2 + h2 ) );
		}

		return ( y2 - ( y1 + h1 ) ) * ( y2 - ( y1 + h1 ) );
	}

	if ( y1 < ( y2 + h2 ) && y2 < ( y1 + h1 ) )
	{
		if (x1 > x2) 
		{
			return ( x1 - ( x2 + w2 ) ) * ( x1 - ( x2 + w2 ) );
		}

		return ( x2 - ( x1 + w1 ) ) * ( x2 - ( x1 + w1 ) );
	}

	if ( x1 > x2 )
	{
		if ( y1 > y2 )
		{
			return squarePoints( x1, y1, ( x2 + w2 ), ( y2 + h2 ) );
		}

		return squarePoints( x1, ( y1 + h1 ), ( x2 + w2 ), y2 );
	}

	if ( y1 > y2 )
	{
		return squarePoints( ( x1 + w1 ), y1, x2, ( y2 + h2 ) );
	}

	return squarePoints( ( x1 + w1 ), ( y1 + h1 ), x2, y2 );
}

static float squarePoints( float x1, float y1, float x2, float y2 )
{
	return ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 );
}

static float squarePointRect( float px, float py, float rx, float ry, float rw, float rh )
{
	if ( px >= rx && px <= ( rx + rw ) )
	{
		if ( py >= ry && py <= ( ry + rh ) )
		{
			return 0;
		}

		if ( py > ry )
		{
			return ( py - ( ry + rh ) ) * ( py - ( ry + rh ) );
		}

		return ( ry - py ) * ( ry - py );
	}

	if ( py >= ry && py <= ( ry + rh ) )
	{
		if ( px > rx )
		{
			return ( px - ( rx + rw ) ) * ( px - ( rx + rw ) );
		}

		return ( rx - px ) * ( rx - px );
	}

	if ( px > rx )
	{
		if ( py > ry )
		{
			return squarePoints( px, py, ( rx + rw ), ( ry + rh ) );
		}

		return squarePoints( px, py, ( rx + rw ), ry );
	}

	if ( py > ry )
	{
		return squarePoints( px, py, rx, ( ry + rh ) );
	}

	return squarePoints( px, py, rx, ry );
}
