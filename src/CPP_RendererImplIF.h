//
//  CPP_RendererImplIF.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 3/22/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_RendererImplIF_h
#define CPP_RendererImplIF_h

class CPP_RendererImplIF
{
public:
	CPP_RendererImplIF() = default;
	virtual ~CPP_RendererImplIF() = default;
	CPP_RendererImplIF(const CPP_RendererImplIF&) = default;
	CPP_RendererImplIF(CPP_RendererImplIF&&) = default;
	CPP_RendererImplIF& operator=(const CPP_RendererImplIF&) = default;
	CPP_RendererImplIF& operator=(CPP_RendererImplIF&&) = default;
	
	virtual void render() const = 0;
};

#endif /* CPP_RendererImplIF_h */
