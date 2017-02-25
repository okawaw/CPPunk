//
//  CPP_Rectangle.h
//  CPPunk
//
//  Created by Wade Okawa-Scannell on 8/28/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_Rectangle_h
#define CPP_Rectangle_h

#include <string>

class CPP_Point;

// A CPP_Rectangle object is an area defined by its position as
// indicated by its top-left corner point (x, y) and by its width
// and its height.
class CPP_Rectangle
{
public:
	// Creates a new CPP_Rectangle object with the top-left corner specified by the x
	// and y parameters and with the specified width and height
	// parameters. If you call this function without parameters,
	// a rectangle with x, y, width, and height
	// properties set to 0.0 is created.
	CPP_Rectangle(double x=0.0, double y=0.0, double width=0.0, double height=0.0);
	
	// The sum of the y and height properties.
	double getBottom() const;
	void setBottom(double value);
	
	// The location of the CPP_Rectangle object's bottom-right corner, determined by the values of the right and
	// bottom properties.
	CPP_Point getBottomRight() const;
	void setBottomRight(const CPP_Point& value);
	
	// The x coordinate of the top-left corner of the rectangle. Changing
	// the left property of a CPP_Rectangle object has no effect on the y
	// and height properties. However it does affect the width
	// property, whereas changing the x value does not affect the
	// width property.
	double getLeft() const;
	void setLeft(double value);
	
	// The sum of the x and
	// width properties.
	double getRight() const;
	void setRight(double value);
	
	// The size of the CPP_Rectangle object, xpressed as a CPP_Point object with the values
	// of the width and height properties.
	CPP_Point getSize() const;
	void setSize(const CPP_Point& value);
	
	// The y coordinate of the top-left corner of the rectangle. Changing
	// the top property of a CPP_Rectangle object has no effect on the x
	// and width properties. However it does affect the height
	// property, wheras changing the y value does not affect the
	// height property.
	double getTop() const;
	void setTop(double value);
	
	// The location of the CPP_Rectangle object's top-left corner, determined by the x and
	// y coordinates of the point.
	CPP_Point getTopLeft() const;
	void setTopLeft(const CPP_Point& value);
	
	// Determines whether the specified point is contained within the rectangular region defined
	// by this CPP_Rectangle object.
	bool contains(double x, double y) const;
	
	// Determines whether the specified point is contained within the rectangular region defined
	// by this CPP_Rectangle object. This method is similar to the CPP_Rectangle::contains(double, double) method,
	// except that it takes a CPP_Point object as a parameter.
	bool containsPoint(const CPP_Point& point) const;
	
	// Determines whether the CPP_Rectangle object specified by the rect parameter is contained
	// within this CPP_Rectangle object. A CPP_Rectangle object is said to contain another if the second
	// CPP_Rectangle object falls entirely within the boundaries of the first.
	bool containsRect(const CPP_Rectangle& rect) const;
	
	// Increases the size of the CPP_Rectangle object by the specified amounts, in pixels. The center point of the
	// CPP_Rectangle object stays the same, and its size increases to the left and right by the
	// dx value, and to the top and bottom by the dy value.
	void inflate(double dx, double dy);
	
	// Increases the size of the CPP_Rectangle object.
	// This method is similar to the CPP_Rectangle::inflate(double, double) method
	// except it takes a CPP_Point object as a parameter.
	void inflatePoint(const CPP_Point& point);
	
	// If the CPP_Rectangle object specified in the toIntersect parameter intersects with this CPP_Rectangle
	// object, returns the area of the intersection as a CPP_Rectangle object.
	// If the rectangles do not intersect, this method returns an empty CPP_Rectangle object with its properties
	// set to 0.
	CPP_Rectangle intersection(CPP_Rectangle toIntersect) const;
	
	// Determines whether the object specified in the toIntersect parameter intersects
	// with this CPP_Rectangle object. This method checks the x, y,
	// width, and height properties of the specified CPP_Rectangle object to see
	// if it intersects with this CPP_Rectangle object.
	bool intersects(const CPP_Rectangle& toIntersect) const;
	
	// Determines whether or not this CPP_Rectangle object is empty.
	bool isEmpty() const;
	
	// Adjusts the location of the CPP_Rectangle object, as determined by its top-left corner,
	// by the specified amounts.
	void offset(double dx, double dy);
	
	// Adjusts the location of the CPP_Rectangle object using a CPP_Point object as a parameter.
	// This method is similar to the CPP_Rectangle::offset(double, double) method, except that it takes a CPP_Point
	// object as a parameter.
	void offsetPoint(const CPP_Point& point);
	
	// Sets all of the CPP_Rectangle object's properties to 0.0. A CPP_Rectangle object is empty if its width or
	// height is less than or equal to 0.0.
	void setEmpty();
	
	// Builds and returns a string that lists the horizontal and vertical positions
	// and the width and height of the CPP_Rectangle object.
	std::string toString() const;
	
	// Adds two rectangles together to create a new CPP_Rectangle object, by
	// filling in the horizontal and vertical space between the two rectangles.
	CPP_Rectangle unionRectangle(CPP_Rectangle toUnion) const;
	
	// The x coordinate of the top-left corner of the rectangle. Changing
	// the value of the x property of a CPP_Rectangle has no effect on the
	// y, width, and height properties.
	double x;
	
	// The y coordinate of the top-left corner of the rectangle. Changing
	// the value of the y property of a CPP_Rectangle has no effect on the
	// x, width, and height properties.
	double y;
	
	// The width of the rectangle, in pixels. Changing the width value of a CPP_Rectangle
	// has no effect on the x, y, and height properties.
	double width;
	
	// The height of the rectangle, in pixels. Changing the height value of a CPP_Rectangle
	// has no effect on the x, y, and width properties.
	double height;
};

// Determines whether the CPP_Rectangle objects specified are equal.
// This method compares the x, y, width, and height properties of one
// CPP_Rectangle object against the other.
bool operator==(const CPP_Rectangle& lhs, const CPP_Rectangle& rhs);
bool operator!=(const CPP_Rectangle& lhs, const CPP_Rectangle& rhs);

#endif /* CPP_Rectangle_h */
