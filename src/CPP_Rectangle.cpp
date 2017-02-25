//
//  CPP_Rectangle.cpp
//  CPPunk
//
//  Created by Wade Okawa-Scannell on 8/29/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_Rectangle.h"

#include "CPP_Point.h"

#include <algorithm>

CPP_Rectangle::CPP_Rectangle(const double x, const double y, const double width, const double height) :
  x{x}
, y{y}
, width{width}
, height{height}
{
}

double CPP_Rectangle::getBottom() const
{
	return y + height;
}

void CPP_Rectangle::setBottom(const double value)
{
	height = value - y;
}

CPP_Point CPP_Rectangle::getBottomRight() const
{
	return {getRight(), getBottom()};
}

void CPP_Rectangle::setBottomRight(const CPP_Point& value)
{
	setRight(value.x);
	setBottom(value.y);
}

double CPP_Rectangle::getLeft() const
{
	return x;
}

void CPP_Rectangle::setLeft(const double value)
{
	width = getRight() - value;
	x = value;
}

double CPP_Rectangle::getRight() const
{
	return x + width;
}

void CPP_Rectangle::setRight(const double value)
{
	width = value - x;
}

CPP_Point CPP_Rectangle::getSize() const
{
	return {width, height};
}

void CPP_Rectangle::setSize(const CPP_Point& value)
{
	width = value.x;
	height = value.y;
}

double CPP_Rectangle::getTop() const
{
	return y;
}

void CPP_Rectangle::setTop(const double value)
{
	height = getBottom() - value;
	y = value;
}

CPP_Point CPP_Rectangle::getTopLeft() const
{
	return {getLeft(), getTop()};
}

void CPP_Rectangle::setTopLeft(const CPP_Point& value)
{
	setLeft(value.x);
	setTop(value.y);
}

bool CPP_Rectangle::contains(const double x, const double y) const
{
	if (isEmpty())
	{
		return false;
	}
	
	return getLeft() <= x && x < getRight() &&
	       getTop() <= y && y < getBottom();
}

bool CPP_Rectangle::containsPoint(const CPP_Point& point) const
{
	return contains(point.x, point.y);
}

bool CPP_Rectangle::containsRect(const CPP_Rectangle& rect) const
{
	if (isEmpty())
	{
		return false;
	}
	
	if (rect.width > 0)
	{
		if (!(getLeft() <= rect.getLeft() &&
		      rect.getRight() <= getRight()))
		{
			return false;
		}
	}
	else
	{
		if (!(getLeft() < rect.getRight() &&
			  rect.getLeft() < getRight()))
		{
			return false;
		}
	}
	
	if (rect.height > 0)
	{
		if (!(getTop() <= rect.getTop() &&
		     rect.getBottom() <= getBottom()))
		{
			return false;
		}
	}
	else
	{
		if (!(getTop() < rect.getBottom() &&
		      rect.getTop() < getBottom()))
		{
			return false;
		}
	}
	
	return true;
}

void CPP_Rectangle::inflate(const double dx, const double dy)
{
	x -= dx;
	setRight(getRight() + dx);
	y -= dy;
	setBottom(getBottom() + dy);
}

void CPP_Rectangle::inflatePoint(const CPP_Point& point)
{
	inflate(point.x, point.y);
}

CPP_Rectangle CPP_Rectangle::intersection(CPP_Rectangle toIntersect) const
{
	if (!isEmpty() && !toIntersect.isEmpty())
	{
		// TODO: DOUBLE CHECK THAT THESE CAN BE CHANGED INDEPENDENTLY IN PLACE!!!
		toIntersect.setLeft(std::max(x, toIntersect.x));
		toIntersect.setTop(std::max(y, toIntersect.y));
		toIntersect.setRight(std::min(getRight(), toIntersect.getRight()));
		toIntersect.setBottom(std::min(getBottom(), toIntersect.getBottom()));
		
		if (toIntersect.isEmpty())
		{
			toIntersect.setEmpty();
		}
	}
	else
	{
		toIntersect.setEmpty();
	}
	
	return toIntersect;
}

// TODO: Check this function.
bool CPP_Rectangle::intersects(const CPP_Rectangle& toIntersect) const
{
	return (!isEmpty() && !toIntersect.isEmpty() &&
	        (getLeft() < toIntersect.getRight() &&
	         toIntersect.getLeft() < getRight() &&
	         getTop() < toIntersect.getBottom() &&
	         toIntersect.getTop() < getBottom()));
}

bool CPP_Rectangle::isEmpty() const
{
	return width <= 0.0 || height <= 0.0;
}

void CPP_Rectangle::offset(const double dx, const double dy)
{
	x += dx;
	y += dy;
}

void CPP_Rectangle::offsetPoint(const CPP_Point& point)
{
	offset(point.x, point.y);
}

std::string CPP_Rectangle::toString() const
{
	using std::string_literals::operator""s;
	return "(x="s + std::to_string(x) + ", y="s + std::to_string(y) +
	       ", w="s + std::to_string(width) + ", h="s + std::to_string(height) + ")"s;
}

void CPP_Rectangle::setEmpty()
{
	x = 0.0;
	y = 0.0;
	width = 0.0;
	height = 0.0;
}

// TODO: Check this function.
CPP_Rectangle CPP_Rectangle::unionRectangle(CPP_Rectangle toUnion) const
{
	if (isEmpty())
	{
		return toUnion;
	}
	
	if (toUnion.isEmpty())
	{
		return *this;
	}
	
	toUnion.setLeft(std::min(x, toUnion.x));
	toUnion.setTop(std::min(y, toUnion.y));
	toUnion.setRight(std::max(getRight(), toUnion.getRight()));
	toUnion.setBottom(std::max(getBottom(), toUnion.getBottom()));
	
	return toUnion;
}

bool operator==(const CPP_Rectangle& lhs, const CPP_Rectangle& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y &&
	       lhs.width == rhs.width && lhs.height == rhs.height;
}

bool operator!=(const CPP_Rectangle& lhs, const CPP_Rectangle& rhs)
{
	return !(lhs == rhs);
}
