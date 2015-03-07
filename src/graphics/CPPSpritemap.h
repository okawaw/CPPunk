#ifndef CPP_SPRITEMAP_H_
#define CPP_SPRITEMAP_H_

#include "CPPImage.h"

#include <map>
#include <string>
#include <vector>

class CPPBitmapData;

class CPPSpritemap : public CPPImage
{
private:
	class CPPAnim
	{
		public:
			CPPAnim( const std::string& name,
			         unsigned int numFrames,
			         unsigned int* frames,
			         float frameRate,
			         bool loop );
			~CPPAnim();

			unsigned int m_numFrames;
			unsigned int* m_pFrames;
			bool m_bLoop;
			float m_frameRate;
			std::string m_name;
	};

public:
	CPPSpritemap( const CPPBitmapData& source,
	              bool autoCleanup = false,
	              unsigned int frameWidth = 0,
	              unsigned int frameHeight = 0 );
	virtual ~CPPSpritemap();

	virtual void update();

	CPPAnim* add( const std::string& name,
	              const std::vector< unsigned int >& frames,
	              float frameRate = 0,
	              bool loop = true );

	CPPAnim* play( const std::string& name,
	               bool reset = false,
	               unsigned int frame = 0 );
private:
	void updateClipRect();

protected:
	bool m_bComplete;         // If the animation has stopped.
	float m_rate;             // Animation speed factor, alter this to speed up/slow down all animations.

	unsigned int m_sourceWidth;
	unsigned int m_sourceHeight;

	float m_timer;

private:
	unsigned int m_columns;
	unsigned int m_rows;
	unsigned int m_frameCount;

	CPPAnim* m_pAnim;
	unsigned int m_index;      // Animation frame index.
	unsigned int m_frame;      // Frame number of source.

	std::map< std::string, CPPAnim* > m_anims;

	CPPSpritemap( const CPPSpritemap& );
	CPPSpritemap& operator=( const CPPSpritemap& );

};

#endif
