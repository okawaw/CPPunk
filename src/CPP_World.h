//
//  CPP_World.h
//  Test
//
//  Created by Wade Okawa-Scannell on 9/29/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

// TODO: Make sure all the passed shared_ptr types are correct and shouldnt be raw or references.

#ifndef CPP_World_h
#define CPP_World_h

#include "CPP_Tweener.h"

#include "CPP_Point.h"

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <experimental/optional>
#include <unordered_map>
#include <vector>

class CPP;
class CPP_Entity;
class CPP_Graphic;
class CPP_Mask;

enum class CPP_EntityType;

class CPP_World : public CPP_Tweener, public std::enable_shared_from_this<CPP_World>
{
	friend CPP_Entity;
public:
	CPP_World(CPP& cpp);
	virtual ~CPP_World() = default;
	// TODO: Other constructors.
	
	// If the render() loop is performed.
	bool isVisible() const;
	void setVisible(bool value);
	
	// CPP_Point used to determine drawing offset in the render loop.
	CPP_Point getCamera() const;
	void setCamera(CPP_Point value);
	
	// Override this; called when CPP_World is switch to, and set to the currently active world.
	virtual void begin();
	
	// Override this; called when CPP_World is changed, and the active world is no longer this.
	virtual void end();
	
	// Performed by the game loop, updates all contained CPP_Entities.
	// If you override this to give your CPP_World update code, remember
	// to call CPP_World::update() or your CPP_Entities will not be updated.
	virtual void update() override;
	
	// Performed by the game loop, renders all contained CPP_Entities.
	// If you override this to give your CPP_World render code, remember
	// to call CPP_World::render() or your CPP_Entities will not be rendered.
	virtual void render() const;
	
	// Override this; called when game gains focus.
	virtual void focusGained();
	
	// Override this; called when game loses focus.
	virtual void focusLost();
	
	// TODO: Mouse functions.
	
	// Adds the CPP_Entity to the CPP_World at the end of the frame.
	void add(std::shared_ptr<CPP_Entity> e);
	
	// Removes the CPP_Entity from the CPP_World at the end of the frame.
	void remove(const CPP_Entity& e);
	
	// Removes all CPP_Entities from the CPP_World at the end of the frame.
	void removeAll();
	
	// Adds multiple CPP_Entities to the world.
	void addList(std::vector<std::shared_ptr<CPP_Entity> > list);
	
	// Removes multiple CPP_Entities from the world.
	void removeList(std::vector<std::reference_wrapper<const CPP_Entity> > list);
	
	// Adds a CPP_Entity to the CPP_World with the CPP_Graphic object.
	std::shared_ptr<CPP_Entity> addGraphic(std::shared_ptr<CPP_Graphic> graphic, int layer=0, int x=0, int y=0);
	
	// Adds a CPP_Entity to the CPP_World with the CPP_Mask object.
	std::shared_ptr<CPP_Entity> addMask(std::shared_ptr<CPP_Mask> mask, const std::experimental::optional<CPP_EntityType>& type, int x=0, int y=0);
	
	// TODO: create();
	// TODO: recycle();
	// TODO: clearRecycled();
	// TODO: clearRecycledAll();
	
	// Brings the CPP_Entity to the front of its contained layer.
	bool bringToFront(const CPP_Entity& e);
	
	// Sends the CPP_Entity to the back of its contained layer.
	bool sendToBack(const CPP_Entity& e);
	
	// Shifts the CPP_Entity one place towards the front of its contained layer.
	bool bringForward(const CPP_Entity& e);
	
	// Shifts the CPP_Entity one place towards the back of its contained layer.
	bool sendBackward(const CPP_Entity& e);
	
	// If the CPP_Entity as at the front of its layer.
	bool isAtFront(const CPP_Entity& e) const;
	
	// If the CPP_Entity as at the back of its layer.
	bool isAtBack(const CPP_Entity& e) const;
	
	// Returns the first CPP_Entity that collides with the rectangular area.
	std::shared_ptr<CPP_Entity> collideRect(CPP_EntityType type, double rX, double rY, double rWidth, double rHeight) const;
	
	// Returns the first CPP_Entity found that collides with the position.
	std::shared_ptr<CPP_Entity> collidePoint(CPP_EntityType type, double pX, double pY) const;
	
	// Returns the first CPP_Entity found that collides with the line.
	std::shared_ptr<CPP_Entity> collideLine(CPP_EntityType type, int fromX, int fromY, int toX, int toY, std::experimental::optional<CPP_Point>& p, unsigned int precision=1u) const;
	
	// Returns a vector with all CPP_Entities that collide with the rectangle.
	std::vector<std::shared_ptr<CPP_Entity> > collideRectInto(CPP_EntityType type, double rX, double rY, double rWidth, double rHeight) const;
	
	// Returns a vector with all CPP_Entities that collide with the position.
	std::vector<std::shared_ptr<CPP_Entity> > collideRectInto(CPP_EntityType type, double pX, double pY) const;
	
	// Finds the CPP_Entity nearest to the rectangle.
	std::shared_ptr<CPP_Entity> nearestToRect(CPP_EntityType type, double x, double y, double width, double height, const CPP_Entity* ignore=nullptr) const;
	
	// Finds the CPP_Entity nearest to another.
	std::shared_ptr<CPP_Entity> nearestToEntity(CPP_EntityType type, const CPP_Entity& e, bool useHitboxes=false) const;
	
	// Finds the CPP_Entity nearest to the position.
	std::shared_ptr<CPP_Entity> nearestToPoint(CPP_EntityType type, double x, double y, bool useHitBoxes=false) const;
	
	// How many CPP_Entities are in the CPP_World.
	unsigned int getCount() const;
	
	// Returns the amount of CPP_Entities of the type are in the CPP_World.
	unsigned int getTypeCount(CPP_EntityType type) const;
	
	// TODO: Implement class.
	// Returns the amount of CPP_Entities of the Class are in the CPP_World.
	// unsigned int getClassCount() const;
	
	// Returns the amount of CPP_Entities are on the layer in the CPP_World.
	unsigned int getLayerCount(int layer) const;
	
	// The first CPP_Entity in the CPP_World.
	std::shared_ptr<CPP_Entity> getFirst() const;
	
	// How many CPP_Entity layers the CPP_World has.
	unsigned int getLayers() const;
	
	// The first CPP_Entity of the type.
	std::shared_ptr<CPP_Entity> getTypeFirst(CPP_EntityType type) const;
	
	// The first CPP_Entity of the Class.
	// std::shared_ptr<CPP_Entity> getClassFirst() const;
	
	// The first CPP_Entity on the layer.
	std::shared_ptr<CPP_Entity> getLayerFirst(int layer) const;
	
	// The last CPP_Entity on the layer.
	std::shared_ptr<CPP_Entity> getLayerLast(int layer) const;
	
	// The CPP_Entity that will be rendered first by the CPP_World.
	std::shared_ptr<CPP_Entity> getFarthest() const;
	
	// The CPP_Entity that will be rendered last by the CPP_World.
	std::shared_ptr<CPP_Entity> getNearest() const;
	
	// The layer that will be rendered first by the CPP_World.
	int getLayerFarthest() const;
	
	// The layer that will be rendered last by the CPP_World.
	int getLayerNearest() const;
	
	// How many different types have been added to the CPP_World.
	unsigned int getUniqueTypes() const;
	
	// Returns a vector of all CPP_Entities in the CPP_World of the type.
	std::vector<std::shared_ptr<CPP_Entity> > getType(CPP_EntityType type) const;
	
	// TODO: Implement class.
	// Returns a vector of all CPP_Entities in the CPP_World of the Class.
	// std::vector<std::shared_ptr<CPP_Entity> > getClass() const;
	
	// Returns a vector of all CPP_Entities in the CPP_World on the layer.
	std::vector<std::shared_ptr<CPP_Entity> > getLayer(int layer) const;
	
	// Returns a vector of all CPP_Entities in the CPP_World.
	std::vector<std::shared_ptr<CPP_Entity> > getAll() const;
	
	// Returns the CPP_Entity with the instance name, or nullptr if none exists.
	std::shared_ptr<CPP_Entity> getInstance(const std::string& name) const;
	
	// Updates the add/remove lists at the end of the frame.
	void updateLists(bool shouldAdd=true);
	
	// Adds Entity to the render list.
	
protected:
	CPP& cpp;
	
private:
	//void addUpdate(std::shared_ptr<CPP_Entity> e);
	void addUpdate(const CPP_Entity& e);
	void removeUpdate(const CPP_Entity& e);
	
	//void addRender(std::shared_ptr<CPP_Entity> e);
	void addRender(const CPP_Entity& e);
	void removeRender(const CPP_Entity& e);
	//void updateRender(const CPP_Entity& e, int layer);
	
	//void addType(std::shared_ptr<CPP_Entity> e);
	void addType(const CPP_Entity& e);
	void removeType(const CPP_Entity& e);
	//void updateType(const CPP_Entity& e, CPP_EntityType type);
	
	//void registerName(std::shared_ptr<CPP_Entity> e);
	void registerName(const CPP_Entity& e);
	void unregisterName(const CPP_Entity& e);
	//void updateName(const CPP_Entity& e, const std::string& name);
	
	bool visible;
	
	CPP_Point camera;
	
	struct CPP_WorldEntityCache
	{
		CPP_WorldEntityCache(std::shared_ptr<CPP_Entity> ptr=nullptr);
		
		std::shared_ptr<CPP_Entity> ptr;
		std::list<const std::reference_wrapper<const std::shared_ptr<CPP_Entity> > >::const_iterator updateIterator;
		std::list<const std::reference_wrapper<const std::shared_ptr<CPP_Entity> > >::const_iterator renderIterator;
		std::list<const std::reference_wrapper<const std::shared_ptr<CPP_Entity> > >::const_iterator typeIterator;
	};
	
	std::unordered_map<const CPP_Entity*, CPP_WorldEntityCache> entityMap;
	
	std::list<const std::reference_wrapper<const std::shared_ptr<CPP_Entity> > > updateList;
	std::map<int, std::list<const std::reference_wrapper<const std::shared_ptr<CPP_Entity> > >, std::greater<> > renderMap;
	std::unordered_map<CPP_EntityType, std::list<const std::reference_wrapper<const std::shared_ptr<CPP_Entity> > > > typeMap;
	std::unordered_map<std::string, std::reference_wrapper<const std::shared_ptr<CPP_Entity> > > nameMap;
	
	// Adding and removal.
	std::vector<std::shared_ptr<CPP_Entity> > addVector;
	std::vector<std::reference_wrapper<const CPP_Entity> > removeVector;
	
	// TODO: Recycle.
	//std::vector<std::reference_wrapper<const CPP_Entity> > recycleVector;
};

#endif /* CPP_World_h */
