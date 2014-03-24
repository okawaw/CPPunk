#ifndef BASE_WORLD_H
#define BASE_WORLD_H

#include "BaseEntity.h"
#include "BaseEntityDefs.h"

#include <vector>

#include "ofEvents.h"

class BaseWorld
{
public:
	BaseWorld();
	virtual ~BaseWorld();

	// virtual functions called by StateHandler
	virtual void setup();
	virtual void update();
	virtual void draw();

	virtual void keyPressed( int key );
	virtual void keyReleased( int key );
	virtual void mouseMoved( int x, int y );
	virtual void mouseDragged( int x, int y, int button );
	virtual void mousePressed( int x, int y, int button );
	virtual void mouseReleased( int x, int y, int button );
	virtual void windowResized( int w, int h );
	virtual void dragEvent( ofDragInfo dragInfo );
	virtual void gotMessage( ofMessage msg );

	void addEntity( BaseEntity* entity );

	BaseEntity* collideRect( BaseEntityTypes::id type, float rX, float rY, float rWidth, float rHeight, BaseEntity* except = NULL );
	void collideRectInto( BaseEntityTypes::id type, float rX, float rY, float rWidth, float rHeight, std::vector< BaseEntity* > into );

private:
	std::vector< BaseEntity* > m_entities;
};

#endif