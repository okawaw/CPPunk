//
//  CPP_Entity.cpp
//  Test
//
//  Created by Wade Okawa-Scannell on 10/9/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_Entity.h"

#include "CPP.h"
#include "CPP_Graphic.h"
#include "CPP_Mask.h"
#include "CPP_Point.h"
#include "CPP_World.h"

#include <iterator>
#include <utility>

CPP_Entity::CPP_Entity(CPP& _cpp, const double _x, const double _y, std::shared_ptr<CPP_Graphic> _graphic, std::shared_ptr<CPP_Mask> _mask) :
  cpp{_cpp}
, visible{true}
, collidable{true}
, x{_x}
, y{_y}
, width{0}
, height{0}
, originX{0}
, originY{0}
, layer{0}
{
	if (_graphic)
	{
		setGraphic(std::move(_graphic));
	}
	
	if (_mask)
	{
		setMask(std::move(_mask));
	}
	
	// TODO: HITBOX
	
	// TODO: class
}

bool CPP_Entity::isVisible() const
{
	return visible;
}

void CPP_Entity::setVisible(const bool value)
{
	visible = value;
}

bool CPP_Entity::isCollidable() const
{
	return collidable;
}

void CPP_Entity::setCollidable(const bool value)
{
	collidable = value;
}

double CPP_Entity::getX() const
{
	return x;
}

void CPP_Entity::setX(const double value)
{
	x = value;
}

double CPP_Entity::getY() const
{
	return y;
}

void CPP_Entity::setY(const double value)
{
	y = value;
}

int CPP_Entity::getWidth() const
{
	return width;
}

void CPP_Entity::setWidth(const int value)
{
	width = value;
}

int CPP_Entity::getHeight() const
{
	return height;
}

void CPP_Entity::setHeight(const int value)
{
	height = value;
}

double CPP_Entity::getHalfWidth() const
{
	return static_cast<double>(width) / 2.0;
}

double CPP_Entity::getHalfHeight() const
{
	return static_cast<double>(height) / 2.0;
}

int CPP_Entity::getOriginX() const
{
	return originX;
}

void CPP_Entity::setOriginX(const int value)
{
	originX = value;
}

int CPP_Entity::getOriginY() const
{
	return originY;
}

void CPP_Entity::setOriginY(const int value)
{
	originY = value;
}

double CPP_Entity::getCenterX() const
{
	return x - static_cast<double>(originX) + static_cast<double>(width) / 2.0;
}

double CPP_Entity::getCenterY() const
{
	return y - static_cast<double>(originY) + static_cast<double>(height) / 2.0;
}

double CPP_Entity::getLeft() const
{
	return x - static_cast<double>(originX);
}

double CPP_Entity::getRight() const
{
	return x - static_cast<double>(originX) + static_cast<double>(width);
}

double CPP_Entity::getTop() const
{
	return y - static_cast<double>(originY);
}

double CPP_Entity::getBottom() const
{
	return y - static_cast<double>(originY) + static_cast<double>(height);
}

int CPP_Entity::getLayer() const
{
	return layer;
}

void CPP_Entity::setLayer(const int value)
{
	if (layer == value)
	{
		return;
	}
	
	const auto _world = world.lock();

	if (!_world)
	{
		layer = value;
		return;
	}
	
	_world->removeRender(*this);
	layer = value;
	_world->addRender(*this);
}

std::experimental::optional<CPP_EntityType> CPP_Entity::getType() const
{
	return type;
}

void CPP_Entity::setType(const std::experimental::optional<CPP_EntityType>& value)
{
	if (type == value)
	{
		return;
	}

	const auto _world = world.lock();
	
	if (!_world)
	{
		type = value;
		return;
	}
	
	if (type)
	{
		_world->removeType(*this);
	}
	
	type = value;
	
	if (value)
	{
		_world->addType(*this);
	}
}

std::experimental::optional<std::string> CPP_Entity::getName() const
{
	return name;
}

void CPP_Entity::setName(const std::experimental::optional<std::string>& value)
{
	if (name == value)
	{
		return;
	}
	
	const auto _world = world.lock();
	
	if (name && _world)
	{
		_world->unregisterName(*this);
	}
	
	name = value;
	
	if (name && _world)
	{
		_world->registerName(*this);
	}
}

std::shared_ptr<CPP_Graphic> CPP_Entity::getGraphic() const
{
	return graphic;
}

void CPP_Entity::setGraphic(std::shared_ptr<CPP_Graphic> value)
{
	if (graphic == value)
	{
		return;
	}
	
	graphic = std::move(value);
	
	if (graphic && graphic->assign)
	{
		graphic->assign();
	}
}

std::shared_ptr<CPP_Mask> CPP_Entity::getMask() const
{
	return mask;
}

void CPP_Entity::setMask(std::shared_ptr<CPP_Mask> value)
{
	if (mask == value)
	{
		return;
	}
	
	if (mask)
	{
		mask->assignTo(nullptr);
	}
	
	mask = std::move(value);
	
	// TODO: Should this be a weak_ptr?
	if (mask)
	{
		mask->assignTo(this);
	}
}

std::shared_ptr<CPP_World> CPP_Entity::getWorld() const
{
	return world.lock();
}

void CPP_Entity::added()
{
}

void CPP_Entity::removed()
{
}

void CPP_Entity::update()
{
}

void CPP_Entity::render() const
{
	if (graphic && graphic->isVisible())
	{
		const auto _world = world.lock();
		
		graphic->render((graphic->isRelative()) ? CPP_Point{x, y} : CPP_Point{0.0, 0.0}, (_world) ? _world->getCamera() : cpp.getWorld()->getCamera());
	}
}

// TODO: Complete this.
std::shared_ptr<CPP_Entity> CPP_Entity::collide(const CPP_EntityType _type, const double _x, const double _y) const
{
	const auto _world = world.lock();
	
	if (!_world)
	{
		return nullptr;
	}
	
	const auto typeIterator = _world->typeMap.find(_type);
	
	if (typeIterator == _world->typeMap.end())
	{
		return nullptr;
	}
	
	const auto& typeList = typeIterator->second;
	
	for (const auto& e : typeList)
	{
		// TODO: Cache values for _x and _y for mask.
		
		// TODO: Check if this CPP_Entity has a mask.
		if (e.get()->isCollidable() && e.get().get() != this && _x - originX + width > e.get()->x - e.get()->originX && _y - originY + height > e.get()->y - e.get()->originY && _x - originX < e.get()->x - e.get()->originX + e.get()->width && _y - originY < e.get()->y - e.get()->originY + e.get()->height)
		{
			// TODO: Check if the other CPP_Entity has a mask.
			return e;
		}
	}
	
	return nullptr;
}

std::shared_ptr<CPP_Entity> CPP_Entity::collideTypes(const std::vector<CPP_EntityType>& types, const double _x, const double _y) const
{
	const auto _world = world.lock();
	
	if (!_world)
	{
		return nullptr;
	}
	
	for (const auto& type : types)
	{
		const auto& e = collide(type, _x, _y);
		
		if (e)
		{
			return e;
		}
	}
	
	return nullptr;
}

bool CPP_Entity::collideWith(const CPP_Entity& e, const double _x, const double _y) const
{
	// TODO: Cache values for _x and _y for mask.

	if (e.isCollidable() && _x - originX + width > e.x - e.originX && _y - originY + height > e.y - e.originY && _x - originX < e.x - e.originX + e.width && _y - originY < e.y - e.originY + e.height)
	{
		// TODO: Check if this CPP_Entity has a mask.
		
		// TODO: Check if the other CPP_Entity has a mask.
		
		return true;
	}
	
	return false;
}

bool CPP_Entity::collideRect(const double _x, const double _y, const double rX, const double rY, const double rWidth, const double rHeight) const
{
	if (_x - originX + width >= rX && _y - originY + height >= rY && _x - originX <= rX + rWidth && _y - originY <= rY + rHeight)
	{
		// TODO: Check if this CPP_Entity has a mask.
		
		// TODO: Check if the other CPP_Entity has a mask.
		
		return true;
	}
	
	return false;
}

bool CPP_Entity::collidePoint(const double _x, const double _y, const double pX, const double pY) const
{
	if (pX >= _x - originX && pY >= _y - originY && pX < _x - originX + width && pY < _y - originY + height)
	{
		// TODO: Check if this CPP_Entity has a mask.
		
		// TODO: Check if the other CPP_Entity has a mask.
		
		return true;
	}
	
	return false;
}

std::vector<std::shared_ptr<CPP_Entity> > CPP_Entity::collideInto(const CPP_EntityType _type, const double _x, const double _y) const
{
	std::vector<std::shared_ptr<CPP_Entity> > ret;
	
	const auto _world = world.lock();
	
	if (!_world)
	{
		return ret;
	}
	
	const auto typeIterator = _world->typeMap.find(_type);
	
	if (typeIterator == _world->typeMap.end())
	{
		return ret;
	}
	
	const auto& typeList = typeIterator->second;
	
	for (const auto& e : typeList)
	{
		// TODO: Cache values for _x and _y for mask.
		
		// TODO: Check if this CPP_Entity has a mask.
		if (e.get()->isCollidable() && e.get().get() != this && _x - originX + width > e.get()->x - e.get()->originX && _y - originY + height > e.get()->y - e.get()->originY && _x - originX < e.get()->x - e.get()->originX + e.get()->width && _y - originY < e.get()->y - e.get()->originY + e.get()->height)
		{
			// TODO: Check if the other CPP_Entity has a mask.
			ret.emplace_back(e.get());
		}
	}
	
	return ret;
}

std::vector<std::shared_ptr<CPP_Entity> > CPP_Entity::collideTypesInto(const std::vector<CPP_EntityType>& types, const double _x, const double _y) const
{
	std::vector<std::shared_ptr<CPP_Entity> > ret;
	
	const auto _world = world.lock();
	
	if (!_world)
	{
		return ret;
	}
	
	for (const auto& _type : types)
	{
		auto collideIntoRet = collideInto(_type, _x, _y);
		ret.reserve(ret.size() + collideIntoRet.size());
		ret.insert(ret.cend(), std::make_move_iterator(collideIntoRet.begin()), std::make_move_iterator(collideIntoRet.end()));
	}
	
	return ret;
}

bool CPP_Entity::isOnCamera() const
{
	const auto _world = world.lock();
	
	if (!_world)
	{
		return false;
	}
	
	const auto camera = _world->getCamera();
	
	return collideRect(x, y, camera.x, camera.y, cpp.getWidth(), cpp.getHeight());
}


