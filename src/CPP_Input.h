//
//  CPP_Input.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 2/26/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_Input_h
#define CPP_Input_h

#include "CPP_InputImplIF.h"

#include <memory>
#include <unordered_set>

class CPP_Engine;

enum class CPP_Key;

class CPP_Input
{
	friend CPP_Engine;
public:
	CPP_Input() = default;
	~CPP_Input() = default;
	CPP_Input(const CPP_Input&) = default;
	CPP_Input(CPP_Input&&) = default;
	CPP_Input& operator=(const CPP_Input&) = default;
	CPP_Input& operator=(CPP_Input&&) = default;
	
	void setImpl(std::unique_ptr<CPP_InputImplIF> impl);
	
	void processInput();
	
	bool check(CPP_Key key) const;
	
	bool pressed(CPP_Key key) const;
	
	bool released(CPP_Key key) const;
	
	void update();
	
	void clear();
	
private:
	void onKeyDown(CPP_Key key);
	void onKeyUp(CPP_Key key);
	
	std::unique_ptr<CPP_InputImplIF> impl;
	
	std::unordered_set<CPP_Key> activeKeys;
	std::unordered_set<CPP_Key> pressedKeys;
	std::unordered_set<CPP_Key> releasedKeys;
};

#endif /* CPP_Input_h */
