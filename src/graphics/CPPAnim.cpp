#include "CPPSpritemap.h"

CPPSpritemap::CPPAnim::CPPAnim( const std::string& name,
                                unsigned int numFrames,
                                unsigned int* frames,
                                float frameRate,
                                bool loop ) :
  m_numFrames( numFrames )
, m_pFrames( frames )
, m_bLoop( loop )
, m_frameRate( frameRate )
, m_name( name )
{
}

CPPSpritemap::CPPAnim::~CPPAnim()
{
	delete[] m_pFrames;
}
