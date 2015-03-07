#include "CPP.h"

#include <stdlib.h>

#include "ofPixels.h"

static const unsigned int ERROR_IMAGE_WIDTH = 32;
static const unsigned int ERROR_IMAGE_HEIGHT = 32;

CPP::CPPResourceManager::CPPResourceManager() :
  m_pErrorTexture( NULL )
{
}

CPP::CPPResourceManager::~CPPResourceManager()
{
	for ( std::map< std::string, std::pair< ofImage*, unsigned int > >::iterator i = m_dataMap.begin(); i != m_dataMap.end(); ++i )
	{
		delete ( i->second.first );
	}

	delete m_pErrorTexture;
}

ofImage* CPP::CPPResourceManager::useTexture( const std::string& key )
{
	std::map< std::string, std::pair< ofImage*, unsigned int > >::iterator i = m_dataMap.find( key );

	// Resource already exists.
	if ( i != m_dataMap.end() )
	{
		++( i->second.second );
		return i->second.first;
	}
	// Resource is not in GPU memory.
	// Load the resource.
	else
	{
		ofImage* newTex = new ofImage();
		if ( !newTex->loadImage( key ) )
		{
			delete newTex;

			std::cerr << "ERROR: the file \"" << key << "\" could not be loaded." << std::endl;

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
		newTex->setImageType( OF_IMAGE_COLOR_ALPHA );

		m_dataMap.insert( std::pair< std::string, std::pair< ofImage*, unsigned int > >( key, std::pair< ofImage*, unsigned int >( newTex, 1 ) ) );

		return newTex;
	}
}

void CPP::CPPResourceManager::releaseTexture( const std::string& key )
{
	std::map< std::string, std::pair< ofImage*, unsigned int > >::iterator i = m_dataMap.find( key );

	// The resource doesn't exist in memory.
	if ( i == m_dataMap.end() )
	{
		std::cerr << "ERROR: the resource \"" << key << "\" is not loaded." << std::endl;
		return;
	}
	else
	{
		// Retain count is 0.
		if ( --( i->second.second ) == 0 )
		{
			delete ( i->second.first );

			m_dataMap.erase( i );
		}
	}
}
