//
//  CPP_World.cpp
//  Test
//
//  Created by Wade Okawa-Scannell on 9/29/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_World.h"

#include "CPP.h"
#include "CPP_Entity.h"
#include "CPP_Graphic.h"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <limits>
#include <utility>

// Calculates the squared distance between two rectangles.
double squareRects(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);

// Calculates the squared distance between two points.
double squarePoints(double x1, double y1, double x2, double y2);

// Calculates the squared distance between a rectangle and a point.
double squarePointRect(double pX, double pY, double rX, double rY, double rW, double rH);


CPP_World::CPP_WorldEntityCache::CPP_WorldEntityCache(std::shared_ptr<CPP_Entity> _ptr) :
  ptr{std::move(_ptr)}
{
}

CPP_World::CPP_World(const CPP& _cpp) :
  cpp{_cpp}
, visible{true}
{
}

bool CPP_World::isVisible() const
{
	return visible;
}

void CPP_World::setVisible(const bool value)
{
	visible = value;
}

CPP_Point CPP_World::getCamera() const
{
	return camera;
}

void CPP_World::setCamera(CPP_Point value)
{
	camera = std::move(value);
}

void CPP_World::begin()
{
}

void CPP_World::end()
{
}

void CPP_World::update()
{
	for (const auto& eRef : updateList)
	{
		const auto& e = eRef.get();
		
		if (e->isActive())
		{
			// TODO: Do tween things.
			e->update();
		}
		
		const auto graphic = e->getGraphic();
		if (graphic && graphic->isActive())
		{
			graphic->update();
		}
	}
}

void CPP_World::render() const
{
	for (const auto& renderMapPair : renderMap)
	{
		for (const auto& eRef : renderMapPair.second)
		{
			const auto& e = eRef.get();

			if (e->isVisible())
			{
				e->render();
			}
		}
	}
}

void CPP_World::focusGained()
{
}

void CPP_World::focusLost()
{
}

void CPP_World::add(std::shared_ptr<CPP_Entity> e)
{
	addVector.emplace_back(std::move(e));
}

void CPP_World::remove(const CPP_Entity& e)
{
	removeVector.emplace_back(std::cref(e));
}

void CPP_World::removeAll()
{
	for (const auto& entityMapPair : entityMap)
	{
		removeVector.emplace_back(std::cref(*entityMapPair.first));
	}
}

void CPP_World::addList(std::vector<std::shared_ptr<CPP_Entity> > list)
{
	addVector.reserve(addVector.size() + list.size());
	addVector.insert(addVector.cend(), std::make_move_iterator(list.begin()), std::make_move_iterator(list.end()));
}

void CPP_World::removeList(std::vector<std::reference_wrapper<const CPP_Entity> > list)
{
	removeVector.reserve(removeVector.size() + list.size());
	removeVector.insert(removeVector.cend(), std::make_move_iterator(list.begin()), std::make_move_iterator(list.end()));
}

std::shared_ptr<CPP_Entity> CPP_World::addGraphic(std::shared_ptr<CPP_Graphic> graphic, const int layer, const int x, const int y)
{
	const auto e = std::make_shared<CPP_Entity>(cpp, static_cast<double>(x), static_cast<double>(y), std::move(graphic));
	
	if (layer != 0)
	{
		e->setLayer(layer);
	}
	
	e->setActive(false);
	
	add(e);
	
	return e;
}

std::shared_ptr<CPP_Entity> CPP_World::addMask(std::shared_ptr<CPP_Mask> mask, const std::experimental::optional<CPP_EntityType>& type, const int x, const int y)
{
	const auto e = std::make_shared<CPP_Entity>(cpp, static_cast<double>(x), static_cast<double>(y), nullptr, std::move(mask));
	
	if (type)
	{
		e->setType(type);
	}
	
	e->setActive(false);
	e->setVisible(false);
	
	add(e);
	
	return e;
}

// TODO: Check this.
bool CPP_World::bringToFront(const CPP_Entity& e)
{
	// Ensure the CPP_Entity's parent world is this.
	if (e.getWorld().get() != this)
	{
		return false;
	}
	
	// Find the CPP_Entity in the cache.
	const auto entityMapIterator = entityMap.find(&e);
	
	// Ensure the CPP_Entity is cached.
	if (entityMapIterator == entityMap.end())
	{
		return false;
	}
	
	// Find the layer list that this CPP_Entity belongs to.
	const auto renderMapIterator = renderMap.find(e.getLayer());
	
	// Ensure that the layer list exists.
	if (renderMapIterator == renderMap.end())
	{
		return false;
	}
	
	auto& renderList = renderMapIterator->second;
	const auto& renderIterator = entityMapIterator->second.renderIterator;
	
	// renderIterator should be referring to e.
	
	// Do nothing if the CPP_Entity is already first to render.
	if (renderList.empty() || &e == renderList.front().get().get())
	{
		return false;
	}
	
	// Move to front of list.
	renderList.splice(renderList.cbegin(), renderList, renderIterator);
	
	return true;
}

bool CPP_World::sendToBack(const CPP_Entity& e)
{
	// Ensure the CPP_Entity's parent world is this.
	if (e.getWorld().get() != this)
	{
		return false;
	}
	
	// Find the CPP_Entity in the cache.
	const auto entityMapIterator = entityMap.find(&e);
	
	// Ensure the CPP_Entity is cached.
	if (entityMapIterator == entityMap.end())
	{
		return false;
	}
	
	// Find the layer list that this CPP_Entity belongs to.
	const auto renderMapIterator = renderMap.find(e.getLayer());
	
	// Ensure that the layer list exists.
	if (renderMapIterator == renderMap.end())
	{
		return false;
	}
	
	auto& renderList = renderMapIterator->second;
	const auto& renderIterator = entityMapIterator->second.renderIterator;
	
	// renderIterator should be referring to e.
	
	// Do nothing if the CPP_Entity is already last to render.
	if (renderList.empty() || &e == renderList.back().get().get())
	{
		return false;
	}
	
	// Move to back of list.
	renderList.splice(renderList.cend(), renderList, renderIterator);
	
	return true;
}

bool CPP_World::bringForward(const CPP_Entity& e)
{
	// Ensure the CPP_Entity's parent world is this.
	if (e.getWorld().get() != this)
	{
		return false;
	}
	
	// Find the CPP_Entity in the cache.
	const auto entityMapIterator = entityMap.find(&e);
	
	// Ensure the CPP_Entity is cached.
	if (entityMapIterator == entityMap.end())
	{
		return false;
	}
	
	// Find the layer list that this CPP_Entity belongs to.
	const auto renderMapIterator = renderMap.find(e.getLayer());
	
	// Ensure that the layer list exists.
	if (renderMapIterator == renderMap.end())
	{
		return false;
	}
	
	auto& renderList = renderMapIterator->second;
	const auto& renderIterator = entityMapIterator->second.renderIterator;
	
	// renderIterator should be referring to e.
	
	// Do nothing if the CPP_Entity is already first to render.
	if (renderList.empty() || &e == renderList.front().get().get())
	{
		return false;
	}
	
	// Move forward in list.
	renderList.splice(std::prev(renderIterator), renderList, renderIterator);
	
	return true;
}

bool CPP_World::sendBackward(const CPP_Entity& e)
{
	// Ensure the CPP_Entity's parent world is this.
	if (e.getWorld().get() != this)
	{
		return false;
	}
	
	// Find the CPP_Entity in the cache.
	const auto entityMapIterator = entityMap.find(&e);
	
	// Ensure the CPP_Entity is cached.
	if (entityMapIterator == entityMap.end())
	{
		return false;
	}
	
	// Find the layer list that this CPP_Entity belongs to.
	const auto renderMapIterator = renderMap.find(e.getLayer());
	
	// Ensure that the layer list exists.
	if (renderMapIterator == renderMap.end())
	{
		return false;
	}
	
	auto& renderList = renderMapIterator->second;
	const auto& renderIterator = entityMapIterator->second.renderIterator;
	
	// renderIterator should be referring to e.
	
	// Do nothing if the CPP_Entity is already last to render.
	if (renderList.empty() || &e == renderList.back().get().get())
	{
		return false;
	}
	
	// Move forward 1 by moving in front of the iterator 2 ahead.
	renderList.splice(std::next(renderIterator, 2), renderList, renderIterator);
	
	return true;
}

bool CPP_World::isAtFront(const CPP_Entity& e) const
{
	// Find the layer list that this CPP_Entity belongs to.
	const auto renderMapIterator = renderMap.find(e.getLayer());
	
	// Ensure that the layer list exists.
	if (renderMapIterator == renderMap.cend())
	{
		return false;
	}
	
	const auto& renderList = renderMapIterator->second;
	
	// Return false if there are no CPP_Entities in that layer.
	if (renderList.empty())
	{
		return false;
	}
	
	return &e == renderList.front().get().get();
}

bool CPP_World::isAtBack(const CPP_Entity& e) const
{
	// Find the layer list that this CPP_Entity belongs to.
	const auto renderMapIterator = renderMap.find(e.getLayer());
	
	// Ensure that the layer list exists.
	if (renderMapIterator == renderMap.cend())
	{
		return false;
	}
	
	const auto& renderList = renderMapIterator->second;
	
	// Return false if there are no CPP_Entities in that layer.
	if (renderList.empty())
	{
		return false;
	}
	
	return &e == renderList.back().get().get();
}

std::shared_ptr<CPP_Entity> CPP_World::collideRect(const CPP_EntityType type, const double rX, const double rY, const double rWidth, const double rHeight) const
{
	const auto typeMapIterator = typeMap.find(type);
	
	if (typeMapIterator == typeMap.cend())
	{
		return nullptr;
	}
	
	const auto& typeList = typeMapIterator->second;
	
	for (const auto& e : typeList)
	{
		if (e.get()->isCollidable() && e.get()->collideRect(e.get()->getX(), e.get()->getY(), rX, rY, rWidth, rHeight))
		{
			return e.get();
		}
	}
	
	return nullptr;
}

std::shared_ptr<CPP_Entity> CPP_World::collidePoint(const CPP_EntityType type, const double pX, const double pY) const
{
	const auto typeMapIterator = typeMap.find(type);
	
	if (typeMapIterator == typeMap.cend())
	{
		return nullptr;
	}
	
	const auto& typeList = typeMapIterator->second;
	
	for (const auto& e : typeList)
	{
		if (e.get()->isCollidable() && e.get()->collidePoint(e.get()->getX(), e.get()->getY(), pX, pY))
		{
			return e.get();
		}
	}
	
	return nullptr;
}

std::shared_ptr<CPP_Entity> CPP_World::collideLine(const CPP_EntityType type, const int fromX, const int fromY, const int toX, const int toY, std::experimental::optional<CPP_Point>& p, const unsigned int _precision) const
{
	// If the distance is less than precision, do the short sweep.
	const auto precision = (_precision < 1u) ? 1u : _precision;
	
	if (CPP::distance(static_cast<double>(fromX), static_cast<double>(fromY), static_cast<double>(toX), static_cast<double>(toY)) < static_cast<double>(precision))
	{
		if (p)
		{
			if (fromX == toX && fromY == toY)
			{
				p->x = static_cast<double>(toX);
				p->y = static_cast<double>(toY);
				return collidePoint(type, toX, toY);
			}
			return collideLine(type, fromX, fromY, toX, toY, p, 1u);
		}
		else
		{
			return collidePoint(type, fromX, fromY);
		}
	}
	
	// Get information about the line we're about to raycast.
	const auto xDelta = std::abs(toX - fromX);
	const auto yDelta = std::abs(toY - fromY);
	auto xSign = (toX > fromX) ? static_cast<double>(precision) : -static_cast<double>(precision);
	auto ySign = (toY > fromY) ? static_cast<double>(precision) : -static_cast<double>(precision);
	auto x = static_cast<double>(fromX);
	auto y = static_cast<double>(fromY);
	std::shared_ptr<CPP_Entity> e;
	
	// Do a raycast from the start to the end point.
	if (xDelta > yDelta)
	{
		ySign *= (static_cast<double>(yDelta) / static_cast<double>(xDelta));
		if (xSign > 0.0)
		{
			while (x < static_cast<double>(toX))
			{
				if ((e = collidePoint(type, x, y)))
				{
					if (!p)
					{
						return e;
					}
					if (precision < 2u)
					{
						p->x = x - xSign;
						p->y = y - ySign;
						return e;
					}
					return collideLine(type, static_cast<int>(x - xSign), static_cast<int>(y - ySign), toX, toY, p, 1u);
				}
				x += xSign;
				y += ySign;
			}
		}
		else
		{
			while (x > static_cast<double>(toX))
			{
				if ((e = collidePoint(type, x, y)))
				{
					if (!p)
					{
						return e;
					}
					if (precision < 2u)
					{
						p->x = x - xSign;
						p->y = y - ySign;
						return e;
					}
					return collideLine(type, static_cast<int>(x - xSign), static_cast<double>(y - ySign), toX, toY, p, 1u);
				}
				x += xSign;
				y += ySign;
			}
		}
	}
	else
	{
		xSign *= static_cast<double>(xDelta) / static_cast<double>(yDelta);
		if (ySign > 0.0)
		{
			while (y < static_cast<double>(toY))
			{
				if ((e = collidePoint(type, x, y)))
				{
					if (!p)
					{
						return e;
					}
					if (precision < 2u)
					{
						p->x = x - xSign;
						p->y = y - ySign;
						return e;
					}
					return collideLine(type, static_cast<int>(x - xSign), static_cast<double>(y - ySign), toX, toY, p, 1u);
				}
				x += xSign;
				y += ySign;
			}
		}
		else
		{
			while (y > static_cast<double>(toY))
			{
				if ((e = collidePoint(type, x, y)))
				{
					if (!p)
					{
						return e;
					}
					if (precision < 2u)
					{
						p->x = x - xSign;
						p->y = y - ySign;
						return e;
					}
					return collideLine(type, static_cast<int>(x - xSign), static_cast<double>(y - ySign), toX, toY, p, 1u);
				}
				x += xSign;
				y += ySign;
			}
		}
	}
	
	// Check the last position.
	if (precision > 1u)
	{
		if (!p)
		{
			return collidePoint(type, static_cast<double>(toX), static_cast<double>(toY));
		}
		if (collidePoint(type, static_cast<double>(toX), static_cast<double>(toY)))
		{
			return collideLine(type, static_cast<int>(x - xSign), static_cast<int>(y - ySign), toX, toY, p, 1u);
		}
	}
	
	// No collision, return the end point.
	if (p)
	{
		p->x = static_cast<double>(toX);
		p->y = static_cast<double>(toY);
	}
	return nullptr;
}

std::vector<std::shared_ptr<CPP_Entity> > CPP_World::collideRectInto(const CPP_EntityType type, const double rX, const double rY, const double rWidth, const double rHeight) const
{
	std::vector<std::shared_ptr<CPP_Entity> > ret;
	
	const auto typeMapIterator = typeMap.find(type);
	
	if (typeMapIterator == typeMap.end())
	{
		return ret;
	}
	
	const auto& typeList = typeMapIterator->second;
	
	for (const auto& e : typeList)
	{
		if (e.get()->isCollidable() && e.get()->collideRect(e.get()->getX(), e.get()->getY(), rX, rY, rWidth, rHeight))
		{
			ret.emplace_back(e.get());
		}
	}
	
	return ret;
}

std::vector<std::shared_ptr<CPP_Entity> > CPP_World::collideRectInto(const CPP_EntityType type, const double pX, const double pY) const
{
	std::vector<std::shared_ptr<CPP_Entity> > ret;
	
	const auto typeMapIterator = typeMap.find(type);
	
	if (typeMapIterator == typeMap.end())
	{
		return ret;
	}
	
	const auto& typeList = typeMapIterator->second;
	
	for (const auto& e : typeList)
	{
		if (e.get()->isCollidable() && e.get()->collidePoint(e.get()->getX(), e.get()->getY(), pX, pY))
		{
			ret.emplace_back(e.get());
		}
	}
	
	return ret;
}

std::shared_ptr<CPP_Entity> CPP_World::nearestToRect(const CPP_EntityType type, const double x, const double y, const double width, const double height, const CPP_Entity* const ignore) const
{
	std::shared_ptr<CPP_Entity> ret;
	
	const auto typeMapIterator = typeMap.find(type);
	
	if (typeMapIterator == typeMap.end())
	{
		return ret;
	}
	
	auto nearDist = std::numeric_limits<double>::max();
	
	const auto& typeList = typeMapIterator->second;
	
	for (const auto& e : typeList)
	{
		if (e.get().get() != ignore)
		{
			const auto dist = squareRects(x, y, width, height, e.get()->getX() - static_cast<double>(e.get()->getOriginX()), e.get()->getY() - static_cast<double>(e.get()->getOriginY()), static_cast<double>(e.get()->getWidth()), static_cast<double>(e.get()->getHeight()));
			if (dist < nearDist)
			{
				nearDist = dist;
				ret = e.get();
			}
		}
	}
	
	return ret;
}

std::shared_ptr<CPP_Entity> CPP_World::nearestToEntity(const CPP_EntityType type, const CPP_Entity& e, const bool useHitboxes) const
{
	if (useHitboxes)
	{
		return nearestToRect(type, e.getX() - static_cast<double>(e.getOriginX()), e.getY() - static_cast<double>(e.getOriginY()), static_cast<double>(e.getWidth()), static_cast<double>(e.getHeight()));
	}
	
	std::shared_ptr<CPP_Entity> ret;
	
	const auto typeMapIterator = typeMap.find(type);
	
	if (typeMapIterator == typeMap.end())
	{
		return ret;
	}
	
	auto nearDist = std::numeric_limits<double>::max();
	const auto x = e.getX() - static_cast<double>(e.getOriginX());
	const auto y = e.getY() - static_cast<double>(e.getOriginY());
	
	const auto& typeList = typeMapIterator->second;
	
	for (const auto& n : typeList)
	{
		if (n.get().get() != &e)
		{
			const auto dist = (x - n.get()->getX()) * (x - n.get()->getX()) + (y - n.get()->getY()) * (y - n.get()->getY());
			if (dist < nearDist)
			{
				nearDist = dist;
				ret = n.get();
			}
		}
	}
	
	return ret;
}

std::shared_ptr<CPP_Entity> CPP_World::nearestToPoint(const CPP_EntityType type, const double x, const double y, const bool useHitBoxes) const
{
	std::shared_ptr<CPP_Entity> ret;
	
	const auto typeMapIterator = typeMap.find(type);
	
	if (typeMapIterator == typeMap.end())
	{
		return ret;
	}
	
	auto nearDist = std::numeric_limits<double>::max();
	
	const auto& typeList = typeMapIterator->second;
	
	if (useHitBoxes)
	{
		for (const auto& e : typeList)
		{
			const auto dist = squarePointRect(x, y, e.get()->getX() - static_cast<double>(e.get()->getOriginX()), e.get()->getY() - static_cast<double>(e.get()->getOriginY()), static_cast<double>(e.get()->getWidth()), static_cast<double>(e.get()->getHeight()));
			if (dist < nearDist)
			{
				nearDist = dist;
				ret = e.get();
			}
		}
	}
	else
	{
		for (const auto& e : typeList)
		{
			const auto dist = (x - e.get()->getX()) * (x - e.get()->getX()) + (y - e.get()->getY()) * (y - e.get()->getY());
			if (dist < nearDist)
			{
				nearDist = dist;
				ret = e.get();
			}
		}
	}
	
	return ret;
}

unsigned int CPP_World::getCount() const
{
	return static_cast<unsigned int>(entityMap.size());
}

unsigned int CPP_World::getTypeCount(const CPP_EntityType type) const
{
	const auto typeMapIterator = typeMap.find(type);
	
	if (typeMapIterator == typeMap.cend())
	{
		return 0u;
	}
	
	const auto& typeList = typeMapIterator->second;
	
	return static_cast<unsigned int>(typeList.size());
}

unsigned int CPP_World::getLayerCount(const int layer) const
{
	const auto renderMapIterator = renderMap.find(layer);

	if (renderMapIterator == renderMap.cend())
	{
		return 0u;
	}
	
	return static_cast<unsigned int>(renderMapIterator->second.size());
}

std::shared_ptr<CPP_Entity> CPP_World::getFirst() const
{
	return updateList.empty() ? nullptr : updateList.front().get();
}

unsigned int CPP_World::getLayers() const
{
	return static_cast<unsigned int>(renderMap.size());
}

std::shared_ptr<CPP_Entity> CPP_World::getTypeFirst(const CPP_EntityType type) const
{
	const auto typeMapIterator = typeMap.find(type);
	
	if (typeMapIterator == typeMap.cend())
	{
		return nullptr;
	}
	
	const auto& typeList = typeMapIterator->second;
	
	return typeList.empty() ? nullptr : typeList.front().get();
}

std::shared_ptr<CPP_Entity> CPP_World::getLayerFirst(int layer) const
{
	const auto renderMapIterator = renderMap.find(layer);
	
	if (renderMapIterator == renderMap.cend())
	{
		return nullptr;
	}
	
	return renderMapIterator->second.empty() ? nullptr : renderMapIterator->second.front().get();
}

std::shared_ptr<CPP_Entity> CPP_World::getLayerLast(int layer) const
{
	const auto renderMapIterator = renderMap.find(layer);
	
	if (renderMapIterator == renderMap.cend())
	{
		return nullptr;
	}
	
	return renderMapIterator->second.empty() ? nullptr : renderMapIterator->second.back().get();
}

std::shared_ptr<CPP_Entity> CPP_World::getFarthest() const
{
	return renderMap.empty() ? nullptr : renderMap.begin()->second.front().get();
}

std::shared_ptr<CPP_Entity> CPP_World::getNearest() const
{
	return renderMap.empty() ? nullptr : renderMap.rbegin()->second.front().get();
}

int CPP_World::getLayerFarthest() const
{
	return renderMap.empty() ? 0 : renderMap.begin()->first;
}

int CPP_World::getLayerNearest() const
{
	return renderMap.empty() ? 0 : renderMap.rbegin()->first;
}

unsigned int CPP_World::getUniqueTypes() const
{
	return static_cast<unsigned int>(typeMap.size());
}

std::vector<std::shared_ptr<CPP_Entity> > CPP_World::getType(const CPP_EntityType type) const
{
	std::vector<std::shared_ptr<CPP_Entity> > ret;
	
	const auto typeMapIterator = typeMap.find(type);
	
	if (typeMapIterator == typeMap.cend())
	{
		return ret;
	}
	
	for (const auto& e : typeMapIterator->second)
	{
		ret.emplace_back(e.get());
	}
	
	return ret;
}

std::vector<std::shared_ptr<CPP_Entity> > CPP_World::getLayer(const int layer) const
{
	std::vector<std::shared_ptr<CPP_Entity> > ret;

	const auto renderMapIterator = renderMap.find(layer);
	
	if (renderMapIterator == renderMap.end())
	{
		return ret;
	}
	
	for (const auto& e : renderMapIterator->second)
	{
		ret.emplace_back(e.get());
	}
	
	return ret;
}

std::vector<std::shared_ptr<CPP_Entity> > CPP_World::getAll() const
{
	std::vector<std::shared_ptr<CPP_Entity> > ret;
	
	for (const auto& entityMapPair : entityMap)
	{
		ret.emplace_back(entityMapPair.second.ptr);
	}
	
	return ret;
}

std::shared_ptr<CPP_Entity> CPP_World::getInstance(const std::string& name) const
{
	const auto nameMapIterator = nameMap.find(name);
	
	return (nameMapIterator == nameMap.end()) ? nullptr : nameMapIterator->second.get();
}

void CPP_World::updateLists(const bool shouldAdd)
{
	// Remove entities.
	if (!removeVector.empty())
	{
		for (const auto& entityRef : removeVector)
		{
			const auto& e = entityRef.get();
			const auto eWorld = e.getWorld();
			
			if (!eWorld)
			{
				const auto addIterator = std::find_if(addVector.begin(), addVector.end(), [e](const std::shared_ptr<CPP_Entity>& _e)
													  {
														  return &e == _e.get();
													  });
				if (addIterator != addVector.end())
				{
					addVector.erase(addIterator);
				}
				continue;
			}
			if (eWorld.get() != this)
			{
				continue;
			}
			
			const auto entityMapIterator = entityMap.find(&e);
			
			if (entityMapIterator == entityMap.end())
			{
				continue;
			}
			
			auto const& ptr = entityMapIterator->second.ptr;
			
			ptr->removed();
			ptr->world.reset();
			
			removeUpdate(e);
			removeRender(e);
			if (e.getType())
			{
				removeType(e);
			}
			if (e.getName())
			{
				unregisterName(e);
			}
			// TODO: Tween stuff.
			
			// Remove from the cache.
			entityMap.erase(entityMapIterator);
		}
		// Clear the remove vector.
		removeVector.clear();
	}
	
	// Remove entities.
	if (shouldAdd)
	{
		for (const auto& e : addVector)
		{
			const auto eWorld = e->getWorld();
			
			if (eWorld)
			{
				continue;
			}
			
			// Add to the cache.
			const auto results = entityMap.try_emplace(e.get(), std::move(e));
			
			if (!results.second)
			{
				continue;
			}
			
			const auto& ptr = results.first->second.ptr;
			
			addUpdate(*ptr);
			addRender(*ptr);
			if (ptr->getType())
			{
				addType(*ptr);
			}
			if (ptr->getName())
			{
				registerName(*ptr);
			}
			
			// TODO: Should be using weak_from_this as in C++17.
			ptr->world = shared_from_this();
			ptr->added();
		}
		// Clear the add vector.
		addVector.clear();
	}
	
	// TODO: Recycle stuff.
}


/*
void CPP_World::addUpdate(std::shared_ptr<CPP_Entity> e)
{
	// Add the entity to the entity map if necessary.
	const auto entityMapIterator = entityMap.try_emplace(e.get(), std::move(e)).first;
	
	// Add the entity to the beginning of the update list.
	const auto updateIterator = updateList.insert(updateList.cbegin(), std::cref(entityMapIterator->second.ptr));
	
	// Cache the update iterator.
	entityMapIterator->second.updateIterator = updateIterator;
	
	// TODO: Class count.
}
*/

void CPP_World::addUpdate(const CPP_Entity& e)
{
	// Find the entity in the cache.
	const auto entityMapIterator = entityMap.find(&e);
	
	// Do nothing if the entity is not in the world.
	if (entityMapIterator == entityMap.end())
	{
		return;
	}
	
	// Add the entity to the beginning of the update list.
	const auto updateIterator = updateList.insert(updateList.cbegin(), std::cref(entityMapIterator->second.ptr));
	
	// Cache the update iterator.
	entityMapIterator->second.updateIterator = updateIterator;
	
	// TODO: Class count.
}

void CPP_World::removeUpdate(const CPP_Entity& e)
{
	// Find the entity in the cache.
	const auto entityMapIterator = entityMap.find(&e);

	// Do nothing if the entity is not in the world.
	if (entityMapIterator == entityMap.end())
	{
		return;
	}
	
	// Erase the entity from the update list.
	updateList.erase(entityMapIterator->second.updateIterator);
	
	// TODO: Class count.
}

/*
void CPP_World::addRender(std::shared_ptr<CPP_Entity> e)
{
	// Add the entity to the entity map if necessary.
	const auto entityMapIterator = entityMap.try_emplace(e.get(), std::move(e)).first;
	
	// Add a list to the layer map if necessary.
	const auto renderMapIterator = renderMap.try_emplace(entityMapIterator->second.ptr->getLayer()).first;
	
	// Add the entity to the beginning of the proper layer list.
	const auto renderIterator = renderMapIterator->second.insert(renderMapIterator->second.cbegin(), std::cref(entityMapIterator->second.ptr));
	
	// Cache the render iterator.
	entityMapIterator->second.renderIterator = renderIterator;
}
*/

void CPP_World::addRender(const CPP_Entity& e)
{
	// Find the entity in the cache.
	const auto entityMapIterator = entityMap.find(&e);
	
	// Do nothing if the entity is not in the world.
	if (entityMapIterator == entityMap.end())
	{
		return;
	}
	
	// Add a list to the layer map if necessary.
	const auto renderMapIterator = renderMap.try_emplace(e.getLayer()).first;
	
	// Add the entity to the beginning of the proper layer list.
	const auto renderIterator = renderMapIterator->second.insert(renderMapIterator->second.cbegin(), std::cref(entityMapIterator->second.ptr));
	
	// Cache the render iterator.
	entityMapIterator->second.renderIterator = renderIterator;
}

void CPP_World::removeRender(const CPP_Entity& e)
{
	// Find the entity in the cache.
	const auto entityMapIterator = entityMap.find(&e);
	
	// Do nothing if the entity is not in the world.
	if (entityMapIterator == entityMap.end())
	{
		return;
	}
	
	const auto renderMapIterator = renderMap.find(e.getLayer());
	
	// Erase the entity from the proper layer list.
	renderMapIterator->second.erase(entityMapIterator->second.renderIterator);
	
	// Remove the layer list from the render map if it is now empty.
	if (renderMapIterator->second.empty())
	{
		renderMap.erase(renderMapIterator);
	}
}

/*
void CPP_World::updateRender(const CPP_Entity& e, const int layer)
{
	const auto entityMapIterator = entityMap.find(&e);
	
	// Do nothing if the entity is not in the world.
	if (entityMapIterator == entityMap.end())
	{
		return;
	}

	const auto renderMapIterator = renderMap.find(e.getLayer());
	
	// Erase the entity from the proper layer list.
	renderMapIterator->second.erase(entityMapIterator->second.renderIterator);
	
	// Remove the layer list from the render map if it is now empty.
	if (renderMapIterator->second.empty())
	{
		renderMap.erase(renderMapIterator);
	}
	
	// Add a list to the proper layer map if necessary.
	const auto newRenderMapIterator = renderMap.try_emplace(layer).first;
	
	// Add the entity to the beginning of the proper layer list.
	const auto renderIterator = newRenderMapIterator->second.insert(newRenderMapIterator->second.cbegin(), std::cref(entityMapIterator->second.ptr));
	
	// Cache the render iterator.
	entityMapIterator->second.renderIterator = renderIterator;
}
*/

/*
void CPP_World::addType(std::shared_ptr<CPP_Entity> e)
{
	// Add the entity to the entity map if necessary.
	const auto entityMapIterator = entityMap.try_emplace(e.get(), std::move(e)).first;
	
	// Add a list to the type map if necessary.
	const auto typeMapIterator = typeMap.try_emplace(*entityMapIterator->second.ptr->getType()).first;
	
	// Add the entity to the beginning of the proper type list.
	const auto typeIterator = typeMapIterator->second.insert(typeMapIterator->second.cbegin(), std::cref(entityMapIterator->second.ptr));
	
	// Cache the type iterator.
	entityMapIterator->second.typeIterator = typeIterator;
}
*/

void CPP_World::addType(const CPP_Entity& e)
{
	// Find the entity in the cache.
	const auto entityMapIterator = entityMap.find(&e);
	
	// Do nothing if the entity is not in the world.
	if (entityMapIterator == entityMap.end())
	{
		return;
	}
	
	// Add a list to the type map if necessary.
	const auto typeMapIterator = typeMap.try_emplace(*e.getType()).first;
	
	auto& typeList = typeMapIterator->second;
	
	// Add the entity to the beginning of the proper type list.
	const auto typeIterator = typeList.insert(typeList.cbegin(), std::cref(entityMapIterator->second.ptr));
	
	// Cache the type iterator.
	entityMapIterator->second.typeIterator = typeIterator;
}

void CPP_World::removeType(const CPP_Entity& e)
{
	// Find the entity in the cache.
	const auto entityMapIterator = entityMap.find(&e);
	
	// Do nothing if the entity is not in the world.
	if (entityMapIterator == entityMap.end())
	{
		return;
	}
	
	const auto typeMapIterator = typeMap.find(*e.getType());
	
	auto& typeList = typeMapIterator->second;
	
	// Erase the entity from the proper type list.
	typeList.erase(entityMapIterator->second.typeIterator);
	
	// Remove the type list from the type map if it is now empty.
	if (typeList.empty())
	{
		typeMap.erase(typeMapIterator);
	}
}

/*
void CPP_World::updateType(const CPP_Entity& e, const CPP_EntityType type)
{
	const auto entityMapIterator = entityMap.find(&e);
	
	// Do nothing if the entity is not in the world.
	if (entityMapIterator == entityMap.end())
	{
		return;
	}
	
	if (e.getType())
	{
		const auto typeMapIterator = typeMap.find(*e.getType());
	
		// Erase the entity from the proper type list.
		typeMapIterator->second.erase(entityMapIterator->second.typeIterator);
	
		// Remove the type list from the type map if it is now empty.
		if (typeMapIterator->second.empty())
		{
			typeMap.erase(typeMapIterator);
		}
	}
	
	// Add a list to the proper type map if necessary.
	const auto newTypeMapIterator = typeMap.try_emplace(type).first;
	
	// Add the entity to the beginning of the proper type list.
	const auto typeIterator = newTypeMapIterator->second.insert(newTypeMapIterator->second.cbegin(), std::cref(entityMapIterator->second.ptr));
	
	// Cache the type iterator.
	entityMapIterator->second.typeIterator = typeIterator;
}
*/

void CPP_World::registerName(const CPP_Entity& e)
{
	// Find the entity in the cache.
	const auto entityMapIterator = entityMap.find(&e);
	
	// Do nothing if the entity is not in the world.
	if (entityMapIterator == entityMap.end())
	{
		return;
	}
	
	const auto results = nameMap.try_emplace(*e.getName(), std::cref(entityMapIterator->second.ptr));
	
	// Update the registration if the name is already registered.
	if (!results.second)
	{
		results.first->second = std::cref(entityMapIterator->second.ptr);
	}
}

void CPP_World::unregisterName(const CPP_Entity& e)
{
	// Find the entity in the cache.
	const auto entityMapIterator = entityMap.find(&e);
	
	// Do nothing if the entity is not in the world.
	if (entityMapIterator == entityMap.end())
	{
		return;
	}
	
	const auto nameMapIterator = nameMap.find(*e.getName());
	
	if (nameMapIterator != nameMap.end() && &e == nameMapIterator->second.get().get())
	{
		nameMap.erase(nameMapIterator);
	}
}

double squareRects(const double x1, const double y1, const double w1, const double h1, const double x2, const double y2, const double w2, const double h2)
{
	if (x1 < x2 + w2 && x2 < x1 + w1)
	{
		if (y1 < y2 + h2 && y2 < y1 + h1)
		{
			return 0.0;
		}
		if (y1 > y2)
		{
			return (y1 - (y2 + h2)) * (y1 - (y2 + h2));
		}
		return (y2 - (y1 + h1)) * (y2 - (y1 + h1));
	}
	if (y1 < y2 + h2 && y2 < y1 + h1)
	{
		if (x1 > x2)
		{
			return (x1 - (x2 + w2)) * (x1 - (x2 + w2));
		}
		return (x2 - (x1 + w1)) * (x2 - (x1 + w1));
	}
	if (x1 > x2)
	{
		if (y1 > y2)
		{
			return squarePoints(x1, y1, (x2 + w2), (y2 + h2));
		}
	}
	if (y1 > y2)
	{
		return squarePoints(x1 + w1, y1, x2, y2 + h2);
	}
	return squarePoints(x1 + w1, y1 + h1, x2, y2);
}

double squarePoints(const double x1, const double y1, const double x2, const double y2)
{
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

double squarePointRect(const double pX, const double pY, const double rX, const double rY, const double rW, const double rH)
{
	if (pX >= rX && pX <= rX + rW)
	{
		if (pY >= rY && pY <= rY + rH)
		{
			return 0.0;
		}
		if (pY > rY)
		{
			return (pY - (rY + rH)) * (pY - (rY + rH));
		}
		return (rY - pY) * (rY - pY);
	}
	if (pY >= rY && pY <= rY + rH)
	{
		if (pX > rX)
		{
			return (pX - (rX + rW)) * (pX - (rX + rW));
		}
		return (rX - pX) * (rX - pX);
	}
	if (pX > rX)
	{
		if (pY > rY)
		{
			return squarePoints(pX, pY, rX + rW, rY + rH);
		}
		return squarePoints(pX, pY, rX + rW, rY);
	}
	if (pY > rY)
	{
		return squarePoints(pX, pY, rX, rY + rH);
	}
	return squarePoints(pX, pY, rX, rY);
}
