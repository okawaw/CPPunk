#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "BaseEntityDefs.h"

#include "ofImage.h"

class BaseWorld;

class BaseEntity
{
public:                                  // TODO: Pass a Graphic once it is implemented.
	BaseEntity( const std::string& graphicFile = "", float x = 0, float y = 0 );
	virtual ~BaseEntity();

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

	BaseEntityTypes::id getType() const;
	void setType( const BaseEntityTypes::id type );

	float getCenterX() const;
	float getCenterY() const;

	float getLeft() const;
	float getRight() const;
	float getTop() const;
	float getBottom() const;

	int getLater() const;
	void setLayer( const int layer );

	void setHitbox( const int width, const int height, const int originX, const int originY );


	// TODO: bool onCamera() const;

	void setGraphic( const std::string& file );

	virtual void update();                                      // Updates the Entity.
	virtual void draw();                                        // Draws the Entity.

	virtual void added();                                       // Override this, called when the Entity is added to a World.
	virtual void removed();                                     // Override this, called when the Entity is removed from a World.

	BaseWorld* getWorld() const { return m_world; }
	void setWorld( BaseWorld* const world ) { m_world = world; }

	BaseEntity* collide( BaseEntityTypes::id type,              // Checks for a collision against an Entity type.
	                     float x, float y );

	bool collideRect( float x, float y,                         // Checks if this Entity overlaps the specified rectangle.
	                  float rX, float rY,
	                  float rWidth, float rHeight );

	BaseEntity* collideTypes( std::vector< BaseEntityTypes::id >& types, // Checks for collision against multiple Entity types.
	                          float x, float y );

	// Checks if this Entity collides with a specific Entity.
	BaseEntity* collideWith( BaseEntity* e, float x, float y );

	// Checks if this Entity overlaps the specified position.
	bool collidePoint( float x, float y, float pX, float pY );

	// Populates a vector with all collided Entities of a type.
	void collideInto( BaseEntityTypes::id type, float x, float y, std::vector< BaseEntity* >& into );

	// Calculates the distance from another Entity.
	float distanceFrom( BaseEntity* e, bool useHitboxes = false );

	// Calculates the distance from this Entity to the point.
	float distanceToPoint( float pX, float pY, bool useHitBox = false );

	// Calculates the distance from this Entity to the Rectangle.
	float distanceToRectangle( float rX, float rY, float rWidth, float rHeight );



private:
	bool m_bVisible;                                            // If the Entity should render.
	bool m_bCollidable;                                         // If the Entity should respond to collision checks.

	float m_posX;                                               // X position of the Entity in the World.
	float m_posY;                                               // Y position of the Entity in the World.

	int m_width;                                                // Width of the Entity's hitbox.
	int m_height;                                               // Height of the Entity's hitbox.

	int m_originX;                                              // X origin of the Entity's hitbox.
	int m_originY;                                              // Y origin of the Entity's hitbox.

	BaseEntityTypes::id m_type;                                 // Type of the Entity.

	int m_layer;                                                // Layer of the Entity.

	// TODO: make Graphic class.
	ofImage m_graphic;                                          // Graphic used when drawing the Entity.

	BaseWorld* m_world;                                         // World that this entity is in.
};

#endif
