#ifndef CPP_IMAGE_H_
#define CPP_IMAGE_H_

#include "../CPPBaseGraphic.h"

#include "ofTexture.h"

#include <string>

class CPPImage : public CPPBaseGraphic
{
public:
	CPPImage( std::string source, bool isAutoCleanup = false );
	virtual ~CPPImage();

	virtual void update();
	virtual void draw( float x, float y );

	float getAngle() const;
	void setAngle( const float angle );

	float getScale() const;
	void setScale( const float scale );

	float getScaleX() const;
	void setScaleX( const float scaleX ); 

	float getScaleY() const;
	void setScaleY( const float scaleY );

	float getOriginX() const;
	void setOriginX( const float originX );

	float getOriginY() const;
	void setOriginY( const float originY );

	unsigned char getRed() const;
	void setRed( const unsigned char red );

	unsigned char getBlue() const;
	void setBlue( const unsigned char blue );

	unsigned char getGreen() const;
	void setGreen( const unsigned char green );

	unsigned char getAlpha() const;
	void setAlpha( const unsigned char alpha );

	// Centers the Image's originX/Y to its center.
	void centerOrigin();

	float getWidth();
	float getHeight();

	// TODO: get/set scaled width/height

private:
	float m_angle;            // Rotation of the image, in degrees.
	float m_scale;            // Scale of the image, affects both x and y scale.
	float m_scaleX;           // X scale of the image.
	float m_scaleY;           // Y scale of the image.
	float m_originX;          // X origin of the image, determines transformation point. Defaults to top-left corner.
	float m_originY;          // Y origin of the image, determines transformation point. Defaults to top-left corner.

	unsigned char m_red;      // Red value of the image, a value from 0 to 255.
	unsigned char m_green;    // Green value of the image, a value from 0 to 255.
	unsigned char m_blue;     // Blue value of the image, a value from 0 to 255.
	unsigned char m_alpha;    // Opacity of the Image, a value from 0 to 255.

	ofTexture* m_pTexture;    // Texture data for the image. TODO: MAKE A POINTER TO A RESOURCEMANAGER GIVEN TEXTURE
	std::string m_source;

	CPPImage( const CPPImage& );
	CPPImage& operator=( const CPPImage& );
};

#endif
