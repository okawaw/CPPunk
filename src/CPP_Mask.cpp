//
//  CPP_Mask.cpp
//  Test
//
//  Created by Wade Okawa-Scannell on 10/10/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_Mask.h"

CPP_Mask::CPP_Mask() :
  parent{nullptr}
{
}

void CPP_Mask::assignTo(CPP_Entity* const _parent)
{
	parent = _parent;
	
	if (!list && parent)
	{
		update();
	}
}

void CPP_Mask::update()
{
}
