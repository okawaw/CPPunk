#ifndef CPP_BITMAP_DATA_H_
#define CPP_BITMAP_DATA_H_

#include <string>

#include "ofImage.h"

class CPPBitmapData
{
public:
	CPPBitmapData( const std::string& source );
	CPPBitmapData( const CPPBitmapData& other );
	CPPBitmapData& operator=( const CPPBitmapData& other );

	~CPPBitmapData();

private:
	friend class CPPImage;
	friend class CPPCanvas;
	friend class CPPTilemap;

	ofImage* m_pTexture;
	std::string m_source;
};

#endif
