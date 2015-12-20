#include "CPPBitmapDataResourceManager.h"

#include <algorithm>
#include <stdlib.h>

static const unsigned int ERROR_IMAGE_WIDTH = 32;
static const unsigned int ERROR_IMAGE_HEIGHT = 32;

CPPBitmapDataResourceManager* CPPBitmapDataResourceManager::ms_pInstance = NULL;

CPPBitmapDataResourceManager::CPPBitmapDataResourceManager() :
  m_pErrorTexture( NULL )
{
}

CPPBitmapDataResourceManager::~CPPBitmapDataResourceManager()
{
	std::for_each( m_textureMap.begin(), m_textureMap.end(), deleteTexture );

	delete m_pErrorTexture;
}

void CPPBitmapDataResourceManager::initialize()
{
	if ( !ms_pInstance )
	{
		ms_pInstance = new CPPBitmapDataResourceManager();
	}
}

void CPPBitmapDataResourceManager::destroy()
{
	delete ms_pInstance;
	ms_pInstance = NULL;
}

CPPBitmapDataResourceManager* CPPBitmapDataResourceManager::getInstance()
{
	return ms_pInstance;
}

ofImage* CPPBitmapDataResourceManager::useTexture( const std::string& fileName )
{
	CPPTextureMap::iterator i = m_textureMap.find( fileName );

	// Resource already exists.
	if ( i != m_textureMap.end() && !( m_textureMap.key_comp()( fileName, i->first ) ) )
	{
		++( i->second.second );
		return i->second.first;
	}
	// Resource is not in GPU memory.
	// Load the resource.
	else
	{
		ofImage* newTexture = new ofImage();
		if ( !newTexture->loadImage( fileName ) )
		{
			delete newTexture;

			std::cerr << "ERROR: the file \"" << fileName << "\" could not be loaded." << std::endl;

			if ( !m_pErrorTexture )
			{
				m_pErrorTexture = new ofImage();

				// Create a red box texture.
				const unsigned int errorDataSize = ERROR_IMAGE_WIDTH * ERROR_IMAGE_HEIGHT * 4;
				unsigned char errorData[ errorDataSize ];
				for ( unsigned int i = 0; i < errorDataSize; i += 4 )
				{
					errorData[ i ]     = 0xee; // red
					errorData[ i + 1 ] = 0x00; // green
					errorData[ i + 2 ] = 0x00; // blue
					errorData[ i + 3 ] = 0xff; // alpha
				}

				m_pErrorTexture->allocate( ERROR_IMAGE_WIDTH, ERROR_IMAGE_HEIGHT, OF_IMAGE_COLOR_ALPHA );
				m_pErrorTexture->setFromPixels( errorData, ERROR_IMAGE_WIDTH, ERROR_IMAGE_HEIGHT, OF_IMAGE_COLOR_ALPHA );
			}

			return m_pErrorTexture;
		}

		// In case the resource image was not an RGBA image.
		newTexture->setImageType( OF_IMAGE_COLOR_ALPHA );

		m_textureMap.insert( i, CPPTextureMap::value_type( fileName, std::make_pair( newTexture, 1 ) ) );

		return newTexture;
	}
}

void CPPBitmapDataResourceManager::releaseTexture( const std::string& fileName )
{
	CPPTextureMap::iterator i = m_textureMap.find( fileName );

	// The resource doesn't exist in memory.
	if ( i == m_textureMap.end() )
	{
		std::cerr << "ERROR: the resource \"" << fileName << "\" is not loaded." << std::endl;
		return;
	}
	else
	{
		// Decrement retain count, if the retain count is now 0.
		if ( --( i->second.second ) == 0 )
		{
			delete ( i->second.first );

			m_textureMap.erase( i );
		}
	}
}

void CPPBitmapDataResourceManager::deleteTexture( CPPTextureMap::value_type& v )
{
	delete v.second.first;
}

