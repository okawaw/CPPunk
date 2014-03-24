#include "BaseEntity.h"

#include "BaseWorld.h"

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

void BaseEntity::draw()
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
