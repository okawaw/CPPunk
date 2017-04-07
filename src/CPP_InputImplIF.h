//
//  CPP_InputImplIF.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 3/22/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_InputImplIF_h
#define CPP_InputImplIF_h

#include <functional>

enum class CPP_Key;

class CPP_InputImplIF
{
public:
	CPP_InputImplIF() = default;
	virtual ~CPP_InputImplIF() = default;
	CPP_InputImplIF(const CPP_InputImplIF&) = default;
	CPP_InputImplIF(CPP_InputImplIF&&) = default;
	CPP_InputImplIF& operator=(const CPP_InputImplIF&) = default;
	CPP_InputImplIF& operator=(CPP_InputImplIF&&) = default;
	
	virtual void processInput() const = 0;
	
	virtual void registerOnKeyDown(std::function<void(CPP_Key key)> onKeyDownFunction) = 0;
	virtual void registerOnKeyUp(std::function<void(CPP_Key key)> onKeyUpFunction) = 0;
};

#endif /* CPP_InputImplIF_h */
