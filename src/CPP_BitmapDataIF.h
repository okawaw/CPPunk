//
//  CPP_BitmapDataIF.h
//  Test
//
//  Created by Wade Okawa-Scannell on 8/28/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_BitmapDataIF_h
#define CPP_BitmapDataIF_h

#include "CPP_Rectangle.h"

#include <experimental/optional>

class CPP_Point;

enum class CPP_BlendMode;

class CPP_BitmapDataIF
{
public:
	CPP_BitmapDataIF() = default;
	virtual ~CPP_BitmapDataIF() = default;
	CPP_BitmapDataIF(const CPP_BitmapDataIF&) = default;
	CPP_BitmapDataIF(CPP_BitmapDataIF&&) = default;
	CPP_BitmapDataIF& operator=(const CPP_BitmapDataIF&) = default;
	CPP_BitmapDataIF& operator=(CPP_BitmapDataIF&&) = default;
	
	virtual int getHeight() const = 0;
	virtual int getWidth() const = 0;
	
	virtual CPP_Rectangle getRect() const = 0;
	
	virtual bool isTransparent() const = 0;
	
	// TODO:
	// void applyFilter()
	
	// TODO:
	// void colorTransform()
	
	// TODO:
	// CPP_BitmapDataIF compare();
	
	// TODO:
	// void copyChannel();
	
	//virtual void copyPixels(const CPP_BitmapDataIF* sourceBitmapData, const CPP_Rectangle& sourceRect,
	//                        const CPP_Point& destPoint, const bool mergeAlpha) const = 0
	
	//virtual void dispose() = 0;
	
	virtual void render(const CPP_Point& destPoint, const std::experimental::optional<CPP_Rectangle>& clipRect=std::experimental::nullopt) const = 0;
	
	virtual void lock() = 0;
	virtual void unlock() = 0;
};

#endif /* CPP_BitmapDataIF_h */
