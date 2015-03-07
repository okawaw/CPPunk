#ifndef CPP_CANVAS_H_
#define CPP_CANVAS_H_

#include "../CPPBaseGraphic.h"

#include "ofImage.h"
#include "ofPixels.h"

class CPPBitmapData;

class CPPCanvas : public CPPBaseGraphic
{
public:
	CPPCanvas( unsigned int width, unsigned int height, bool autoCleanup = false );
	virtual ~CPPCanvas();

	// Draws the canvas.
	virtual void draw( float x, float y );

	// Copies a rectangular area of a source image to a rectangular area of the same size at the destination point of the destination BitmapData object.
	void copyPixels( int x, int y, const CPPBitmapData& source, bool mergeAlpha = false, bool useRectangle = false, int rX = 0, int rY = 0, unsigned int rWidth = 0, unsigned int rHeight = 0 );

	// Fills the rectangular area of the canvas. The previous contents of that area are completely removed
	// if mergeAlpha is false. Otherwise, alpha compositing is performed.
	void fill( int rX, int rY, unsigned int rWidth, unsigned int rHeight,
	           unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0, unsigned char alpha = 255,
	           bool mergeAlpha = false );

	// Fills the rectangle area of the canvas with the texture.
	void fillTexture( int rX, int rY, int rWidth, int rHeight, const CPPBitmapData& texture );

	// Get the pixel data at a position.
	void getPixel( int x, int y,
	               unsigned char& red, unsigned char& green, unsigned char& blue, unsigned char& alpha ) const;

	// Set the pixel data at a position.
	void setPixel( const unsigned int x, const unsigned int y, const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha );

	// The tinted color of the Canvas.
	unsigned char getRed() const;
	void setRed( const unsigned char red );

	unsigned char getGreen() const;
	void setGreen( const unsigned char green );

	unsigned char getBlue() const;
	void setBlue( const unsigned char blue );

	unsigned char getAlpha() const;
	void setAlpha( const unsigned char alpha );

	// Shifts the canvas's pixels by the offset.
	void shift( const int x, const int y );

	unsigned int getWidth() const;
	unsigned int getHeight() const;

protected:
	unsigned int m_width;
	unsigned int m_height;

	unsigned char m_red;      // Red value of the image, a value from 0 to 255.
	unsigned char m_green;    // Green value of the image, a value from 0 to 255.
	unsigned char m_blue;     // Blue value of the image, a value from 0 to 255.
	unsigned char m_alpha;    // Opacity of the Image, a value from 0 to 255.

private:
	ofImage m_texture;        // Texture data for the image.

	// Internal function that handles copying pixels to the canvas.
	void copyPixelsAlg( int x, int y, const ofPixels& source, bool mergeAlpha = false, bool useRectangle = false, int rX = 0, int rY = 0, unsigned int rWidth = 0, unsigned int rHeight = 0 );

	CPPCanvas( const CPPCanvas& );
	CPPCanvas& operator=( const CPPCanvas& );
};

#endif
