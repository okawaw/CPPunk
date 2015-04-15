#ifndef CPP_TEXT_H_
#define CPP_TEXT_H_

#include "CPPBaseImage.h"

#include "ofTrueTypeFont.h"

#include <string>

class CPPText : public CPPBaseImage
{
public:
	CPPText( const std::string& text, bool autoCleanup = false, float offsetX = 0, float offsetY = 0 );
	virtual ~CPPText();

	virtual void update();
	virtual void drawImage( float x, float y );

	unsigned int getSize() const;
	void setSize( const unsigned int size );
	std::string getFont() const;
	void setFont( const std::string& font );
	std::string getText() const;
	void setText( const std::string& text );
	bool isAntiAliased() const;
	void setAntiAliased( const bool antiAliased );
	float getLineHeight() const;
	void setLineHeight( const float lineHeight );
	float getLetterSpacing() const;
	void setLetterSpacing( const float letterSpacing );
	float getSpaceSize() const;
	void setSpaceSize( const float spaceSize );

	static unsigned int getDefaultSize();
	static void setDefaultSize( const unsigned int size );
	static std::string getDefaultFont();
	static void setDefaultFont( const std::string& font );
	static bool isDefaultAntiAliased();
	static void setDefaultAntiAliased( const bool antiAliased );
	static float getDefaultLetterSpacing();
	static void setDefaultLetterSpacing( const float letterSpacing );
	static float getDefaultSpaceSize();
	static void setDefaultSpaceSize( const float spaceSize );

	virtual float getWidth() const;
	virtual float getHeight() const;

	virtual float getScaledWidth() const;
	virtual void setScaledWidth( const float w );

	virtual float getScaledHeight() const;
	virtual void setScaledHeight( const float h );

	void lock();
	void unlock();

protected:

private:
	void reloadFont();
	void updateFont();

	ofTrueTypeFont* m_pTrueTypeFont;

	unsigned int m_size;
	unsigned int m_nextSize;
	std::string m_font;
	std::string m_nextFont;
	std::string m_text;
	bool m_bAntiAliased;
	bool m_bNextAntiAliased;
	bool m_bLocked;
	bool m_bNeedsUpdate;
	float m_defaultLineHeight;
	float m_lineHeight;
	float m_letterSpacing;
	float m_spaceSize;

	// Static default parameters
	static unsigned int ms_size;             // The font to assign to new CPPText objects.
	static std::string ms_font;              // The font size to assign to new CPPText objects.
	static bool ms_bAntiAliased;             // The anti-aliasing property to assign to new CPPText objects.
	static float ms_letterSpacing;           // The spacing between letters factor to assign to new CPPText objects.
	static float ms_spaceSize;               // The space size factor to assign to new CPPText objects.

	CPPText( const CPPText& );
	CPPText& operator=( const CPPText& );
};

#endif
