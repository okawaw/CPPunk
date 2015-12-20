#include "CPPTextResourceManager.h"

#include "ofTrueTypeFont.h"

#include <algorithm>
#include <stdlib.h>

static const unsigned int DEFAULT_FONT_SIZE = 16;
static const char DEFAULT_FONT[] = "default";

CPPTextResourceManager* CPPTextResourceManager::ms_pInstance = NULL;

CPPTextResourceManager::CPPTextResourceManager() :
  m_pErrorFont( NULL )
{
}

CPPTextResourceManager::~CPPTextResourceManager()
{
	std::for_each( m_fontMap.begin(), m_fontMap.end(), deleteFont);

	delete m_pErrorFont;
}

void CPPTextResourceManager::initialize()
{
	if ( !ms_pInstance )
	{
		ms_pInstance = new CPPTextResourceManager();
	}
}

void CPPTextResourceManager::destroy()
{
	delete ms_pInstance;
	ms_pInstance = NULL;
}

CPPTextResourceManager* CPPTextResourceManager::getInstance()
{
	return ms_pInstance;
}

ofTrueTypeFont* CPPTextResourceManager::useFont( const std::string& fontName, unsigned int fontSize, bool antiAliased )
{
	CPPFontMap::key_type key( fontName, std::make_pair( fontSize, antiAliased ) );
	CPPFontMap::iterator i = m_fontMap.lower_bound( key );

	// Resource already exists.
	if ( i != m_fontMap.end() && !( m_fontMap.key_comp()( key, i->first ) ) )
	{
		++( i->second.second );
		return i->second.first;
	}
	// Resource is not in GPU memory.
	// Load the resource.
	else
	{
		ofTrueTypeFont* newFont = new ofTrueTypeFont();
		if ( !newFont->loadFont( fontName, fontSize, antiAliased ) ) // TODO: Load with other ofTrueTypeFont::loadFont parameters non-default?
		{
			delete newFont;

			std::cerr << "ERROR: the font \"" << fontName
			          << "\" in size " << fontSize
			          << ", with" << ( antiAliased ? "" : "out" ) << " anti-aliasing could not be loaded." << std::endl;

			if ( !m_pErrorFont )
			{
				m_pErrorFont = new ofTrueTypeFont();
				m_pErrorFont->loadFont( DEFAULT_FONT, DEFAULT_FONT_SIZE );
			}

			return m_pErrorFont;
		}

		m_fontMap.insert( i, CPPFontMap::value_type( key, std::make_pair( newFont, 1 ) ) );

		return newFont;
	}
}

void CPPTextResourceManager::releaseFont( const std::string& fontName, unsigned int fontSize, bool antiAliased )
{
	CPPFontMap::iterator i = m_fontMap.find( CPPFontMap::key_type( fontName, std::make_pair( fontSize, antiAliased ) ) );

	// The resource doesn't exist in memory.
	if ( i == m_fontMap.end() )
	{
		std::cerr << "ERROR: the font \"" << fontName << "\" in size " << fontSize << " is not loaded." << std::endl;
		return;
	}
	else
	{
		// Decrement retain count, if the retain count is now 0.
		if ( --( i->second.second ) == 0 )
		{
			delete ( i->second.first );

			m_fontMap.erase( i );
		}
	}
}

void CPPTextResourceManager::deleteFont( CPPFontMap::value_type& v )
{
	delete v.second.first;
}
