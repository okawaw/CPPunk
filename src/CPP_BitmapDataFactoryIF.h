//
//  CPP_BitmapDataFactoryIF.h
//  Test
//
//  Created by Wade Okawa-Scannell on 9/17/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_BitmapDataFactoryIF_h
#define CPP_BitmapDataFactoryIF_h

#include <memory>
#include <string>

class CPP_BitmapDataIF;

class CPP_BitmapDataFactoryIF
{
public:
	CPP_BitmapDataFactoryIF() = default;
	virtual ~CPP_BitmapDataFactoryIF() = default;
	CPP_BitmapDataFactoryIF(const CPP_BitmapDataFactoryIF&) = default;
	CPP_BitmapDataFactoryIF(CPP_BitmapDataFactoryIF&&) = default;
	CPP_BitmapDataFactoryIF& operator=(const CPP_BitmapDataFactoryIF&) = default;
	CPP_BitmapDataFactoryIF& operator=(CPP_BitmapDataFactoryIF&&) = default;
	
	// TODO: Should these be const functions?
	// TODO: Should this be using "transparent"?
	virtual std::unique_ptr<CPP_BitmapDataIF> getBitmapData(const std::string& filename) const = 0;
	virtual std::unique_ptr<CPP_BitmapDataIF> getBitmapData(int width, int height, bool transparent=true, unsigned int fillColor=0xFFFFFFFFu) const = 0;
};

#endif /* CPP_BitmapDataFactoryIF_h */
