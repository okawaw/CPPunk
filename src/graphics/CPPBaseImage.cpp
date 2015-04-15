#include "CPPBaseImage.h"

#include "ofGraphics.h"

#include "../CPP.h"

#include <iostream>

CPPBaseImage::CPPBaseImage( bool autoCleanup/* = false */ ) :
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
{
}

CPPBaseImage::~CPPBaseImage()
{
}

float CPPBaseImage::getAngle() const { return m_angle; }
void CPPBaseImage::setAngle( const float angle ) { m_angle = angle; }

float CPPBaseImage::getScale() const { return m_scale; }
void CPPBaseImage::setScale( const float scale ) { m_scale = scale; }

float CPPBaseImage::getScaleX() const { return m_scaleX; }
void CPPBaseImage::setScaleX( const float scaleX ) { m_scaleX = scaleX; }

float CPPBaseImage::getScaleY() const { return m_scaleY; }
void CPPBaseImage::setScaleY( const float scaleY ) { m_scaleY = scaleY; }

float CPPBaseImage::getOriginX() const { return m_originX; }
void CPPBaseImage::setOriginX( const float originX ) { m_originX = originX; }

float CPPBaseImage::getOriginY() const { return m_originY; }
void CPPBaseImage::setOriginY( const float originY ) { m_originY = originY; }

unsigned char CPPBaseImage::getRed() const { return m_red; }
void CPPBaseImage::setRed( unsigned char red ) { m_red = red; }

unsigned char CPPBaseImage::getGreen() const { return m_green; }
void CPPBaseImage::setGreen( unsigned char green ) { m_green = green; }

unsigned char CPPBaseImage::getBlue() const { return m_blue; }
void CPPBaseImage::setBlue( unsigned char blue ) { m_blue = blue; }

unsigned char CPPBaseImage::getAlpha() const { return m_alpha; }
void CPPBaseImage::setAlpha( unsigned char alpha ) { m_alpha = alpha; }

void CPPBaseImage::centerOrigin()
{
	m_originX = getWidth() / 2;
	m_originY = getHeight() / 2;
}

void CPPBaseImage::update()
{
}

void CPPBaseImage::draw( float x, float y )                   // TODO: transforms and origin offset TODO: scroll camera
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

	// Render without transformations.
	if ( m_angle == 0 && m_scaleX * m_scale == 1 && m_scaleY * m_scale == 1 )
	{
		drawImage( x, y );
	}
	// Render with transformations. TODO
	else
	{
		drawImage( x, y );
	}

	if ( m_alpha != 255 )
	{
		ofDisableAlphaBlending();
	}

	ofPopStyle();
}

// TODO: flipped
