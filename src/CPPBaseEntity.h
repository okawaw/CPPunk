#ifndef CPP_BASE_ENTITY_H_
#define CPP_BASE_ENTITY_H_

#include "ofImage.h"

class CPPBaseWorld;

class CPPBaseEntity
{
public:
	struct ptrCmp
	{
		bool operator()( const CPPBaseEntity* left, const CPPBaseEntity* right );
	};

public:                                  // TODO: Pass a Graphic once it is implemented.
	CPPBaseEntity( const std::string& graphicFile = "", float x = 0, float y = 0 );
	virtual ~CPPBaseEntity();

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

	int getLayer() const;
	void setLayer( const int layer );

	void setHitbox( const int width, const int height, const int originX, const int originY );

	bool onCamera() const;

	void setGraphic( const std::string& file );

	virtual void update();                                      // Updates the Entity.
	virtual void draw();                                        // Draws the Entity.

	virtual void added();                                       // Override this, called when the Entity is added to a World.
	virtual void removed();                                     // Override this, called when the Entity is removed from a World.

	CPPBaseWorld* getWorld() const { return m_world; }
	void setWorld( CPPBaseWorld* const world ) { m_world = world; }

	CPPBaseEntity* collide( unsigned int type,           // Checks for a collision against an Entity type.
	                     float x, float y ) const;

	bool collideRect( float x, float y,                         // Checks if this Entity overlaps the specified rectangle.
	                  float rX, float rY,
	                  float rWidth, float rHeight ) const;

	CPPBaseEntity* collideTypes( std::vector< unsigned int >& types, // Checks for collision against multiple Entity types.
	                          float x, float y );

	// Checks if this Entity collides with a specific Entity.
	CPPBaseEntity* collideWith( CPPBaseEntity* e, float x, float y );

	// Checks if this Entity overlaps the specified position.
	bool collidePoint( float x, float y, float pX, float pY );

	// Populates a vector with all collided Entities of a type.
	void collideInto( unsigned int type, float x, float y, std::vector< CPPBaseEntity* >& into );

	// Calculates the distance from another Entity.
	float distanceFrom( CPPBaseEntity* e, bool useHitboxes = false );

	// Calculates the distance from this Entity to the point.
	float distanceToPoint( float pX, float pY, bool useHitBox = false );

	// Calculates the distance from this Entity to the Rectangle.
	float distanceToRectangle( float rX, float rY, float rWidth, float rHeight );



protected:
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

	CPPBaseWorld* m_world;                                      // World that this entity is in.

private:
	// TODO: make Graphic class.
	ofImage m_graphic;                                          // Graphic used when drawing the Entity.
};

#endif
