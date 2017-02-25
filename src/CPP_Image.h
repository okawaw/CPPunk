//
//  CPP_Image.h
//  Test
//
//  Created by Wade Okawa-Scannell on 9/1/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_Image_h
#define CPP_Image_h

#include "CPP_Graphic.h"

#include "CPP_BitmapDataIF.h"
#include "CPP_Rectangle.h"

#include <memory>
#include <experimental/optional>

class CPP_Point;

// Performance-optimized non-animated image. Can be drawn to the screen with transformations.
class CPP_Image : public CPP_Graphic
{
public:
	// TODO: See if other constructors are necessary.
	CPP_Image(std::unique_ptr<CPP_BitmapDataIF> source, std::experimental::optional<CPP_Rectangle> clipRect=std::experimental::nullopt);
	
	// X origin of the image, determines transformation point.
	// Defaults to top-left corner.
	double originX;
	
	// Y origin of the image, determines transformation point.
	// Defaults to top-left corner.
	double originY;
	
	virtual void render(const CPP_Point& point, const CPP_Point& camera) const override;

	std::unique_ptr<CPP_BitmapDataIF> bitmapData;
	std::experimental::optional<CPP_Rectangle> clipRect;
};

#endif /* CPP_Image_h */
