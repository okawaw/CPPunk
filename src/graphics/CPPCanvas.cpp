#include "CPPCanvas.h"

#include "../CPP.h"
#include "CPPBitmapData.h"

#include "ofColor.h"

#include <algorithm>

#include <stdlib.h>
#include <string.h>

static const int BYTES_PER_PIXEL = 4 * sizeof( char );

CPPCanvas::CPPCanvas( unsigned int width, unsigned int height, bool autoCleanup/* = false*/ ) :
  CPPBaseGraphic( autoCleanup )
, m_width( width )
, m_height( height )
, m_red( 255 )
, m_green( 255 )
, m_blue( 255 )
, m_alpha( 255 )
{
	m_texture.allocate( width, height, OF_IMAGE_COLOR_ALPHA );

	// Clear contents of the buffers.
	ofColor newColor;
	newColor.r = 0;
	newColor.g = 0;
	newColor.b = 0;
    newColor.a = 0;

	m_texture.setColor( newColor );

	m_texture.update();
}

CPPCanvas::~CPPCanvas()
{
}

unsigned char CPPCanvas::getRed() const { return m_red; }
void CPPCanvas::setRed( const unsigned char red ) { m_red = red; }

unsigned char CPPCanvas::getGreen() const { return m_green; }
void CPPCanvas::setGreen( const unsigned char green ) { m_green = green; }

unsigned char CPPCanvas::getBlue() const { return m_blue; }
void CPPCanvas::setBlue( const unsigned char blue ) { m_blue = blue; }

unsigned char CPPCanvas::getAlpha() const { return m_alpha; }
void CPPCanvas::setAlpha( const unsigned char alpha ) { m_alpha = alpha; }

unsigned int CPPCanvas::getWidth() const { return m_width; }
unsigned int CPPCanvas::getHeight() const { return m_height; }

void CPPCanvas::draw( float x, float y )
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

	m_texture.draw( x + m_posX, y + m_posY );

	if ( m_alpha != 255 )
	{
		ofDisableAlphaBlending();
	}

	ofPopStyle();
}

void CPPCanvas::copyPixels( int x, int y, const CPPBitmapData& source, bool mergeAlpha/* = false*/, bool useRectangle/* = false*/, int rX/* = 0*/, int rY/* = 0*/, unsigned int rWidth/* = 0*/, unsigned int rHeight/* = 0*/ )
{
	copyPixelsAlg( x, y, source.m_pTexture->getPixelsRef(), mergeAlpha, useRectangle, rX, rY, rWidth, rHeight );

	m_texture.update();
}

void CPPCanvas::fill( int rX, int rY, unsigned int rWidth, unsigned int rHeight,
                      unsigned char red/* = 0*/, unsigned char green/* = 0*/, unsigned char blue/* = 0*/, unsigned char alpha/* = 255*/,
                      bool mergeAlpha/* = false*/ )
{
	if (    m_width == 0 || m_height == 0
		 || rWidth == 0 || rHeight == 0 )
	{
		return;
	}

	int aWidth = rWidth;
	int aHeight = rHeight;

	int destLeft = std::max( rX, 0 );
	int destRight = std::min( rX + aWidth, m_texture.width );
	int destTop = std::max( rY, 0 );
	int destBottom = std::min( rY + aHeight, m_texture.height );

	if (    destLeft >= destRight
	     || destTop >= destBottom )
	{
		// No overlap.
		return;
	}

	int destWidth = destRight - destLeft;
	int destHeight = destBottom - destTop;

	if ( destWidth == 0 || destHeight == 0 )
	{
		return;
	}

	unsigned char color[ 4 ] = { red, green, blue, alpha };

	int destItrX = BYTES_PER_PIXEL;
	int destItrY = BYTES_PER_PIXEL * ( m_texture.width - destWidth );

	unsigned char* d = &( m_texture.getPixels()[ BYTES_PER_PIXEL * ( ( destTop * m_texture.width ) + destLeft ) ] );

	for ( int i = 0; i < destHeight; ++i, d += destItrY )
	{
		for ( int j = 0; j < destWidth; ++j, d += destItrX )
		{
			if ( mergeAlpha )
			{
				CPPUtil::alphaOver( color[ 0 ], color[ 1 ], color[ 2 ], color[ 3 ],
									d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ],
									d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ] );
			}
			else
			{
				memcpy( d, color, sizeof( char ) * BYTES_PER_PIXEL );
			}
		}
	}

	m_texture.update();
}

void CPPCanvas::fillTexture( int rX, int rY, int rWidth, int rHeight, const CPPBitmapData& texture )
{
	int startX;
	int startY;
	int endX;
	int endY;

	if ( rWidth < 0 )
	{
		startX = rX + rWidth;
		endX = rX;
	}
	else
	{
		startX = rX;
		endX = rX + rWidth;
	}

	if ( rHeight < 0 )
	{
		startY = rY + rHeight;
		endY = rY;
	}
	else
	{
		startY = rY;
		endY = rY + rHeight;
	}

	for ( int i = startX; i < endX && i < m_texture.width; i += texture.m_pTexture->width )
	{
		for ( int j = startY; j < endY && j < m_texture.height; j += texture.m_pTexture->height )
		{
			copyPixelsAlg( i, j, texture.m_pTexture->getPixelsRef(), false, true, 0, 0, std::abs( rWidth ), std::abs( rHeight ) );
		}
	}

	m_texture.update();
}

void CPPCanvas::getPixel( int x, int y,
                          unsigned char& red, unsigned char& green, unsigned char& blue, unsigned char& alpha ) const
{
	red = m_texture.getColor(x, y).r;
	green = m_texture.getColor(x, y).g;
	blue = m_texture.getColor(x, y).b;
	alpha = m_texture.getColor(x, y).a;
}

void CPPCanvas::setPixel( const unsigned int x, const unsigned int y,
                          const unsigned char red, const unsigned char green,
                          const unsigned char blue, const unsigned char alpha )
{
	ofColor newColor;
	newColor.r = red;
	newColor.g = green;
	newColor.b = blue;
	newColor.a = alpha;

	m_texture.setColor( x, y, newColor );

	m_texture.update();
}

void CPPCanvas::shift( const int x, const int y )
{
	// Create a copy of the canvas to overlay.
	ofPixels p( m_texture.getPixelsRef() );

	copyPixelsAlg( x, y, p, true );

	m_texture.update();
}

void CPPCanvas::copyPixelsAlg( int x, int y, const ofPixels& source, bool mergeAlpha/* = false*/, bool useRectangle/* = false*/, int rX/* = 0*/, int rY/* = 0*/, unsigned int rWidth/* = 0*/, unsigned int rHeight/* = 0*/ )
{
	if ( !useRectangle )
	{
		rX = 0;
		rY = 0;
		rWidth = source.getWidth();
		rHeight = source.getHeight();
	}

	int aWidth = rWidth;
	int aHeight = rHeight;

	int sourceLeft = std::max( rX, 0 );
	int sourceRight = std::min( rX + aWidth, source.getWidth() );
	int sourceTop = std::max( rY, 0 );
	int sourceBottom = std::min( rY + aHeight, source.getHeight() );

	if (    sourceLeft >= sourceRight
	     || sourceTop >= sourceBottom )
	{
		// No overlap.
		return;
	}

	int destLeft = std::max( x + ( sourceLeft - rX ), 0 );
	int destRight = std::min( x + ( sourceRight - rX ), m_texture.width );
	int destTop = std::max( y + ( sourceTop - rY ), 0 );
	int destBottom = std::min( y + ( sourceBottom - rY ), m_texture.height );

	if (    destLeft >= destRight
	     || destTop >= destBottom )
	{
		// No overlap.
		return;
	}

	int destWidth = destRight - destLeft;
	int destHeight = destBottom - destTop;

	int sourceItrX = BYTES_PER_PIXEL;
	int sourceItrY = BYTES_PER_PIXEL * ( source.getWidth() - destWidth );
	int destItrX = BYTES_PER_PIXEL;
	int destItrY = BYTES_PER_PIXEL * ( m_texture.width - destWidth );

	const unsigned char* s = &( source.getPixels()[ BYTES_PER_PIXEL * ( ( ( rY + ( destTop - y ) ) * source.getWidth() ) + ( rX + ( destLeft - x ) ) ) ] );
	unsigned char* d = &( m_texture.getPixels()[ BYTES_PER_PIXEL * ( ( destTop * m_texture.width ) + destLeft ) ] );

	for ( int i = 0; i < destHeight; ++i, s += sourceItrY, d += destItrY )
	{
		for ( int j = 0; j < destWidth; ++j, s += sourceItrX, d += destItrX )
		{
			if ( mergeAlpha )
			{
				CPPUtil::alphaOver( s[ 0 ], s[ 1 ], s[ 2 ], s[ 3 ],
				                    d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ],
				                    d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ] );
			}
			else
			{
				memcpy( d, s, sizeof( char ) * BYTES_PER_PIXEL );
			}
		}
	}
}
