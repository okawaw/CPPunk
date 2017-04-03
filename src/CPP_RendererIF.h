//
//  CPP_RendererIF.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 3/22/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_RendererIF_h
#define CPP_RendererIF_h

#include <functional>

class CPP_RendererIF
{
public:
	CPP_RendererIF() = default;
	virtual ~CPP_RendererIF() = default;
		
	virtual void render(std::function<void()> renderFunction) const = 0;
};

#endif /* CPP_RendererIF_h */
