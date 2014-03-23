#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "ofImage.h"

class BaseEntity
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

	unsigned int getWidth() const { return m_width; }
	unsigned int getHeight() const { return m_height; }
	void setWidth( const unsigned int width ) { m_width = width; }
	void setHeight( const unsigned int height ) { m_height = height; }

	unsigned int getOriginX() const { return m_originX; }
	unsigned int getOriginY() const { return m_originY; }
	void setOriginX( const unsigned int x ) { m_originX = x; }
	void setOriginY( const unsigned int y ) { m_originY = y; }

	void setGraphic( const std::string& file );

	virtual void update();                     // Updates the Entity.
	virtual void draw();                       // Draws the Entity.

	virtual void added();                      // Override this, called when the Entity is added to a World.
	virtual void removed();                    // Override this, called when the Entity is removed from a World.

private:
	bool m_bVisible;                           // If the Entity should render.
	bool m_bCollidable;                        // If the Entity should respond to collision checks.

	float m_posX;                              // X position of the Entity in the World.
	float m_posY;                              // Y position of the Entity in the World.

	unsigned int m_width;                      // Width of the Entity's hitbox.
	unsigned int m_height;                     // Height of the Entity's hitbox.

	unsigned int m_originX;                    // X origin of the Entity's hitbox.
	unsigned int m_originY;                    // Y origin of the Entity's hitbox.

	ofImage m_graphic;
};

#endif
