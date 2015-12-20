#include "CPPBitmapData.h"

#include "utils/CPPBitmapDataResourceManager.h"

CPPBitmapData::CPPBitmapData( const std::string& source ) :
  m_pTexture( CPPBitmapDataResourceManager::getInstance()->useTexture( source ) )
, m_source( source )
{
}

CPPBitmapData::CPPBitmapData( const CPPBitmapData& other ) :
  m_pTexture( CPPBitmapDataResourceManager::getInstance()->useTexture( other.m_source ) )
, m_source( other.m_source )
{
}

CPPBitmapData& CPPBitmapData::operator=( const CPPBitmapData& other )
{
	if ( this != &other )
	{
		CPPBitmapDataResourceManager::getInstance()->releaseTexture( m_source );
		m_pTexture = CPPBitmapDataResourceManager::getInstance()->useTexture( other.m_source );

		m_source = other.m_source;
	}
	return *this;
}

CPPBitmapData::~CPPBitmapData()
{
	CPPBitmapDataResourceManager::getInstance()->releaseTexture( m_source );
}
