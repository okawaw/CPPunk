//
//  CPP_Input.cpp
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 2/26/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP_Input.h"

#include "CPP_Key.h"

#include <utility>

void CPP_Input::setImpl(std::unique_ptr<CPP_InputImplIF> _impl)
{
	impl = std::move(_impl);
	
	if (impl)
	{
		impl->registerOnKeyDown([this](const CPP_Key key)
		{
			onKeyDown(key);
		});
		
		impl->registerOnKeyUp([this](const CPP_Key key)
		{
			onKeyUp(key);
		});
	}
}

void CPP_Input::processInput()
{
	if (impl)
	{
		impl->processInput();
	}
}

bool CPP_Input::check(const CPP_Key key) const
{
	return (key == CPP_Key::ANY) ? !activeKeys.empty() : (activeKeys.find(key) != activeKeys.end());
}

bool CPP_Input::pressed(const CPP_Key key) const
{
	return (key == CPP_Key::ANY) ? !pressedKeys.empty() : (pressedKeys.find(key) != pressedKeys.end());
}

bool CPP_Input::released(const CPP_Key key) const
{
	return (key == CPP_Key::ANY) ? !releasedKeys.empty() : (releasedKeys.find(key) != releasedKeys.end());
}

void CPP_Input::update()
{
	pressedKeys.clear();
	releasedKeys.clear();
}

void CPP_Input::clear()
{
	pressedKeys.clear();
	releasedKeys.clear();
	activeKeys.clear();
}

void CPP_Input::onKeyDown(const CPP_Key key)
{
	if (activeKeys.emplace(key).second)
	{
		pressedKeys.emplace(key);
	}
}

void CPP_Input::onKeyUp(const CPP_Key key)
{
	if (activeKeys.erase(key))
	{
		releasedKeys.emplace(key);
	}
}
