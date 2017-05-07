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
#include <typeinfo>
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
	
	// TODO: void addGraphic(std::shared_ptr<CPP_Graphic> g);
	
	// An optional CPP_Mask component, used for specialized collision. If this is
	// not assigned, collision checks will use the CPP_Entity's hitbox by default.
	std::shared_ptr<CPP_Mask> getMask() const;
	void setMask(std::shared_ptr<CPP_Mask> value);
	
	// Sets the Entity's hitbox properties.
	void setHitbox(int width=0, int height=0, int originX=0, int originY=0);
	
	// TODO: template <typename T> void setHitboxTo(const T& object);
	
	// Sets the origin of the CPP_Entity.
	void setOrigin(int x=0, int y=0);
	
	// Centers the CPP_Entity's origin (half width & height).
	void centerOrigin();
	
	// Calculates the distance from another CPP_Entity.
	double distanceFrom(const CPP_Entity& e, bool useHitboxes=false) const;
	
	// Calculates the distance from this CPP_Entity to the point.
	double distanceToPoint(double pX, double pY, bool useHitbox=false) const;
	
	// Calculates the distance from this CPP_Entity to the rectangle.
	double distanceToRect(double rX, double rY, double rWidth, double rHeight) const;
	
	// Gets the class name as a string.
	std::string toString() const;
	
	// Moves the CPP_Entity by the amount, retaining integer values for its x and y.
	void moveBy(double x, double y, const std::experimental::optional<std::vector<CPP_EntityType> >& solidType=std::experimental::nullopt, bool sweep=false);
	
	// Moves the CPP_Entity to the position, retaining integer values for its x and y.
	void moveTo(double x, double y, const std::experimental::optional<std::vector<CPP_EntityType> >& solidType=std::experimental::nullopt, bool sweep=false);
	
	// Moves towards the target position, retaining integer values for its x and y.
	void moveTowards(double x, double y, double amount, const std::experimental::optional<std::vector<CPP_EntityType> >& solidType=std::experimental::nullopt, bool sweep=false);
	
	// Clamps the CPP_Entity's hitbox on the x-axis.
	void clampHorizontal(double left, double right, double padding=0.0);
	
	// Clamps the CPP_Entity's hitbox on the y axis.
	void clampVertical(double top, double bottom, double padding=0.0);
	
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
	
	// When you collide with a CPP_Entity on the x-axis with moveTo() or moveBy().
	virtual bool moveCollideX(const CPP_Entity& e);
	
	// When you collide with a CPP_Entity on the y-axis with moveTo() or moveBy().
	virtual bool moveCollideY(const CPP_Entity& e);
	
	const std::type_info& getClass() const;
	
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
	double _moveX;
	double _moveY;
	
	int layer;
	std::experimental::optional<CPP_EntityType> type;
	std::experimental::optional<std::string> name;
	
	std::shared_ptr<CPP_Graphic> graphic;
	std::shared_ptr<CPP_Mask> mask;
	std::weak_ptr<CPP_World> world;
	
	mutable const std::type_info* _class;
	
};

#endif /* CPP_Entity_h */
