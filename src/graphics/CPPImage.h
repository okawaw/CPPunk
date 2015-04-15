#ifndef CPP_IMAGE_H_
#define CPP_IMAGE_H_

#include "CPPBaseImage.h"

#include "CPPBitmapData.h"

#include "ofImage.h"

class CPPImage : public CPPBaseImage
{
public:
	CPPImage( const CPPBitmapData& source,
	          bool autoCleanup = false,
	          bool useClipRect = false,
	          float clipRectPosX = 0,
	          float clipRectPosY = 0,
	          float clipRectWidth = 0,
	          float clipRectHeight = 0 );
	virtual ~CPPImage();

	virtual void update();
	virtual void drawImage( float x, float y );

	float getWidth() const;
	float getHeight() const;

	float getScaledWidth() const;
	void setScaledWidth( const float w );

	float getScaledHeight() const;
	void setScaledHeight( const float h );

	float getSourceRectPosX() const;
	float getSourceRectPosY() const;

	// TODO: get/set scaled width/height

protected:

	ofImage* m_pTexture;        // Texture data for the image. This is not owned/managed by this class. TODO: CONSTANT POINTER?
	CPPBitmapData m_bitmapData; // BitmapData for the image. This allows the resource manager to correctly handle the data.

private:
	CPPImage( const CPPImage& );
	CPPImage& operator=( const CPPImage& );

protected:
	float m_clipRectPosX;       // Clipping Rectangle X Position
	float m_clipRectPosY;       // Clipping Rectangle Y Position
	float m_clipRectWidth;      // Clipping Rectangle Width
	float m_clipRectHeight;     // Clipping Rectangle Height
};

#endif
