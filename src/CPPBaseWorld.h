#ifndef CPP_BASE_WORLD_H_
#define CPP_BASE_WORLD_H_

#include "CPPBaseEntity.h"

#include <map>
#include <set>

#include "ofEvents.h"

class CPPBaseWorld
{
public:
	CPPBaseWorld( bool autoCleanup = false );
	virtual ~CPPBaseWorld();

	// Override this; called when World is switch to, and set to the currently active world.
	virtual void begin();
	// Override this; called when World is changed, and the active world is no longer this.
	virtual void end();

	// Override this; can be used as an initializer function.
	virtual void setup();
	// Performed by the game loop, updates all contained Entities.
	// If you override this to give your World update code, remember
	// to call CPPBaseWorld::update() or your Entities will not be
	// updated.
	virtual void update();
	// Performed by the game loop, renders all contained Entities.
	// If you override this to give your World render code, remember
	// to call CPPBaseWorld::render() or your Entities will not be
	// rendered.
	virtual void draw();

	// Override these; called when the particular event is performed.
	virtual void keyPressed( int key );
	virtual void keyReleased( int key );
	virtual void mouseMoved( int x, int y );
	virtual void mouseDragged( int x, int y, int button );
	virtual void mousePressed( int x, int y, int button );
	virtual void mouseReleased( int x, int y, int button );
	virtual void windowResized( int w, int h );
	virtual void dragEvent( ofDragInfo dragInfo );
	virtual void gotMessage( ofMessage msg );

	bool isActive() const;
	void setActive( const bool active );

	bool isVisible() const;
	void setVisible( const bool visible );

	bool isAutoCleanup() const;

	void updateEntityLayer( CPPBaseEntity* entity, int layer );

	// Adds the Entity to the World at the end of the frame.
	// Note: This function doesn't detect duplicates.
	CPPBaseEntity* add( CPPBaseEntity* entity );
	// Removes the Entity to the World at the end of the frame.
	// Note: This function doesn't detect duplicates.
	CPPBaseEntity* remove( CPPBaseEntity* entity );
	// Removes all Entities from the World at the end of the frame.
	void removeAll();
	// Adds multiple Entities to the world.
	void addList( std::vector< CPPBaseEntity* >& list );
	// Removes multiple Entities to the world.
	void removeList( std::vector< CPPBaseEntity* >& list );

	// Returns the first Entity that collides with the rectangular area.
	CPPBaseEntity* collideRect( unsigned int type, float rX, float rY, float rWidth, float rHeight, const CPPBaseEntity* except = NULL ) const;
	// Returns the first Entity found that collides with the position.
	CPPBaseEntity* collidePoint( unsigned int type, float pX, float pY, const CPPBaseEntity* except = NULL ) const;
	// Returns the first Entity found that collides with the line.
	CPPBaseEntity* collideLine( unsigned int type, int fromX, int fromY, int toX, int toY, int& pX, int& pY, unsigned int precision = 1, const CPPBaseEntity* except = NULL ) const;
	CPPBaseEntity* collideLine( unsigned int type, int fromX, int fromY, int toX, int toY, unsigned int precision = 1, const CPPBaseEntity* except = NULL ) const;
	// Populates a vector with all Entities that collide with the rectangle. This
	// function does not empty the array, that responsibility is left to the user.
	void collideRectInto( unsigned int type, float rX, float rY, float rWidth, float rHeight, std::vector< CPPBaseEntity* >& into, const CPPBaseEntity* except = NULL ) const;
	// Populates a vector with all Entities that collide with the position. This
	// function does not empty the array, that responsibility is left to the user.
	void collidePointInto( unsigned int type, float pX, float pY, std::vector< CPPBaseEntity* >& into, const CPPBaseEntity* except = NULL ) const;
	
	// Finds the Entity nearest to the rectangle.
	CPPBaseEntity* nearestToRect( unsigned int type, float x, float y, float width, float height, const CPPBaseEntity* except = NULL ) const;
	// Finds the Entity nearest to another.
	CPPBaseEntity* nearestToEntity( unsigned int type, const CPPBaseEntity* e, bool useHitboxes = false, CPPBaseEntity* except = NULL ) const;
	// Finds the Entity nearest to the position.
	CPPBaseEntity* nearestToPoint( unsigned int type, float x, float y, bool useHitBoxes = false, CPPBaseEntity* except = NULL ) const;

	// Returns the amount of Entities in the World.
	unsigned int count() const;
	// Returns the amount of Entities of the type are in the World.
	unsigned int typeCount( unsigned int type ) const;

	// The Entity that will be rendered first by the World.
	CPPBaseEntity* farthest() const;
	// The Entity that will be rendered last by the World.
	CPPBaseEntity* nearest() const;
	// The layer that will be rendered first by the World.
	int layerFarthest() const;
	// The layer that will be rendered last by the World.
	int layerNearest() const;

	// Pushes all Entities in the World of the type into the Vector.
	void getType( unsigned int type, std::vector< CPPBaseEntity* >& into ) const;
	// Pushes all Entities in the World on the layer into the Vector.
	void getLayer( int layer, std::vector< CPPBaseEntity* >& into ) const;
	// Pushes all Entities in the World into the Vector.
	void getAll( std::vector< CPPBaseEntity* >& into ) const;

	// Updates the add/remove lists at the end of the frame.
	void updateLists( bool shouldAdd = true );

protected:
	bool m_bActive;                   // If the World should update.
	bool m_bVisible;                  // If the render() loop is performed.

private:
	// Cleanup.
	const bool m_bAutoCleanup;                                     // If the World should be auto deallocated when switched out.

	// Entity records.
	std::set< CPPBaseEntity*, CPPBaseEntity::ptrCmp > m_entities;  // Set of all entities within this World.
	std::map< unsigned int, unsigned int > m_typeCount;            // Map for keeping track of entity type counts.                   // TODO: use update this...

	// Adding and Removal.
	std::vector< CPPBaseEntity* > m_add;                           // Vector of entities to be added.
	std::vector< CPPBaseEntity* > m_remove;                        // Vector of entities to be removed.

	static CPPBaseEntity::EntityKey m_entityKey;

	CPPBaseWorld( const CPPBaseWorld& );
	CPPBaseWorld& operator=( const CPPBaseWorld& );
};

#endif
