#include "CPPBitmapData.h"

#include "../CPP.h"

CPPBitmapData::CPPBitmapData( const std::string& source ) :
  m_pTexture( CPP::ms_resourceManager.useTexture( source ) )
, m_source( source )
{
}

CPPBitmapData::CPPBitmapData( const CPPBitmapData& other ) :
  m_pTexture( CPP::ms_resourceManager.useTexture( other.m_source ) )
, m_source( other.m_source )
{
}

CPPBitmapData& CPPBitmapData::operator=( const CPPBitmapData& other )
{
	if ( this != &other )
	{
		CPP::ms_resourceManager.releaseTexture( m_source );
		m_pTexture = CPP::ms_resourceManager.useTexture( other.m_source );

		m_source = other.m_source;
	}
	return *this;
}

CPPBitmapData::~CPPBitmapData()
{
	CPP::ms_resourceManager.releaseTexture( m_source );
}
