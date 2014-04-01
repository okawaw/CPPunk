#include "BaseEntity.h"

#include "BaseWorld.h"
#include "CPP.h"

#include <math.h>

#define DEBUG_MODE

#ifdef DEBUG_MODE
#include "ofGraphics.h"
#endif

CPPBaseEntity::CPPBaseEntity( const std::string& graphicFile/* = ""*/, float x/* = 0*/, float y/* = 0*/ ) :
  m_bVisible( true )
, m_bCollidable( true )
, m_posX( x )
, m_posY( y )
, m_width( 0 )
, m_height( 0 )
, m_originX( 0 )
, m_originY( 0 )
, m_type( BaseEntityTypes::LAST_TYPE )
, m_layer( 0 )
, m_world( NULL )
{
	if ( graphicFile.length() != 0 )
	{
		m_graphic.loadImage( graphicFile );
		m_width = m_graphic.width;
		m_height = m_graphic.height;
	}
}

CPPBaseEntity::~CPPBaseEntity()
{
}

bool CPPBaseEntity::ptrCmp::operator()( const CPPBaseEntity* left, const CPPBaseEntity* right )
{
	return ( left->m_layer == right->m_layer ) ? left < right : left->m_layer > right->m_layer;
}

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

BaseEntityTypes::id CPPBaseEntity::getType() const { return m_type; }
void CPPBaseEntity::setType( const BaseEntityTypes::id type ) { m_type = type; }

float CPPBaseEntity::getCenterX() const { return m_posX - m_originX + ( ( float )m_width / 2.0 ); }
float CPPBaseEntity::getCenterY() const { return m_posY - m_originY + ( ( float )m_height / 2.0 ); }

float CPPBaseEntity::getLeft() const { return m_posX - m_originX; }
float CPPBaseEntity::getRight() const { return m_posX - m_originX + m_width; }
float CPPBaseEntity::getTop() const { return m_posY - m_originY; }
float CPPBaseEntity::getBottom() const { return m_posY - m_originY + m_height; }

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

void CPPBaseEntity::setGraphic( const std::string& file )
{
	if ( m_graphic.isAllocated() )
	{
		m_graphic.clear();
	}

	m_graphic.loadImage( file );
	m_width = m_graphic.width;
	m_height = m_graphic.height;
}

void CPPBaseEntity::update()
{
}

void CPPBaseEntity::draw() // TODO: Use layer.
{
#ifdef DEBUG_MODE
	ofSetColor(255,255,255);
#endif

	if ( m_bVisible )
	{
		m_graphic.draw( m_posX, m_posY );
	}
	
#ifdef DEBUG_MODE
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
#endif
}

void CPPBaseEntity::added()
{
}

void CPPBaseEntity::removed()
{
}

CPPBaseEntity* CPPBaseEntity::collide( BaseEntityTypes::id type, float x, float y ) const
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

CPPBaseEntity* CPPBaseEntity::collideTypes( vector< BaseEntityTypes::id >& types, float x, float y )
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

CPPBaseEntity* CPPBaseEntity::collideWith( CPPBaseEntity* e, float x, float y )
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

bool CPPBaseEntity::collidePoint( float x, float y, float pX, float pY )
{
	return (    pX >= x - m_originX && pY >= y - m_originY
	         && pX < x - m_originX + m_width && pY < y - m_originY + m_height );
}

void CPPBaseEntity::collideInto( BaseEntityTypes::id type, float x, float y, std::vector< CPPBaseEntity* >& into )
{
	if ( !m_world )
	{
		return;
	}

	m_world->collideRectInto( type, x - m_originX, y - m_originY, m_width, m_height, into, this );
}

float CPPBaseEntity::distanceFrom( CPPBaseEntity* e, bool useHitboxes/* = false*/ )
{
	if ( !useHitboxes )
	{
		return sqrt( ( m_posX - e->m_posX ) * ( m_posX - e->m_posX ) + ( m_posY - e->m_posY ) * ( m_posY - e->m_posY ) );
	}

	return CPP::distanceRects( m_posX - m_originX, m_posY - m_originY, m_width, m_height, e->m_posX - e->m_originX, e->m_posY - e->m_originY, e->m_width, e->m_height );
}

float CPPBaseEntity::distanceToPoint( float pX, float pY, bool useHitBox/* = false*/ )
{
	if ( !useHitBox )
	{
		return sqrt( ( m_posX - pX ) * ( m_posX - pX ) + ( m_posY - pY ) * ( m_posY - pY ) ); 
	}

	return CPP::distanceRectPoint( pX, pY, m_posX - m_originX, m_posY - m_originY, m_width, m_height );
}

float CPPBaseEntity::distanceToRectangle( float rX, float rY, float rWidth, float rHeight )
{
	return CPP::distanceRects( rX, rY, rWidth, rHeight, m_posX - m_originX, m_posY - m_originY, m_width, m_height);
}
