#include "CPPImage.h"

#include "ofGraphics.h"

#include "../CPP.h"

#include <iostream>

CPPImage::CPPImage( const CPPBitmapData& source,
                    bool autoCleanup/* = false */,
                    bool useClipRect/* = false */,
                    float clipRectPosX/* = 0 */,
                    float clipRectPosY/* = 0 */,
                    float clipRectWidth/* = 0 */,
                    float clipRectHeight/* = 0 */ ) :
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
, m_pTexture( source.m_pTexture )
, m_bitmapData( source )
, m_clipRectPosX( clipRectPosX )
, m_clipRectPosY( clipRectPosY )
, m_clipRectWidth( useClipRect
                     ? ( clipRectWidth != 0
                       ? clipRectWidth
                       : m_pTexture->getWidth() )
                     : m_pTexture->getWidth() )
, m_clipRectHeight( useClipRect
                      ? ( clipRectHeight != 0
                        ? clipRectHeight
                        : m_pTexture->getHeight() )
                      : m_pTexture->getHeight() )
{
}

CPPImage::~CPPImage()
{
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

	// Render without transformations.
	if ( m_angle == 0 && m_scaleX * m_scale == 1 && m_scaleY * m_scale == 1 )
	{
		m_pTexture->drawSubsection( x + m_posX - m_originX, y + m_posY - m_originY, // position
		                            m_clipRectWidth*1, m_clipRectHeight*1,          // image dimensions (scale)
		                            m_clipRectPosX, m_clipRectPosY,                 // clipping position
		                            m_clipRectWidth, m_clipRectHeight);             // clipping dimensions
	}
	// Render with transformations. TODO
	else
	{
		// TODO: Should be drawSubsection().
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
	m_originX = m_clipRectWidth / 2;
	m_originY = m_clipRectHeight / 2;
}

float CPPImage::getWidth() const
{
	return m_clipRectWidth;
}

float CPPImage::getHeight() const
{
	return m_clipRectHeight;
}

float CPPImage::getScaledWidth() const
{
	return m_clipRectWidth * m_scaleX * m_scale;
}

void CPPImage::setScaledWidth( const float w )
{
	m_scaleX = w / m_scale / m_clipRectWidth;
}

float CPPImage::getScaledHeight() const
{
	return m_clipRectHeight * m_scaleY * m_scale;
}

void CPPImage::setScaledHeight( const float h )
{
	m_scaleY = h / m_scale / m_clipRectHeight;
}

float CPPImage::getSourceRectPosX() const
{
	return m_clipRectPosX;
}

float CPPImage::getSourceRectPosY() const
{
	return m_clipRectPosY;
}
