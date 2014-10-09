#include "CPPImage.h"

#include "ofImage.h"
#include "ofGraphics.h"

#include "../CPP.h"

#include <iostream>

CPPImage::CPPImage( std::string source, bool autoCleanup/* = false */ ) :
  CPPBaseGraphic( autoCleanup )
, m_angle( 0 )
, m_scale( 1 )
, m_scaleX( 1 )
, m_scaleY( 1 )
, m_originX( 0 )
, m_originY( 0 )
, m_red( 255 )
, m_green( 255 )
, m_blue( 255 )
, m_alpha( 255 )
, m_source( source )
{
	// Load the image file into the texture data.
	m_pTexture = CPP::getTexture( source );
}

CPPImage::~CPPImage()
{
	CPP::releaseTexture( m_source );
}

float CPPImage::getAngle() const { return m_angle; }
void CPPImage::setAngle( const float angle ) { m_angle = angle; }

float CPPImage::getScale() const { return m_scale; }
void CPPImage::setScale( const float scale ) { m_scale = scale; }

float CPPImage::getScaleX() const { return m_scaleX; }
void CPPImage::setScaleX( const float scaleX ) { m_scaleX = scaleX; }

float CPPImage::getScaleY() const { return m_scaleY; }
void CPPImage::setScaleY( const float scaleY ) { m_scaleY = scaleY; }

float CPPImage::getOriginX() const { return m_originX; }
void CPPImage::setOriginX( const float originX ) { m_originX = originX; }

float CPPImage::getOriginY() const { return m_originY; }
void CPPImage::setOriginY( const float originY ) { m_originY = originY; }

unsigned char CPPImage::getRed() const { return m_red; }
void CPPImage::setRed( unsigned char red ) { m_red = red; }

unsigned char CPPImage::getGreen() const { return m_green; }
void CPPImage::setGreen( unsigned char green ) { m_green = green; }

unsigned char CPPImage::getBlue() const { return m_blue; }
void CPPImage::setBlue( unsigned char blue ) { m_blue = blue; }

unsigned char CPPImage::getAlpha() const { return m_alpha; }
void CPPImage::setAlpha( unsigned char alpha ) { m_alpha = alpha; }

void CPPImage::update()
{
}

void CPPImage::draw( float x, float y )                                             // TODO: transforms and origin offset TODO: scroll camera
{
	ofPushStyle();

	if ( m_alpha != 255 )
	{
		ofEnableAlphaBlending();
		ofSetColor( m_red, m_blue, m_green, m_alpha );
	}
	else
	{
		ofSetColor( m_red, m_blue, m_green );
	}

	if ( m_angle == 0 && m_scaleX * m_scale == 1 && m_scaleY * m_scale == 1 )
	{
		m_pTexture->draw( x + m_posX - m_originX, y + m_posY - m_originY );
	}
	// Render without transformations.
	else
	{
		m_pTexture->draw( x + m_posX - m_originX, y + m_posY - m_originY );           // TODO: transformations.
	}

	if ( m_alpha != 255 )
	{
		ofDisableAlphaBlending();
	}

	ofPopStyle();
}

// TODO: flipped

void CPPImage::centerOrigin()
{
	m_originX = m_pTexture->getWidth() / 2;
	m_originY = m_pTexture->getHeight() / 2;
}

float CPPImage::getWidth()
{
	return m_pTexture->getWidth();
}

float CPPImage::getHeight()
{
	return m_pTexture->getHeight();
}
