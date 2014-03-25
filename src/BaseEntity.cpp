#include "BaseEntity.h"

#include "BaseWorld.h"
#include "CPP.h"

#include <math.h>

#define DEBUG_MODE

#ifdef DEBUG_MODE
#include "ofGraphics.h"
#endif

BaseEntity::BaseEntity( const std::string& graphicFile/* = ""*/, float x/* = 0*/, float y/* = 0*/ ) :
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

BaseEntity::~BaseEntity()
{
}

bool BaseEntity::isVisible() const { return m_bVisible; }
void BaseEntity::setVisible( const bool visible ) { m_bVisible = visible; }

bool BaseEntity::isCollidable() const { return m_bCollidable; }
void BaseEntity::setCollidable( const bool collidable ) { m_bCollidable = collidable; }

float BaseEntity::getPosX() const { return m_posX; }
float BaseEntity::getPosY() const { return m_posY; }
void BaseEntity::setPosX( const float x ) { m_posX = x; }
void BaseEntity::setPosY( const float y ) { m_posY = y; }

int BaseEntity::getWidth() const { return m_width; }
int BaseEntity::getHeight() const { return m_height; }
void BaseEntity::setWidth( const int width ) { m_width = width; }
void BaseEntity::setHeight( const int height ) { m_height = height; }
float BaseEntity::getHalfWidth() const { return ( ( float )m_width / 2.0 ); }
float BaseEntity::getHalfHeight() const { return ( ( float )m_height / 2.0 ); }

int BaseEntity::getOriginX() const { return m_originX; }
int BaseEntity::getOriginY() const { return m_originY; }
void BaseEntity::setOriginX( const int x ) { m_originX = x; }
void BaseEntity::setOriginY( const int y ) { m_originY = y; }
void BaseEntity::centerOrigin() { m_originX = ( ( float )m_width / 2.0 ); m_originY = ( ( float )m_height / 2.0 ); }

BaseEntityTypes::id BaseEntity::getType() const { return m_type; }
void BaseEntity::setType( const BaseEntityTypes::id type ) { m_type = type; }

float BaseEntity::getCenterX() const { return m_posX - m_originX + ( ( float )m_width / 2.0 ); }
float BaseEntity::getCenterY() const { return m_posY - m_originY + ( ( float )m_height / 2.0 ); }

float BaseEntity::getLeft() const { return m_posX - m_originX; }
float BaseEntity::getRight() const { return m_posX - m_originX + m_width; }
float BaseEntity::getTop() const { return m_posY - m_originY; }
float BaseEntity::getBottom() const { return m_posY - m_originY + m_height; }

int BaseEntity::getLater() const { return m_layer; }
void BaseEntity::setLayer( const int layer ) { m_layer = layer; }

void BaseEntity::setHitbox( const int width, const int height, const int originX, const int originY )
{
	m_width = width;
	m_height = height;
	m_originX = originX;
	m_originY = originY;
}

void BaseEntity::setGraphic( const std::string& file )
{
	if ( m_graphic.isAllocated() )
	{
		m_graphic.clear();
	}

	m_graphic.loadImage( file );
	m_width = m_graphic.width;
	m_height = m_graphic.height;
}

void BaseEntity::update()
{
}

void BaseEntity::draw() // TODO: Use layer.
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

void BaseEntity::added()
{
}

void BaseEntity::removed()
{
}

BaseEntity* BaseEntity::collide( BaseEntityTypes::id type, float x, float y )
{
	if ( !m_world )
	{
		return NULL;
	}

	return m_world->collideRect( type, x - m_originX, y - m_originY, m_width, m_height, this );
}

bool BaseEntity::collideRect( float x, float y, float rX, float rY, float rWidth, float rHeight )
{
	return (    x - m_originX + m_width >= rX && y - m_originY + m_height >= rY
	         && x - m_originX <= rX + rWidth && y - m_originY <= rY + rHeight );
}

BaseEntity* BaseEntity::collideTypes( vector< BaseEntityTypes::id >& types, float x, float y )
{
	if ( !m_world )
	{
		return NULL;
	}

	BaseEntity* e;

	for ( unsigned int i = 0; i < types.size(); ++i )
	{
		if ( e = collide( types[ i ], x, y ) )
		{
			return e;
		}
	}

	return NULL;
}

BaseEntity* BaseEntity::collideWith( BaseEntity* e, float x, float y )
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

bool BaseEntity::collidePoint( float x, float y, float pX, float pY )
{
	return (    pX >= x - m_originX && pY >= y - m_originY
	         && pX < x - m_originX + m_width && pY < y - m_originY + m_height );
}

void BaseEntity::collideInto( BaseEntityTypes::id type, float x, float y, std::vector< BaseEntity* >& into )
{
	if ( !m_world )
	{
		return;
	}

	m_world->collideRectInto( type, x - m_originX, y - m_originY, m_width, m_height, into, this );
}

float BaseEntity::distanceFrom( BaseEntity* e, bool useHitboxes/* = false*/ )
{
	if ( !useHitboxes )
	{
		return sqrt( ( m_posX - e->m_posX ) * ( m_posX - e->m_posX ) + ( m_posY - e->m_posY ) * ( m_posY - e->m_posY ) );
	}

	return CPP::distanceRects( m_posX - m_originX, m_posY - m_originY, m_width, m_height, e->m_posX - e->m_originX, e->m_posY - e->m_originY, e->m_width, e->m_height );
}

float BaseEntity::distanceToPoint( float pX, float pY, bool useHitBox/* = false*/ )
{
	if ( !useHitBox )
	{
		return sqrt( ( m_posX - pX ) * ( m_posX - pX ) + ( m_posY - pY ) * ( m_posY - pY ) ); 
	}

	return CPP::distanceRectPoint( pX, pY, m_posX - m_originX, m_posY - m_originY, m_width, m_height );
}

float BaseEntity::distanceToRectangle( float rX, float rY, float rWidth, float rHeight )
{
	return CPP::distanceRects( rX, rY, rWidth, rHeight, m_posX - m_originX, m_posY - m_originY, m_width, m_height);
}
