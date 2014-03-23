#include "BaseEntity.h"

BaseEntity::BaseEntity( const std::string& graphicFile/* = ""*/, float x/* = 0*/, float y/* = 0*/ ) :
  m_bVisible( true )
, m_bCollidable( true )
, m_posX( x )
, m_posY( y )
, m_width( 0 )
, m_height( 0 )
, m_originX( 0 )
, m_originY( 0 )
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
	if ( m_bVisible )
	{
		m_graphic.draw( m_posX, m_posY );
	}
}

void BaseEntity::added()
{
}

void BaseEntity::removed()
{
}
