//
//  CPP_Point.h
//  CPPunk
//
//  Created by Wade Okawa-Scannell on 8/28/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_Point_h
#define CPP_Point_h

#include <string>

// The CPP_Point object represents a location in a two-dimensional coordinate system, where x
// represents the horizontal axis and y represents the vertical axis.
class CPP_Point
{
public:
	// Creates a new point. If you pass no parameters to this method, a point is created at (0.0, 0.0).
	CPP_Point(double x=0.0, double y=0.0);
	
	// Adds the coordinates of another point to the coordinates of this point.
	CPP_Point& operator+=(const CPP_Point& other);
	
	// Subtracts the coordinates of another point from the coordinates of this point.
	CPP_Point& operator-=(const CPP_Point& other);
	
	// The length of the line segment from (0.0, 0.0) to this point.
	double getLength() const;
	
	// Returns the distance between pt1 and pt2.
	static double distance(const CPP_Point& pt1, const CPP_Point& pt2);
	
	// Determines a point between two specified points. The parameter f
	// determines where the new interpolated point is located relative to the two end points
	// specified by parameters pt1 and pt2. The closer the value of the parameter
	// f is to 1.0, the closer the interpolated point is to the
	// first point (parameter pt1). The closer the value of the parameter f is
	// to 0.0, the closer the interpolated point is to the second point (parameter pt2).
	static CPP_Point interpolate(const CPP_Point& pt1, const CPP_Point& pt2, double f);
	
	// Scales the line segment between (0.0, 0.0) and the current point to a set length.
	void normalize(double thickness);
	
	// Converts a pair of polar coordinates to a Cartesian point coordinate.
	static CPP_Point polar(double len, double angle);
	
	// Returns a string that contains the values of the x and y coordinates.
	std::string toString() const;
	
	// The horizontal coordinate of the point. The default value is 0.0.
	double x;
	
	// The vertical coordinate of the point. The default value is 0.0.
	double y;
};

// Adds the coordinates of a point to the coordinates of another point to create a new point.
CPP_Point operator+(CPP_Point lhs, const CPP_Point& rhs);

// Subtracts the coordinates of a point from the coordinates of another point to create a new
// point.
CPP_Point operator-(CPP_Point lhs, const CPP_Point& rhs);

// Determines whether two points are equal. Two points are equal if they have the same x and
// y values.
bool operator==(const CPP_Point& lhs, const CPP_Point& rhs);
bool operator!=(const CPP_Point& lhs, const CPP_Point& rhs);

#endif /* CPP_Point_h */
