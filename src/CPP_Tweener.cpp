//
//  CPP_Tweener.cpp
//  Test
//
//  Created by Wade Okawa-Scannell on 9/29/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_Tweener.h"

CPP_Tweener::CPP_Tweener() :
active{true}
{
}

bool CPP_Tweener::isActive() const
{
	return active;
}

void CPP_Tweener::setActive(const bool value)
{
	active = value;
}

bool CPP_Tweener::isAutoClear() const
{
	return autoClear;
}

void CPP_Tweener::setAutoClear(const bool value)
{
	autoClear = value;
}

void CPP_Tweener::update()
{
}
