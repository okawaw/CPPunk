//
//  CPP_Entity.h
//  Test
//
//  Created by Wade Okawa-Scannell on 10/9/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_Entity_h
#define CPP_Entity_h

#include "CPP_Tweener.h"

#include <memory>
#include <experimental/optional>
#include <string>
#include <vector>

class CPP;
class CPP_Graphic;
class CPP_Mask;
class CPP_World;

enum class CPP_EntityType;

// TODO: Check if CPP_EntityType should always be an optional.

// Main game CPP_Entity class updated by CPP_World.
class CPP_Entity : public CPP_Tweener
{
	friend CPP_World;
public:
	CPP_Entity(CPP& cpp, double x=0.0, double y=0.0, std::shared_ptr<CPP_Graphic> graphic=nullptr, std::shared_ptr<CPP_Mask> mask=nullptr);
	virtual ~CPP_Entity() = default;
	// TODO: Other constructors.
	
	// If the CPP_Entity should render.
	bool isVisible() const;
	void setVisible(bool value);
	
	// If the CPP_Entity should respond to collision checks.
	bool isCollidable() const;
	void setCollidable(bool value);
	
	// X position of the CPP_Entity in the CPP_World.
	double getX() const;
	void setX(double value);
	
	// Y position of the CPP_Entity in the CPP_World.
	double getY() const;
	void setY(double value);
	
	// Width of the CPP_Entity's hitbox.
	int getWidth() const;
	void setWidth(int value);
	
	// Height of the CPP_Entity's hitbox.
	int getHeight() const;
	void setHeight(int value);
	
	// Half the Entity's width.
	double getHalfWidth() const;
	
	// Half the Entity's height.
	double getHalfHeight() const;
	
	// X origin of the CPP_Entity's hitbox.
	int getOriginX() const;
	void setOriginX(int value);
	
	// Y origin of the CPP_Entity's hitbox.
	int getOriginY() const;
	void setOriginY(int value);
	
	// The center x position of the CPP_Entity's hitbox.
	double getCenterX() const;
	
	// The center y position of the CPP_Entity's hitbox.
	double getCenterY() const;
	
	// The leftmost position of the CPP_Entity's hitbox.
	double getLeft() const;
	
	// The rightmost position of the CPP_Entity's hitbox.
	double getRight() const;
	
	// The topmost position of the CPP_Entity's hitbox.
	double getTop() const;
	
	// The bottommost position of the CPP_Entity's hitbox.
	double getBottom() const;
	
	// The rendering layer of this CPP_Entity. Higher layers are rendered first.
	int getLayer() const;
	void setLayer(int value);
	
	// The collision type, used for collision checking.
	std::experimental::optional<CPP_EntityType> getType() const;
	void setType(const std::experimental::optional<CPP_EntityType>& value);
	
	// The CPP_Entity's instance name. Use this to uniquely identify single
	// game CPP_Entities, which can then be looked-up with
	// CPP_World::getInstance(const std::string&).
	std::experimental::optional<std::string> getName() const;
	void setName(const std::experimental::optional<std::string>& value);
	
	// Graphical component to render to the screen.
	std::shared_ptr<CPP_Graphic> getGraphic() const;
	void setGraphic(std::shared_ptr<CPP_Graphic> value);
	
	// An optional CPP_Mask component, used for specialized collision. If this is
	// not assigned, collision checks will use the CPP_Entity's hitbox by default.
	std::shared_ptr<CPP_Mask> getMask() const;
	void setMask(std::shared_ptr<CPP_Mask> value);
	
	// The CPP_World object this Entity has been added to.
	std::shared_ptr<CPP_World> getWorld() const;
	
	// Override this, called when the CPP_Entity is added to a CPP_World.
	virtual void added();
	
	// Override this, called when the CPP_Entity is removed from a CPP_World.
	virtual void removed();
	
	// Updates the CPP_Entity.
	virtual void update() override;
	
	// Renders the Entity. If you override this for special behaviour,
	// remember to call CPP_Entity::render() to render the CPP_Entity's graphic.
	virtual void render() const;
	
	// Checks for a collision against an CPP_Entity type.
	std::shared_ptr<CPP_Entity> collide(CPP_EntityType type, double x, double y) const;
	
	// Checks for collision against multiple CPP_Entity types.
	std::shared_ptr<CPP_Entity> collideTypes(const std::vector<CPP_EntityType>& types, double x, double y) const;
	
	// Checks if this CPP_Entity collides with a specific CPP_Entity.
	bool collideWith(const CPP_Entity& e, double x, double y) const;
	
	// Checks if this CPP_Entity overlaps the specified rectangle.
	bool collideRect(double x, double y, double rX, double rY, double rWidth, double rHeight) const;
	
	// Checks if this CPP_Entity overlaps the specified position.
	bool collidePoint(double x, double y, double pX, double pY) const;
	
	// Returns a vector with all collided CPP_Entities of a type.
	std::vector<std::shared_ptr<CPP_Entity> > collideInto(CPP_EntityType type, double x, double y) const;
	
	// Returns a vector with all collided CPP_Entities of multiple types.
	std::vector<std::shared_ptr<CPP_Entity> > collideTypesInto(const std::vector<CPP_EntityType>& types, double x, double y) const;
	
	// If the CPP_Entity collides with the camera rectangle.
	bool isOnCamera() const;
	
private:
	CPP& cpp;
	bool visible;
	bool collidable;
	double x;
	double y;
	int width;
	int height;
	int originX;
	int originY;
	
	int layer;
	std::experimental::optional<CPP_EntityType> type;
	std::experimental::optional<std::string> name;
	
	std::shared_ptr<CPP_Graphic> graphic;
	std::shared_ptr<CPP_Mask> mask;
	std::weak_ptr<CPP_World> world;
	
};

#endif /* CPP_Entity_h */
