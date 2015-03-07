#ifndef CPP_BASE_ENTITY_H_
#define CPP_BASE_ENTITY_H_

#include "CPPBaseGraphic.h"

#include <vector>
#include <stdlib.h>

class CPPBaseWorld;

class CPPBaseEntity
{
public:
	struct ptrCmp
	{
		bool operator()( const CPPBaseEntity* left, const CPPBaseEntity* right );
	};

	class EntityKey
	{
		friend class CPPBaseWorld;
	private:
		EntityKey();
		~EntityKey();
		EntityKey( const EntityKey& );
		EntityKey& operator=( const EntityKey& );
	};

public:
	CPPBaseEntity( float x = 0, float y = 0, CPPBaseGraphic* graphic = NULL, bool autoCleanup = false );
	virtual ~CPPBaseEntity();

	bool isActive() const;
	void setActive( const bool active );

	bool isVisible() const;
	void setVisible( const bool visible );

	bool isCollidable() const;
	void setCollidable( const bool collidable );

	float getPosX() const;
	float getPosY() const;
	void setPosX( const float x );
	void setPosY( const float y );

	int getWidth() const;
	int getHeight() const;
	void setWidth( const int width );
	void setHeight( const int height );
	float getHalfWidth() const;
	float getHalfHeight() const;

	int getOriginX() const;
	int getOriginY() const;
	void setOriginX( const int x );
	void setOriginY( const int y );
	void centerOrigin();

	unsigned int getType() const;
	void setType( const unsigned int type );

	float getCenterX() const;
	float getCenterY() const;

	float getLeft() const;
	float getRight() const;
	float getTop() const;
	float getBottom() const;

	CPPBaseWorld* getWorld() const;
	void setWorld( CPPBaseWorld* const world, EntityKey& );

	bool isAutoCleanup() const;

	int getLayer() const;
	void setLayer( const int layer );

	void setHitbox( const int width, const int height, const int originX, const int originY );

	bool onCamera() const;

	CPPBaseGraphic* getGraphic() const;
	void setGraphic( CPPBaseGraphic* graphic );

	// Updates the Entity.
	virtual void update();
	// Draws the Entity.
	virtual void draw();

	// Override this, called when the Entity is added to a World.
	virtual void added();
	// Override this, called when the Entity is removed from a World.
	virtual void removed();

	// Checks for a collision against an Entity type.
	CPPBaseEntity* collide( unsigned int type, float x, float y ) const;

	// Checks if this Entity overlaps the specified rectangle.
	bool collideRect( float x, float y, float rX, float rY, float rWidth, float rHeight ) const;

	// Checks for collision against multiple Entity types.
	CPPBaseEntity* collideTypes( const std::vector< unsigned int >& types, float x, float y ) const;

	// Checks if this Entity collides with a specific Entity.
	CPPBaseEntity* collideWith( CPPBaseEntity* e, float x, float y ) const;

	// Checks if this Entity overlaps the specified position.
	bool collidePoint( float x, float y, float pX, float pY ) const;

	// Populates a vector with all collided Entities of a type.
	void collideInto( unsigned int type, float x, float y, std::vector< CPPBaseEntity* >& into ) const;

	// Calculates the distance from another Entity.
	float distanceFrom( CPPBaseEntity* e, bool useHitboxes = false ) const;

	// Calculates the distance from this Entity to the point.
	float distanceToPoint( float pX, float pY, bool useHitBox = false ) const;

	// Calculates the distance from this Entity to the Rectangle.
	float distanceToRect( float rX, float rY, float rWidth, float rHeight ) const;

	// Moves the entity by the amount, retaining integer values for its x and y. One solid type.
	void moveBy( float x, float y, bool useSolidType = false, unsigned int solidType = 0, bool sweep = false );

	// Moves the entity by the amount, retaining integer values for its x and y. Vector of solid types.
	void moveBy( float x, float y, const std::vector< unsigned int >& solidTypes, bool sweep = false );

	// Moves the Entity to the position, retaining integer values for its x and y. One solid type.
	void moveTo( float x, float y, bool useSolidType = false, unsigned int solidType = 0, bool sweep = false );

	// Moves the Entity to the position, retaining integer values for its x and y. Vector of solid types.
	void moveTo( float x, float y, const std::vector< unsigned int >& solidTypes, bool sweep = false );

	// Moves towards the target position, retaining integer values for its x and y. One solid type.
	void moveTowards( float x, float y, float amount, bool useSolidType = false, unsigned int solidType = 0, bool sweep = false );

	// Moves towards the target position, retaining integer values for its x and y. Vector of solid types.
	void moveTowards( float x, float y, float amount, const std::vector< unsigned int >& solidTypes, bool sweep = false );

	// Clamps the Entity's hitbox on the x-axis.
	void clampHorizontal( float left, float right, float padding = 0 );

	// Clamps the Entity's hitbox on the y-axis.
	void clampVertical( float top, float bottom, float padding = 0 );

	// Optional callback for a collision in moveBy
	virtual void moveCollideX( CPPBaseEntity* e );

	// Optional callback for a collision in moveBy
	virtual void moveCollideY( CPPBaseEntity* e );

protected:
	bool m_bActive;                                             // If the Entity should update.
	bool m_bVisible;                                            // If the Entity should render.
	bool m_bCollidable;                                         // If the Entity should respond to collision checks.

	float m_posX;                                               // X position of the Entity in the World.
	float m_posY;                                               // Y position of the Entity in the World.

	int m_width;                                                // Width of the Entity's hitbox.
	int m_height;                                               // Height of the Entity's hitbox.

	int m_originX;                                              // X origin of the Entity's hitbox.
	int m_originY;                                              // Y origin of the Entity's hitbox.

	unsigned int m_type;                                        // Type of the Entity.

	int m_layer;                                                // Layer of the Entity.

	CPPBaseWorld* m_pWorld;                                     // World that this entity is in.

private:
	// Cleanup.
	const bool m_bAutoCleanup;                                  // If the Entity should be auto deallocated.

	// TODO: make Graphic class.
	CPPBaseGraphic* m_pGraphic;                                 // Graphic used when drawing the Entity.

	float _moveX;
	float _moveY;

	CPPBaseEntity( const CPPBaseEntity& );
	CPPBaseEntity& operator=( const CPPBaseEntity& );
};

#endif
