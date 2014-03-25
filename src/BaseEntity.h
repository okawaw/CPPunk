#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "BaseEntityDefs.h"

#include "ofImage.h"

class BaseWorld;

class BaseEntity   // TODO: move all definitions to cpp file.
{
public:
	BaseEntity( const std::string& graphicFile = "", float x = 0, float y = 0 );
	virtual ~BaseEntity();

	bool isVisible() const { return m_bVisible; }
	void setVisible( const bool visible ) { m_bVisible = visible; }

	bool isCollidable() const { return m_bCollidable; }
	void setCollidable( const bool collidable ) { m_bCollidable = collidable; }

	float getPosX() const { return m_posX; }
	float getPosY() const { return m_posY; }
	void setPosX( const float x ) { m_posX = x; }
	void setPosY( const float y ) { m_posY = y; }

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	void setWidth( const int width ) { m_width = width; }
	void setHeight( const int height ) { m_height = height; }
	float getHalfWidth() const { return ( ( float )m_width / 2.0 ); }
	float getHalfHeight() const { return ( ( float )m_height / 2.0 ); }

	int getOriginX() const { return m_originX; }
	int getOriginY() const { return m_originY; }
	void setOriginX( const int x ) { m_originX = x; }
	void setOriginY( const int y ) { m_originY = y; }
	void centerOrigin() { m_originX = ( ( float )m_width / 2.0 ); m_originY = ( ( float )m_height / 2.0 ); }

	BaseEntityTypes::id getType() const { return m_type; }
	void setType( const BaseEntityTypes::id type ) { m_type = type; }

	float getCenterX() const { return m_posX - m_originX + ( ( float )m_width / 2.0 ); }
	float getCenterY() const { return m_posY - m_originY + ( ( float )m_height / 2.0 ); }

	float getLeft() const { return m_posX - m_originX; }
	float getRight() const { return m_posX - m_originX + m_width; }
	float getTop() const { return m_posY - m_originY; }
	float getBottom() const { return m_posY - m_originY + m_height; }

	int getLater() const { return m_layer; }
	int setLayer( const int layer ) { m_layer = layer; }

	void setHitbox( int width, int height, int originX, int originY )
	{
		m_width = width;
		m_height = height;
		m_originX = originX;
		m_originY = originY;
	}


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
