#include "CPPBaseEntity.h"

#include "CPPBaseWorld.h"
#include "CPP.h"

#include <math.h>

#define DEBUG_MODE

#ifdef DEBUG_MODE
#include "ofGraphics.h"
#endif

CPPBaseEntity::CPPBaseEntity( float x/* = 0*/, float y/* = 0*/, CPPBaseGraphic* graphic/* = NULL*/, bool autoCleanup/* = false */ ) :
  m_bVisible( true )
, m_bActive( true )
, m_bCollidable( true )
, m_posX( x )
, m_posY( y )
, m_width( 0 )
, m_height( 0 )
, m_originX( 0 )
, m_originY( 0 )
, m_type( 0 )
, m_layer( 0 )
, m_world( NULL )
, m_bAutoCleanup( autoCleanup )
, m_pGraphic( graphic )
, _moveX( 0 )
, _moveY( 0 )
{
}

CPPBaseEntity::~CPPBaseEntity()
{
	// TODO: make this optional...
	delete m_pGraphic;
}

bool CPPBaseEntity::ptrCmp::operator()( const CPPBaseEntity* left, const CPPBaseEntity* right )
{
	return ( left->m_layer == right->m_layer ) ? left < right : left->m_layer > right->m_layer;
}

CPPBaseEntity::EntityKey::EntityKey() {}
CPPBaseEntity::EntityKey::~EntityKey() {}

bool CPPBaseEntity::isActive() const { return m_bActive; }
void CPPBaseEntity::setActive( const bool active ) { m_bActive = active; }

bool CPPBaseEntity::isVisible() const { return m_bVisible; }
void CPPBaseEntity::setVisible( const bool visible ) { m_bVisible = visible; }

bool CPPBaseEntity::isCollidable() const { return m_bCollidable; }
void CPPBaseEntity::setCollidable( const bool collidable ) { m_bCollidable = collidable; }

float CPPBaseEntity::getPosX() const { return m_posX; }
float CPPBaseEntity::getPosY() const { return m_posY; }
void CPPBaseEntity::setPosX( const float x ) { m_posX = x; }
void CPPBaseEntity::setPosY( const float y ) { m_posY = y; }

int CPPBaseEntity::getWidth() const { return m_width; }
int CPPBaseEntity::getHeight() const { return m_height; }
void CPPBaseEntity::setWidth( const int width ) { m_width = width; }
void CPPBaseEntity::setHeight( const int height ) { m_height = height; }
float CPPBaseEntity::getHalfWidth() const { return ( ( float )m_width / 2.0 ); }
float CPPBaseEntity::getHalfHeight() const { return ( ( float )m_height / 2.0 ); }

int CPPBaseEntity::getOriginX() const { return m_originX; }
int CPPBaseEntity::getOriginY() const { return m_originY; }
void CPPBaseEntity::setOriginX( const int x ) { m_originX = x; }
void CPPBaseEntity::setOriginY( const int y ) { m_originY = y; }
void CPPBaseEntity::centerOrigin() { m_originX = ( ( float )m_width / 2.0 ); m_originY = ( ( float )m_height / 2.0 ); }

unsigned int CPPBaseEntity::getType() const { return m_type; }
void CPPBaseEntity::setType( const unsigned int type ) { m_type = type; }

float CPPBaseEntity::getCenterX() const { return m_posX - m_originX + ( ( float )m_width / 2.0 ); }
float CPPBaseEntity::getCenterY() const { return m_posY - m_originY + ( ( float )m_height / 2.0 ); }

float CPPBaseEntity::getLeft() const { return m_posX - m_originX; }
float CPPBaseEntity::getRight() const { return m_posX - m_originX + m_width; }
float CPPBaseEntity::getTop() const { return m_posY - m_originY; }
float CPPBaseEntity::getBottom() const { return m_posY - m_originY + m_height; }

CPPBaseWorld* CPPBaseEntity::getWorld() const { return m_world; }
void CPPBaseEntity::setWorld( CPPBaseWorld* const world, EntityKey& ) { m_world = world; }

bool CPPBaseEntity::isAutoCleanup() const { return m_bAutoCleanup; }

int CPPBaseEntity::getLayer() const { return m_layer; }
void CPPBaseEntity::setLayer( const int layer )
{	
	// Reinsert this entity into its world to make sure it draws in the correct order.
	if ( m_world )
	{
		m_world->updateEntityLayer( this, layer );
	}
	else
	{
		m_layer = layer;
	}
}

void CPPBaseEntity::setHitbox( const int width, const int height, const int originX, const int originY )
{
	m_width = width;
	m_height = height;
	m_originX = originX;
	m_originY = originY;
}

bool CPPBaseEntity::onCamera() const
{
	return collideRect( m_posX, m_posY, CPP::getCameraX(), CPP::getCameraY(), CPP::getWidth(), CPP::getHeight() );
}

CPPBaseGraphic* CPPBaseEntity::getGraphic() const
{
	return m_pGraphic;
}

void CPPBaseEntity::setGraphic( CPPBaseGraphic* graphic )
{
	delete m_pGraphic;

	m_pGraphic = graphic;
}

void CPPBaseEntity::update()
{
}

void CPPBaseEntity::draw()
{
	if ( m_pGraphic && m_pGraphic->isVisible() )
	{
		if ( m_pGraphic->isRelative() )
		{
			m_pGraphic->draw( m_posX, m_posY );
		}
		else
		{
			m_pGraphic->draw( 0, 0 );
		}

	
#ifdef DEBUG_MODE
		ofPushStyle();

		ofPolyline p;
		ofSetLineWidth( 2 );

		ofSetColor(255,0,0);
		p.addVertex( m_posX - m_originX, m_posY - m_originY );
		p.addVertex( m_posX - m_originX + m_width, m_posY - m_originY );
		p.addVertex( m_posX - m_originX + m_width, m_posY - m_originY );
		p.addVertex( m_posX - m_originX + m_width, m_posY - m_originY + m_height );
		p.addVertex( m_posX - m_originX + m_width, m_posY - m_originY + m_height );
		p.addVertex( m_posX - m_originX, m_posY - m_originY + m_height );
		p.addVertex( m_posX - m_originX, m_posY - m_originY + m_height );
		p.addVertex( m_posX - m_originX, m_posY - m_originY );
		p.draw();

		p.clear();

		ofSetColor( 0, 255, 0 );
		p.addVertex( m_posX - 2, m_posY - 2 );
		p.addVertex( m_posX + 2, m_posY - 2 );
		p.addVertex( m_posX + 2, m_posY - 2 );
		p.addVertex( m_posX + 2, m_posY + 2 );
		p.addVertex( m_posX + 2, m_posY + 2 );
		p.addVertex( m_posX - 2, m_posY + 2 );
		p.addVertex( m_posX - 2, m_posY + 2 );
		p.addVertex( m_posX - 2, m_posY - 2 );
		p.draw();

		ofPopStyle();
#endif
	}
}

void CPPBaseEntity::added()
{
}

void CPPBaseEntity::removed()
{
}

CPPBaseEntity* CPPBaseEntity::collide( unsigned int type, float x, float y ) const
{
	if ( !m_world )
	{
		return NULL;
	}

	return m_world->collideRect( type, x - m_originX, y - m_originY, m_width, m_height, this );
}

bool CPPBaseEntity::collideRect( float x, float y, float rX, float rY, float rWidth, float rHeight ) const
{
	return (    x - m_originX + m_width >= rX && y - m_originY + m_height >= rY
	         && x - m_originX <= rX + rWidth && y - m_originY <= rY + rHeight );
}

CPPBaseEntity* CPPBaseEntity::collideTypes( const vector< unsigned int >& types, float x, float y ) const
{
	if ( !m_world )
	{
		return NULL;
	}

	CPPBaseEntity* e;

	for ( unsigned int i = 0; i < types.size(); ++i )
	{
		if ( e = collide( types[ i ], x, y ) )
		{
			return e;
		}
	}

	return NULL;
}

CPPBaseEntity* CPPBaseEntity::collideWith( CPPBaseEntity* e, float x, float y ) const
{
	if (    e->m_bCollidable
	     && x - m_originX + m_width > e->m_posX - e->m_originX
	     && y - m_originY + m_height > e->m_posY - e->m_originY
	     && x - m_originX < e->m_posX - e->m_originX + e->m_width
	     && y - m_originY < e->m_posY - e->m_originY + e->m_height )
	{
		return e;
	}
	
	return NULL;
}

bool CPPBaseEntity::collidePoint( float x, float y, float pX, float pY ) const
{
	return (    pX >= x - m_originX && pY >= y - m_originY
	         && pX < x - m_originX + m_width && pY < y - m_originY + m_height );
}

void CPPBaseEntity::collideInto( unsigned int type, float x, float y, std::vector< CPPBaseEntity* >& into ) const
{
	if ( !m_world )
	{
		return;
	}

	m_world->collideRectInto( type, x - m_originX, y - m_originY, m_width, m_height, into, this );
}

float CPPBaseEntity::distanceFrom( CPPBaseEntity* e, bool useHitboxes/* = false*/ ) const
{
	if ( !useHitboxes )
	{
		return sqrt( ( m_posX - e->m_posX ) * ( m_posX - e->m_posX ) + ( m_posY - e->m_posY ) * ( m_posY - e->m_posY ) );
	}

	return CPP::distanceRects( m_posX - m_originX, m_posY - m_originY, m_width, m_height, e->m_posX - e->m_originX, e->m_posY - e->m_originY, e->m_width, e->m_height );
}

float CPPBaseEntity::distanceToPoint( float pX, float pY, bool useHitBox/* = false*/ ) const
{
	if ( !useHitBox )
	{
		return sqrt( ( m_posX - pX ) * ( m_posX - pX ) + ( m_posY - pY ) * ( m_posY - pY ) ); 
	}

	return CPP::distanceRectPoint( pX, pY, m_posX - m_originX, m_posY - m_originY, m_width, m_height );
}

float CPPBaseEntity::distanceToRect( float rX, float rY, float rWidth, float rHeight ) const
{
	return CPP::distanceRects( rX, rY, rWidth, rHeight, m_posX - m_originX, m_posY - m_originY, m_width, m_height);
}

void CPPBaseEntity::moveBy( float x, float y, bool useSolidType/* = false*/, unsigned int solidType/* = 0*/, bool sweep/* = false*/ )
{
	_moveX += x;
	_moveY += y;
	x = floor( _moveX + 0.5 );
	y = floor( _moveY + 0.5 );
	_moveX -= x;
	_moveY -= y;

	if ( useSolidType )
	{
		int sign;
		CPPBaseEntity* e;

		if ( x != 0 )
		{
			if ( sweep || collide( solidType, m_posX + x, m_posY ) )
			{
				sign = ( x > 0 ) ? 1 : -1;
				while ( x != 0 )
				{
					if ( ( e = collide( solidType, m_posX + sign, m_posY ) ) )
					{
						moveCollideX( e );
						break;
					}
					else
					{
						m_posX += sign;
					}
					x -= sign;
				}
			}
			else
			{
				m_posX += x;
			}
		}
		if ( y != 0 )
		{
			if ( sweep || collide( solidType, m_posX, m_posY + y ) )
			{
				sign = ( y > 0 ) ? 1 : -1;
				while ( y != 0 )
				{
					if ( ( e = collide( solidType, m_posX, m_posY + sign ) ) )
					{
						moveCollideY( e );
						break;
					}
					else
					{
						m_posY += sign;
					}
					y -= sign;
				}
			}
			else
			{
				m_posY += y;
			}
		}
	}
	else
	{
		m_posX += x;
		m_posY += y;
	}
}

void CPPBaseEntity::moveBy( float x, float y, const std::vector< unsigned int >& solidTypes, bool sweep/* = false*/ )
{
	_moveX += x;
	_moveY += y;
	x = floor( _moveX + 0.5 );
	y = floor( _moveY + 0.5 );
	_moveX -= x;
	_moveY -= y;

	int sign;
	CPPBaseEntity* e;

	if ( x != 0 )
	{
		if ( sweep || collideTypes( solidTypes, m_posX + x, m_posY ) )
		{
			sign = ( x > 0 ) ? 1 : -1;
			while ( x != 0 )
			{
				if ( ( e = collideTypes( solidTypes, m_posX + sign, m_posY ) ) )
				{
					moveCollideX( e );
					break;
				}
				else
				{
					m_posX += sign;
				}
				x -= sign;
			}
		}
		else
		{
			m_posX += x;
		}
	}
	if ( y != 0 )
	{
		if ( sweep || collideTypes( solidTypes, m_posX, m_posY + y ) )
		{
			sign = ( y > 0 ) ? 1 : -1;
			while ( y != 0 )
			{
				if ( ( e = collideTypes( solidTypes, m_posX, m_posY + sign ) ) )
				{
					moveCollideY( e );
					break;
				}
				else
				{
					m_posY += sign;
				}
				y -= sign;
			}
		}
		else
		{
			m_posY += y;
		}
	}
}

void CPPBaseEntity::moveTo( float x, float y, bool useSolidType/* = false*/, unsigned int solidType/* = 0*/, bool sweep/* = false*/ )
{
	moveBy( x - m_posX, y - m_posY, useSolidType, solidType, sweep );
}

void CPPBaseEntity::moveTo( float x, float y, const std::vector< unsigned int >& solidTypes, bool sweep/* = false*/ )
{
	moveBy( x - m_posX, y - m_posY, solidTypes, sweep );
}

void CPPBaseEntity::moveTowards( float x, float y, float amount, bool useSolidType/* = false*/, unsigned int solidType/* = 0*/, bool sweep/* = false*/ )
{
	const float xMovement = x - m_posX;
	const float yMovement = y - m_posY;

	const float distance = sqrt( ( xMovement * xMovement ) + ( yMovement * yMovement ) );

	moveBy( ( xMovement / distance ), ( yMovement / distance ), useSolidType, solidType, sweep );
}

void CPPBaseEntity::moveTowards( float x, float y, float amount, const std::vector< unsigned int >& solidTypes, bool sweep/* = false*/ )
{
	const float xMovement = x - m_posX;
	const float yMovement = y - m_posY;

	const float distance = sqrt( ( xMovement * xMovement ) + ( yMovement * yMovement ) );

	moveBy( ( xMovement / distance ), ( yMovement / distance ), solidTypes, sweep );
}

void CPPBaseEntity::clampHorizontal( float left, float right, float padding/* = 0*/ )
{
	if ( m_posX - m_originX < left + padding )
	{
		m_posX = left + m_originX + padding;
	}
	if ( m_posX - m_originX + m_width > right - padding )
	{
		m_posX = right - m_width + m_originX - padding;
	}
}

void CPPBaseEntity::clampVertical( float top, float bottom, float padding/* = 0*/ )
{
	if ( m_posY - m_originY < top + padding )
	{
		m_posY = top + m_originY + padding;
	}
	if ( m_posY - m_originY + m_height > bottom - padding )
	{
		m_posY = bottom - m_height + m_originY - padding;
	}
}

void CPPBaseEntity::moveCollideX( CPPBaseEntity* e )
{
}

void CPPBaseEntity::moveCollideY( CPPBaseEntity* e )
{
}
