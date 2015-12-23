//#include "CPP.h"
//
//#include <stdlib.h>
//
//#include "ofPixels.h"
//
//static const unsigned int ERROR_IMAGE_WIDTH = 32;
//static const unsigned int ERROR_IMAGE_HEIGHT = 32;
//
//static const unsigned int DEFAULT_FONT_SIZE = 16;
//static const char DEFAULT_FONT[] = "default";
//
//CPP::CPPResourceManager::CPPResourceManager() :
//  m_pErrorTexture( NULL )
//, m_pErrorFont( NULL )
//{
//}
//
//CPP::CPPResourceManager::~CPPResourceManager()
//{
//	for ( std::map< std::string, std::pair< ofImage*, unsigned int > >::iterator i = m_textureMap.begin(); i != m_textureMap.end(); ++i )
//	{
//		delete ( i->second.first );
//	}
//
//	for ( std::map< std::pair< std::string, std::pair< unsigned int, bool > >, std::pair< ofTrueTypeFont*, unsigned int > >::iterator i = m_fontMap.begin(); i != m_fontMap.end(); ++i )
//	{
//		delete ( i->second.first );
//	}
//
//	delete m_pErrorTexture;
//	delete m_pErrorFont;
//}
//
//ofImage* CPP::CPPResourceManager::useTexture( const std::string& fileName )
//{
//	std::map< std::string, std::pair< ofImage*, unsigned int > >::iterator i = m_textureMap.find( fileName );
//
//	// Resource already exists.
//	if ( i != m_textureMap.end() )
//	{
//		++( i->second.second );
//		return i->second.first;
//	}
//	// Resource is not in GPU memory.
//	// Load the resource.
//	else
//	{
//		ofImage* newTex = new ofImage();
//		if ( !newTex->loadImage( fileName ) )
//		{
//			delete newTex;
//
//			std::cerr << "ERROR: the file \"" << fileName << "\" could not be loaded." << std::endl;
//
//			if ( !m_pErrorTexture )
//			{
//				m_pErrorTexture = new ofImage();
//
//				// Create a red box texture.
//				const unsigned int errorDataSize = ERROR_IMAGE_WIDTH * ERROR_IMAGE_HEIGHT * 4;
//				unsigned char errorData[ errorDataSize ];
//				for ( unsigned int i = 0; i < errorDataSize; i += 4 )
//				{
//					errorData[ i ]     = 0xee; // red
//					errorData[ i + 1 ] = 0x00; // green
//					errorData[ i + 2 ] = 0x00; // blue
//					errorData[ i + 3 ] = 0xff; // alpha
//				}
//
//				m_pErrorTexture->allocate( ERROR_IMAGE_WIDTH, ERROR_IMAGE_HEIGHT, OF_IMAGE_COLOR_ALPHA );
//				m_pErrorTexture->setFromPixels( errorData, ERROR_IMAGE_WIDTH, ERROR_IMAGE_HEIGHT, OF_IMAGE_COLOR_ALPHA );
//			}
//
//			return m_pErrorTexture;
//		}
//
//		// In case the resource image was not an RGBA image.
//		newTex->setImageType( OF_IMAGE_COLOR_ALPHA );
//
//		m_textureMap.insert( std::pair< std::string, std::pair< ofImage*, unsigned int > >( fileName, std::pair< ofImage*, unsigned int >( newTex, 1 ) ) );
//
//		return newTex;
//	}
//}
//
//void CPP::CPPResourceManager::releaseTexture( const std::string& fileName )
//{
//	std::map< std::string, std::pair< ofImage*, unsigned int > >::iterator i = m_textureMap.find( fileName );
//
//	// The resource doesn't exist in memory.
//	if ( i == m_textureMap.end() )
//	{
//		std::cerr << "ERROR: the resource \"" << fileName << "\" is not loaded." << std::endl;
//		return;
//	}
//	else
//	{
//		// Retain count is 0.
//		if ( --( i->second.second ) == 0 )
//		{
//			delete ( i->second.first );
//
//			m_textureMap.erase( i );
//		}
//	}
//}
//
//ofTrueTypeFont* CPP::CPPResourceManager::useFont( const std::string& fontName, unsigned int fontSize, bool antiAliased )
//{
//	std::pair< std::string, std::pair< unsigned int, bool > > key( fontName, std::make_pair( fontSize, antiAliased ) );
//	std::map< std::pair< std::string, std::pair< unsigned int, bool > >, std::pair< ofTrueTypeFont*, unsigned int > >::iterator i = m_fontMap.find( key );
//
//	// Resource already exists.
//	if ( i != m_fontMap.end() )
//	{
//		++( i->second.second );
//		return i->second.first;
//	}
//	// Resource is not in GPU memory.
//	// Load the resource.
//	else
//	{
//		ofTrueTypeFont* newFont = new ofTrueTypeFont();
//		if ( !newFont->loadFont( fontName, fontSize, antiAliased ) ) // TODO: Load with other parameters non-default?
//		{
//			std::cerr << "ERROR: the font \"" << fontName
//			          << "\" in size " << fontSize
//			          << ", with" << ( antiAliased ? "" : "out" ) << " anti-aliasing could not be loaded." << std::endl;
//
//			if ( !m_pErrorFont )
//			{
//				newFont->loadFont( DEFAULT_FONT, DEFAULT_FONT_SIZE );
//				m_pErrorFont = newFont;
//			}
//			else
//			{
//				delete newFont;
//			}
//
//			return m_pErrorFont;
//		}
//
//		m_fontMap.insert( std::pair< std::pair< std::string, std::pair< unsigned int, bool > >,
//		                  std::pair< ofTrueTypeFont*, unsigned int > >( key, std::pair< ofTrueTypeFont*, unsigned int >( newFont, 1 ) ) );
//
//		return newFont;
//	}
//}
//
//void CPP::CPPResourceManager::releaseFont( const std::string& fontName, unsigned int fontSize, bool antiAliased )
//{
//	std::pair< std::string, std::pair< unsigned int, bool > > key( fontName, std::make_pair( fontSize, antiAliased ) );
//	std::map< std::pair< std::string, std::pair< unsigned int, bool > >, std::pair< ofTrueTypeFont*, unsigned int > >::iterator i = m_fontMap.find( key );
//
//	// The resource doesn't exist in memory.
//	if ( i == m_fontMap.end() )
//	{
//		std::cerr << "ERROR: the font \"" << fontName << "\" in size " << fontSize << " is not loaded." << std::endl;
//		return;
//	}
//	else
//	{
//		// Retain count is 0.
//		if ( --( i->second.second ) == 0 )
//		{
//			delete ( i->second.first );
//
//			m_fontMap.erase( i );
//		}
//	}
//}
