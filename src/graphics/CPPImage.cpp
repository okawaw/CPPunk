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
  CPPBaseImage( autoCleanup )
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

void CPPImage::update()
{
}

void CPPImage::drawImage( float x, float y )                // TODO: transforms and origin offset TODO: scroll camera
{
	m_pTexture->drawSubsection( x + m_posX - m_originX, y + m_posY - m_originY, // position
	                            m_clipRectWidth*1, m_clipRectHeight*1,          // image dimensions (scale)
	                            m_clipRectPosX, m_clipRectPosY,                 // clipping position
	                            m_clipRectWidth, m_clipRectHeight);             // clipping dimensions
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
