//
//  CPP_Image.cpp
//  Test
//
//  Created by Wade Okawa-Scannell on 9/2/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_Image.h"

#include "CPP_BitmapDataIF.h"
#include "CPP_Point.h"

#include <utility>

CPP_Image::CPP_Image(std::unique_ptr<CPP_BitmapDataIF> source, std::experimental::optional<CPP_Rectangle> clipRect) :
  originX{0.0}
, originY{0.0}
, bitmapData{std::move(source)}
, clipRect{std::move(clipRect)}
{
}

void CPP_Image::render(const CPP_Point& point, const CPP_Point& camera) const
{
	if (!bitmapData)
	{
		return;
	}
	
	bitmapData->render(CPP_Point{point.x + x - originX - camera.x * scrollX,
	                             point.y + y - originY - camera.y * scrollY}, clipRect);
}

