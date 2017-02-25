//
//  CPP_Graphic.cpp
//  CPPunk
//
//  Created by Wade Okawa-Scannell on 9/1/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_Graphic.h"

CPP_Graphic::CPP_Graphic() :
  active{false}
, visible{true}
, x{0.0}
, y{0.0}
, scrollX{1.0}
, scrollY{1.0}
, relative{true}
{
}

bool CPP_Graphic::isActive() const
{
	return active;
}

void CPP_Graphic::setActive(const bool value)
{
	active = value;
}

bool CPP_Graphic::isVisible() const
{
	return visible;
}

void CPP_Graphic::setVisible(const bool value)
{
	visible = value;
}

bool CPP_Graphic::isRelative() const
{
	return relative;
}

void CPP_Graphic::setRelative(const bool value)
{
	relative = value;
}

void CPP_Graphic::update()
{
}

void CPP_Graphic::render(const CPP_Point&, const CPP_Point&) const
{
}
