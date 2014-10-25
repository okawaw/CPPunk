#include "CPPSpritemap.h"

#include "../CPP.h"

#include "ofTexture.h"

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <utility>

CPPSpritemap::CPPSpritemap( const std::string& source,
                            bool autoCleanup/* = false */,
                            unsigned int frameWidth/* = 0 */,
                            unsigned int frameHeight/* = 0 */ ) :
  CPPImage( source, autoCleanup, true, 0, 0, frameWidth, frameHeight )
, m_bComplete( true )
, m_rate( 1 )
, m_sourceWidth( m_pTexture->getWidth() )
, m_sourceHeight( m_pTexture->getHeight() )
, m_timer( 0 )
, m_columns( ( unsigned int )std::ceil( m_sourceWidth / m_clipRectWidth ) )
, m_rows( ( unsigned int )std::ceil( m_sourceHeight / m_clipRectHeight ) )
, m_frameCount( m_columns * m_rows )
, m_pAnim( NULL )
, m_index( 0 )
, m_frame( 0 )
{
	m_bActive = true;
}

CPPSpritemap::~CPPSpritemap()
{
	for ( std::map< std::string, CPPAnim* >::iterator i = m_anims.begin(); i != m_anims.end(); ++i )
	{
		delete i->second;
	}
}

void CPPSpritemap::update()
{
	if ( m_pAnim && !m_bComplete )
	{
		float timeAdd = m_pAnim->m_frameRate * m_rate;
		if ( !CPP::getTimeInFrames() )
		{
			timeAdd *= CPP::getElapsed();
		}
		m_timer += timeAdd;

		if ( m_timer >= 1 )
		{
			while ( m_timer >= 1 )
			{
				m_timer -= 1.0f;
				++m_index;

				if ( m_index == m_pAnim->m_numFrames )
				{
					if ( m_pAnim->m_bLoop )
					{
						m_index = 0;
					}
					else
					{
						m_index = m_pAnim->m_numFrames - 1;
						m_bComplete = true;
						break;
					}
				}
			}
			m_frame = m_pAnim->m_pFrames[ m_index ];
			updateClipRect();
		}
	}
}

CPPSpritemap::CPPAnim* CPPSpritemap::add( const std::string& name,
                                          const std::vector< unsigned int >& frames,
                                          float frameRate/* = 0 */,
                                          bool loop/* = true */ )
{
	const unsigned int size = frames.size();
	unsigned int* newFrames = new unsigned int[ size ];
	for ( unsigned int i = 0; i < size; ++i )
	{
		newFrames[ i ] = frames[ i ] % m_frameCount;
	}

	CPPAnim* newAnim = new CPPAnim( name, size, newFrames, frameRate, loop );

	std::pair< std::map< std::string, CPPAnim* >::iterator, bool > ret = m_anims.insert( std::make_pair( name, newAnim ) );
	if ( !ret.second )
	{
		std::cerr << "WARNING: \"" << name << "\" is already a registered animation and is being replaced." << std::endl;
		delete ret.first->second;
		ret.first->second = newAnim;
	}

	return newAnim;
}

CPPSpritemap::CPPAnim* CPPSpritemap::play( const std::string& name,
                                           bool reset/* = false */,
                                           unsigned int frame/* = 0 */ )
{
	if ( !reset && m_pAnim && m_pAnim->m_name == name )
	{
		return m_pAnim;
	}

	CPPAnim* ret;

	std::map< std::string, CPPAnim* >::iterator anim = m_anims.find( name );
	if ( anim == m_anims.end() )
	{
		std::cerr << "ERROR: \"" << name << "\" is not a registered animation." << std::endl;

		m_frame = 0;
		m_index = 0;
		m_bComplete = true;

		ret = NULL;
	}
	else
	{
		m_index = 0;
		m_timer = 0;
		m_frame = anim->second->m_pFrames[ frame % anim->second->m_numFrames ];
		m_bComplete = false;

		ret = anim->second;
	}

	m_pAnim = ret;
	return ret;
}

void CPPSpritemap::updateClipRect()
{
	m_clipRectPosX = m_clipRectWidth * ( m_frame % m_columns );
	m_clipRectPosY = m_clipRectHeight * ( m_frame / m_columns );
}

