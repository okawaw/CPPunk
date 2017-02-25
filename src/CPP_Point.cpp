//
//  CPP_Point.cpp
//  CPPunk
//
//  Created by Wade Okawa-Scannell on 8/28/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_Point.h"

#include <cmath>

CPP_Point::CPP_Point(const double x, const double y) :
  x{x}
, y{y}
{
}

CPP_Point& CPP_Point::operator+=(const CPP_Point& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

CPP_Point& CPP_Point::operator-=(const CPP_Point& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

double CPP_Point::getLength() const
{
	return std::sqrt(std::pow(x, 2.0) + std::pow(y, 2.0));
}

double CPP_Point::distance(const CPP_Point& pt1, const CPP_Point& pt2)
{
	return std::sqrt(std::pow(pt2.x - pt1.x, 2.0) + std::pow(pt2.y - pt1.y, 2.0));
}

CPP_Point CPP_Point::interpolate(const CPP_Point& pt1, const CPP_Point& pt2, const double f)
{
	return {pt2.x + (pt1.x - pt2.x) * f, pt2.y + (pt1.y - pt2.y) * f};
}

void CPP_Point::normalize(const double thickness)
{
	const auto length{getLength()};
	
	if (length == 0.0)
	{
		x = 0.0;
		y = 0.0;
	}
	else
	{
		x *= (thickness / length);
		y *= (thickness / length);
	}
}

CPP_Point CPP_Point::polar(const double len, const double angle)
{
	return {len * std::cos(angle), len * std::sin(angle)};
}

std::string CPP_Point::toString() const
{
	using std::string_literals::operator""s;
	return "(x="s + std::to_string(x) + ", y="s + std::to_string(y) + ")"s;
}

CPP_Point operator+(CPP_Point lhs, const CPP_Point& rhs)
{
	lhs += rhs;
	return lhs;
}

CPP_Point operator-(CPP_Point lhs, const CPP_Point& rhs)
{
	lhs -= rhs;
	return lhs;
}

bool operator==(const CPP_Point& lhs, const CPP_Point& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const CPP_Point& lhs, const CPP_Point& rhs)
{
	return !(lhs == rhs);
}
