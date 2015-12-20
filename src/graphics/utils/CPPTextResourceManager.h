#ifndef CPP_TEXT_RESOURCE_MANAGER_H_
#define CPP_TEXT_RESOURCE_MANAGER_H_

#include <map>
#include <string>

class ofTrueTypeFont;

class CPPTextResourceManager
{
	friend class CPP;
	friend class CPPText;
private:
	// < < fontName, < fontSize, antiAliased > >, < ofTrueTypeFontPointer, retainCount > >
	typedef std::map< std::pair< std::string, std::pair< unsigned int, bool > >, std::pair< ofTrueTypeFont*, unsigned int > > CPPFontMap;

	CPPTextResourceManager();
	~CPPTextResourceManager();

	static void initialize();
	static void destroy();
	static CPPTextResourceManager* getInstance();

	ofTrueTypeFont* useFont( const std::string& fontName, unsigned int fontSize, bool antiAliased );
	void releaseFont( const std::string& fontName, unsigned int fontSize, bool antiAliased );

	static void deleteFont( CPPFontMap::value_type& v );

	CPPFontMap m_fontMap;
	ofTrueTypeFont* m_pErrorFont;

	static CPPTextResourceManager* ms_pInstance;

	CPPTextResourceManager( const CPPTextResourceManager& );
	CPPTextResourceManager& operator=( const CPPTextResourceManager& );
};

#endif
