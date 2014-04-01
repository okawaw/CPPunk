#ifndef CPP_BASE_WORLD_H_
#define CPP_BASE_WORLD_H_

#include "BaseEntity.h"
#include "BaseEntityDefs.h"

#include <set>

#include "ofEvents.h"

class CPPBaseWorld
{
public:
	CPPBaseWorld();
	virtual ~CPPBaseWorld();

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

	void addEntity( CPPBaseEntity* entity, bool quiet = false );
	CPPBaseEntity* removeEntity( CPPBaseEntity* entity, bool quiet = false );
	void updateEntityLayer( CPPBaseEntity* entity, int layer );

	CPPBaseEntity* collideRect( BaseEntityTypes::id type, float rX, float rY, float rWidth, float rHeight, const CPPBaseEntity* except = NULL ) const;
	void collideRectInto( BaseEntityTypes::id type, float rX, float rY, float rWidth, float rHeight, std::vector< CPPBaseEntity* >& into, const CPPBaseEntity* except = NULL ) const;

private:
	std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp > m_entities;
};

#endif
