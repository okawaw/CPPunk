#ifndef CPP_BITMAP_DATA_RESOURCE_MANAGER_H_
#define CPP_BITMAP_DATA_RESOURCE_MANAGER_H_

#include "ofImage.h"

#include <map>
#include <string>

class CPPBitmapDataResourceManager
{
	friend class CPP;
	friend class CPPBitmapData;
private:
	// < resourceName, < ofImagePointer, retainCount > >
	typedef std::map< std::string, std::pair< ofImage*, unsigned int > > CPPTextureMap;

	CPPBitmapDataResourceManager();
	~CPPBitmapDataResourceManager();

	static void initialize();
	static void destroy();
	static CPPBitmapDataResourceManager* getInstance();

	ofImage* useTexture( const std::string& fileName );
	void releaseTexture( const std::string& fileName );

	static void deleteTexture( CPPTextureMap::value_type& v );

	CPPTextureMap m_textureMap;
	ofImage* m_pErrorTexture;

	static CPPBitmapDataResourceManager* ms_pInstance;

	CPPBitmapDataResourceManager( const CPPBitmapDataResourceManager& );
	CPPBitmapDataResourceManager& operator=( const CPPBitmapDataResourceManager& );
};

#endif
