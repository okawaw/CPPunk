#include "CPP.h"

#include "ofImage.h"

#include <stdlib.h>

static const unsigned int ERROR_IMAGE_WIDTH = 32;
static const unsigned int ERROR_IMAGE_HEIGHT = 32;

CPP::CPPResourceManager::CPPResourceManager() :
  m_pErrorTexture( NULL )
{
}

CPP::CPPResourceManager::~CPPResourceManager()
{
	for ( std::map< std::string, std::pair< ofTexture*, unsigned int > >::iterator i = m_dataMap.begin(); i != m_dataMap.end(); ++i )
	{
		delete ( i->second.first );
	}

	delete m_pErrorTexture;
}

ofTexture* CPP::CPPResourceManager::useTexture( const std::string& key )
{
	std::map< std::string, std::pair< ofTexture*, unsigned int > >::iterator i = m_dataMap.find( key );

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
		ofTexture* newTex = new ofTexture();
		if ( !ofLoadImage( *newTex, key ) )
		{
			delete newTex;

			std::cerr << "ERROR: the file \"" << key << "\" could not be loaded." << std::endl;

			if ( !m_pErrorTexture )
			{
				m_pErrorTexture = new ofTexture();

				// Create a red box texture.
				const unsigned int errorDataSize = ERROR_IMAGE_WIDTH * ERROR_IMAGE_HEIGHT * 3;
				unsigned char errorData[ errorDataSize ];
				for ( unsigned int i = 0; i < errorDataSize; i += 3 )
				{
					errorData[ i ] = 0xee;
					errorData[ i + 1 ] = 0;
					errorData[ i + 2 ] = 0;
				}

				m_pErrorTexture->allocate( ERROR_IMAGE_WIDTH, ERROR_IMAGE_HEIGHT, GL_RGB );
				m_pErrorTexture->loadData( errorData, ERROR_IMAGE_WIDTH, ERROR_IMAGE_HEIGHT, GL_RGB );
			}

			return m_pErrorTexture;
		}

		m_dataMap.insert( std::pair< std::string, std::pair< ofTexture*, unsigned int > >( key, std::pair< ofTexture*, unsigned int >( newTex, 1 ) ) );

		return newTex;
	}
}

void CPP::CPPResourceManager::releaseTexture( const std::string& key )
{
	std::map< std::string, std::pair< ofTexture*, unsigned int > >::iterator i = m_dataMap.find( key );

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
