#include "CPPText.h"

#include "utils/CPPTextResourceManager.h"

// TODO: Get these defaults and from CPPTextResourceManager from one location.
unsigned int CPPText::ms_size = 16;        // The font to assign to new CPPText objects.
std::string CPPText::ms_font = "default";  // The font size to assign to new CPPText objects.
bool CPPText::ms_bAntiAliased = true;      // The anti-aliasing property to assign to new CPPText objects.
float CPPText::ms_letterSpacing = 1.0;     // The spacing between letters factor to assign to new CPPText objects.
float CPPText::ms_spaceSize = 1.0;         // The space size factor to assign to new CPPText objects.

CPPText::CPPText( const std::string& text, bool autoCleanup/* = false*/, float offsetX/* = 0*/, float offsetY/* = 0*/ ) :
  CPPBaseImage( autoCleanup )
, m_pTrueTypeFont( CPPTextResourceManager::getInstance()->useFont( ms_font, ms_size, ms_bAntiAliased ) )
, m_size( ms_size )
, m_nextSize( m_size )
, m_font( ms_font )
, m_nextFont( m_font )
, m_text( text )
, m_bAntiAliased( ms_bAntiAliased )
, m_bNextAntiAliased( m_bAntiAliased )
, m_bLocked( false )
, m_bNeedsUpdate( false )
, m_defaultLineHeight( m_pTrueTypeFont->getLineHeight() )
, m_lineHeight( m_defaultLineHeight )
, m_letterSpacing( ms_letterSpacing )
, m_spaceSize( ms_spaceSize )
{
	m_posX = offsetX;
	m_posY = offsetY;
}

CPPText::~CPPText()
{
	CPPTextResourceManager::getInstance()->releaseFont( m_font, m_size, m_bAntiAliased );
}

unsigned int CPPText::getSize() const { return m_size; }
void CPPText::setSize( const unsigned int size )
{
	m_nextSize = size;
	reloadFont();
}

std::string CPPText::getFont() const { return m_font; }
void CPPText::setFont( const std::string& font )
{
	m_nextFont = font;
	reloadFont();
}

bool CPPText::isAntiAliased() const { return m_bAntiAliased; }
void CPPText::setAntiAliased( const bool antiAliased )
{
	m_bNextAntiAliased = antiAliased;
	reloadFont();
}

float CPPText::getLineHeight() const { return m_lineHeight; }
void CPPText::setLineHeight( const float lineHeight) { m_lineHeight = lineHeight; }

std::string CPPText::getText() const { return m_text; }
void CPPText::setText( const std::string& text ) { m_text = text; }

float CPPText::getLetterSpacing() const { return m_letterSpacing; }
void CPPText::setLetterSpacing( const float letterSpacing ) { m_letterSpacing = letterSpacing; }

float CPPText::getSpaceSize() const { return m_spaceSize; }
void CPPText::setSpaceSize( const float spaceSize ) { m_spaceSize = spaceSize; }

unsigned int CPPText::getDefaultSize() { return ms_size; }
void CPPText::setDefaultSize( const unsigned int size ) { ms_size = size; }

std::string CPPText::getDefaultFont() { return ms_font; }
void CPPText::setDefaultFont( const std::string& font ) { ms_font = font; }

bool CPPText::isDefaultAntiAliased() { return ms_bAntiAliased; }
void CPPText::setDefaultAntiAliased( const bool antiAliased ) { ms_bAntiAliased = antiAliased; }

float CPPText::getDefaultLetterSpacing() { return ms_letterSpacing; }
void CPPText::setDefaultLetterSpacing( const float letterSpacing ) { ms_letterSpacing = letterSpacing; }

float CPPText::getDefaultSpaceSize() { return ms_spaceSize; }
void CPPText::setDefaultSpaceSize( const float spaceSize ) { ms_spaceSize = spaceSize; }

float CPPText::getWidth() const
{
	return m_pTrueTypeFont->stringWidth( m_text );
}

float CPPText::getHeight() const
{
	return m_pTrueTypeFont->stringHeight( m_text );
}

float CPPText::getScaledWidth() const
{
	return getWidth() * m_scaleX * m_scale;
}
void CPPText::setScaledWidth( const float w )
{
	m_scaleX = w / m_scale / getWidth();
}

float CPPText::getScaledHeight() const
{
	return getHeight() * m_scaleY * m_scale;
}

void CPPText::setScaledHeight( const float h )
{
	m_scaleY = h / m_scale / getHeight();
}

void CPPText::lock()
{
	m_bLocked = true;
}

void CPPText::unlock()
{
	m_bLocked = false;
	if ( m_bNeedsUpdate )
	{
		reloadFont();
	}
	m_bNeedsUpdate = false;
}

void CPPText::reloadFont()
{
	if ( m_bLocked )
	{
		m_bNeedsUpdate = true;
		return;
	}
	if ( m_font != m_nextFont || m_size != m_nextSize || m_bAntiAliased != m_bNextAntiAliased )
	{
		CPPTextResourceManager::getInstance()->releaseFont( m_font, m_size, m_bAntiAliased );
		m_pTrueTypeFont = CPPTextResourceManager::getInstance()->useFont( m_nextFont, m_nextSize, m_bNextAntiAliased );
		m_font = m_nextFont;
		m_size = m_nextSize;
		m_bAntiAliased = m_bNextAntiAliased;
		m_defaultLineHeight = m_pTrueTypeFont->getLineHeight();
	}
}

void CPPText::updateFont()
{
	m_pTrueTypeFont->setLineHeight( m_lineHeight );
	m_pTrueTypeFont->setLetterSpacing( m_letterSpacing );
	m_pTrueTypeFont->setSpaceSize( m_spaceSize );
}

void CPPText::update()
{
}

void CPPText::drawImage( float x, float y )
{
	// Any other parameters setting before rendering.
	updateFont();
	m_pTrueTypeFont->drawString( m_text, x + m_posX, y + m_posY + m_lineHeight );
}
