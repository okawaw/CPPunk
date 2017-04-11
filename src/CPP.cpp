//
//  CPP.cpp
//  Test
//
//  Created by Wade Okawa-Scannell on 9/20/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#include "CPP.h"

#include "CPP_BitmapDataIF.h"
#include "CPP_BitmapDataFactoryIF.h"

#include <algorithm>
#include <utility>

using std::string_literals::operator""s;

// TODO: Make sure all member variables are initialized in the CORRECT ORDER.
CPP::CPP() :
  VERSION{"1.0.0"s}
, title{"untitled"s}
, width{0u}
, height{0u}
, halfWidth{0.0}
, halfHeight{0.0}
, fixed{false}
, timeInFrames{false}
, frameTime{std::chrono::steady_clock::duration::zero()}
, frameRate{0.0}
, assignedFrameTime{std::chrono::steady_clock::duration::zero()}
, assignedFrameRate{0.0}
, elapsed{std::chrono::steady_clock::duration::zero()}
, rate{1.0}
, focused{true}
, engine{nullptr}
, updateTime{std::chrono::steady_clock::duration::zero()}
, renderTime{std::chrono::steady_clock::duration::zero()}
, gameTime{std::chrono::steady_clock::duration::zero()}
, flashTime{std::chrono::steady_clock::duration::zero()}
, _volume{0.0}
, _pan{0.0}
, _getSeed{std::minstd_rand0::default_seed}
{
}

std::string CPP::getVersion() const
{
	return VERSION;
}

std::string CPP::getTitle() const
{
	return title;
}

unsigned int CPP::getWidth() const
{
	return width;
}

void CPP::setWidth(const unsigned int value)
{
	width = value;
	halfWidth = static_cast<double>(value) / 2.0;
}

unsigned int CPP::getHeight() const
{
	return height;
}

void CPP::setHeight(const unsigned int value)
{
	height = value;
	halfHeight = static_cast<double>(value) / 2.0;
}

double CPP::getHalfWidth() const
{
	return halfWidth;
}

double CPP::getHalfHeight() const
{
	return halfHeight;
}

bool CPP::isFixed() const
{
	return fixed;
}

bool CPP::isTimeInFrames() const
{
	return timeInFrames;
}

double CPP::getFrameRate() const
{
	return frameRate;
}

double CPP::getAssignedFrameRate() const
{
	return assignedFrameRate;
}

double CPP::getElapsed() const
{
	return std::chrono::duration<double>{elapsed}.count();
}

double CPP::getRate() const
{
	return rate;
}

CPP_Rectangle CPP::getBounds() const
{
	return bounds;
}

void CPP::setBounds(const CPP_Rectangle& value)
{
	bounds = value;
}

bool CPP::isFocused() const
{
	return focused;
}

void CPP::resize(const int _width, const int _height)
{
	width = static_cast<unsigned int>(_width);
	height = static_cast<unsigned int>(_height);
	halfWidth = static_cast<double>(_width) / 2.0;
	halfHeight = static_cast<double>(_height) / 2.0;
	bounds.width = static_cast<double>(_width);
	bounds.height = static_cast<double>(_height);
}

std::shared_ptr<CPP_World> CPP::getWorld() const
{
	return world;
}

void CPP::setWorld(std::shared_ptr<CPP_World> value)
{
	if (gotoWorld)
	{
		if (gotoWorld == value)
		{
			return;
		}
	}
	else
	{
		if (world == value)
		{
			return;
		}
	}
	
	gotoWorld = std::move(value);
}

CPP_Point CPP::getCamera() const
{
	return camera;
}

void CPP::setCamera(const CPP_Point& value)
{
	camera = value;
}

void CPP::resetCamera()
{
	camera.x = 0.0;
	camera.y = 0.0;
}

double CPP::getVolume() const
{
	return _volume;
}

// TODO: Come back to this once sound is implemented.
void CPP::setVolume(const double value)
{
	const auto volume = (value < 0.0) ? 0.0 : value;

	if (_volume == volume)
	{
		return;
	}
	
	_volume = volume;
}

double CPP::getPan() const
{
	return _pan;
}

void CPP::setPan(const double value)
{
	const auto pan = (value < -1.0) ? -1.0 : ((value > 1.0) ? 1.0 : value);
	
	if (_pan == pan)
	{
		return;
	}
	
	_pan = pan;
}

double  CPP::approach(const double value, const double target, const double amount)
{
	if (value < target - amount)
	{
		return value + amount;
	}
	else if (value > target + amount)
	{
		return value - amount;
	}
	else
	{
		return target;
	}
}

double CPP::lerp(const double a, const double b, const double t)
{
	return a + (b - a) * t;
}

unsigned int CPP::colorLerp(const unsigned int fromColor, const unsigned int toColor, const double t)
{
	if (t <= 0.0)
	{
		return fromColor;
	}
	if (t >= 1.0)
	{
		return toColor;
	}
	unsigned int a = fromColor >> 24u & 0xFFu;
	unsigned int r = fromColor >> 16u & 0xFFu;
	unsigned int g = fromColor >> 8u & 0xFFu;
	unsigned int b = fromColor & 0xFFu;
	const int dA = (toColor >> 24 & 0xFF) - static_cast<int>(a);
	const int dR = (toColor >> 16 & 0xFF) - static_cast<int>(r);
	const int dG = (toColor >> 8 & 0xFF) - static_cast<int>(g);
	const int dB = (toColor & 0xFF) - static_cast<int>(b);
	a += static_cast<unsigned int>(static_cast<double>(dA) * t);
	r += static_cast<unsigned int>(static_cast<double>(dR) * t);
	g += static_cast<unsigned int>(static_cast<double>(dG) * t);
	b += static_cast<unsigned int>(static_cast<double>(dB) * t);
	return a << 24u | r << 16u | g << 8u | b;
}

double CPP::radiansToDegrees(const double value)
{
	return value * -180.0 / M_PI;
}

double CPP::degreesToRadians(const double value)
{
	return value * M_PI / -180.0;
}

double CPP::angle(const double x1, const double y1, const double x2, const double y2)
{
	const auto a = radiansToDegrees(std::atan2(y2 - y1, x2 - x1));
	return (a < 0.0) ? a + 360.0 : a;
}

double CPP::angleDiff(const double a, const double b)
{
	auto diff = b - a;

	while (diff > 180.0)
	{
		diff -= 360.0;
	}
	while (diff <= -180.0)
	{
		diff += 360.0;
	}
	
	return diff;
}

double CPP::distance(const double x1, const double y1, const double x2, const double y2)
{
	return std::sqrt(std::pow(x2 - x1, 2.0) + std::pow(y2 - y1, 2.0));
}

double CPP::distanceRects(const double x1, const double y1, const double w1, const double h1, const double x2, const double y2, const double w2, const double h2)
{
	if (x1 < x2 + w2 && x2 < x1 + w1)
	{
		if (y1 < y2 + h2 && y2 < y1 + h1)
		{
			return 0.0;
		}
		if (y1 > y2)
		{
			return y1 - (y2 + h2);
		}
		return y2 - (y1 + h1);
	}
	if (y1 < y2 + h2 && y2 < y1 + h1)
	{
		if (x1 > x2)
		{
			return x1 - (x2 + w2);
		}
		return x2 - (x1 + w1);
	}
	if (x1 > x2)
	{
		if (y1 > y2)
		{
			return distance(x1, y1, (x2 + w2), (y2 + h2));
		}
		return distance(x1, y1 + h1, x2 + w2, y2);
	}
	if (y1 > y2)
	{
		return distance(x1 + w1, y1, x2, y2 + h2);
	}
	return distance(x1 + w1, y1 + h1, x2, y2);
}

double CPP::distanceRectPoint(const double px, const double py, const double rx, const double ry, const double rw, const double rh)
{
	if (px >= rx && px <= rx + rw)
	{
		if (py >= ry && py <= ry + rh)
		{
			return 0.0;
		}
		if (py > ry)
		{
			return py - (ry + rh);
		}
		return ry - py;
	}
	if (py >= ry && py <= ry + rh)
	{
		if (px > rx)
		{
			return px - (rx + rw);
		}
		return rx - px;
	}
	if (px > rx)
	{
		if (py > ry)
		{
			return distance(px, py, rx + rw, ry + rh);
		}
		return distance(px, py, rx + rw, ry);
	}
	if (py > ry)
	{
		return distance(px, py, rx, ry + rh);
	}
	return distance(px, py, rx, ry);
}

double CPP::clamp(const double value, const double min, const double max)
{
	if (max > min)
	{
		if (value < min)
		{
			return min;
		}
		else if (value > max)
		{
			return max;
		}
		else
		{
			return value;
		}
	}
	else
	{
		// Min/max swapped.
		if (value < max)
		{
			return max;
		}
		else if (value > min)
		{
			return min;
		}
		else
		{
			return value;
		}
	}
}

double CPP::scale(const double value, const double min, const double max, const double min2, const double max2)
{
	return min2 + ((value - min) / (max - min)) * (max2 - min2);
}

double CPP::scaleClamp(const double _value, const double min, const double max, const double min2, const double max2)
{
	auto value = min2 + ((_value - min) / (max - min)) * (max2 - min2);
	if (max2 > min2)
	{
		value = value < max2 ? value : max2;
		return value > min2 ? value : min2;
	}
	value = value < min2 ? value : min2;
	return value > max2 ? value : max2;
}

std::minstd_rand0::result_type CPP::getRandomSeed() const
{
	return _getSeed;
}

void CPP::setRandomSeed(const std::minstd_rand0::result_type value)
{
	rnEngine.seed(value);
	_getSeed = value;
}

void CPP::randomizeSeed()
{
	setRandomSeed(static_cast<std::minstd_rand0::result_type>(rd()));
}

std::uniform_int_distribution<>::result_type CPP::getRandom()
{
	return dist(rnEngine);
}

unsigned int CPP::rand(const unsigned int amount)
{
	return static_cast<unsigned int>(getRandom() * static_cast<std::uniform_int_distribution<>::result_type>(amount));
}

unsigned int CPP::getColorRGB(const unsigned int r, const unsigned int g, const unsigned int b)
{
	return r << 16u | g << 8u | b;
}

unsigned int CPP::getColorHSV(const double _h, const double _s, const double _v)
{
	auto h = _h < 0.0 ? 0.0 : (_h > 1.0 ? 1.0 : _h);
	const auto s = _s < 0.0 ? 0.0 : (_s > 1.0 ? 1.0 : _s);
	const auto v = _v < 0.0 ? 0.0 : (_v > 1.0 ? 1.0 : _v);
	h = std::trunc(h * 360.0);
	const auto hi = static_cast<unsigned int>(h / 60.0) % 6u;
	const auto f = h / 60.0 - std::trunc(h / 60.0);
	const auto p = (v * (1.0 - s));
	const auto q = (v * (1.0 - f * s));
	const auto t = (v * (1.0 - (1.0 - f) * s));
	switch(hi)
	{
		case 0:
		{
			return static_cast<unsigned int>(v * 255.0) << 16u | static_cast<unsigned int>(t * 255.0) << 8u | static_cast<unsigned int>(p * 255.0);
			break;
		}
		case 1:
		{
			return static_cast<unsigned int>(q * 255.0) << 16u | static_cast<unsigned int>(v * 255.0) << 8u | static_cast<unsigned int>(p * 255.0);
			break;
		}
		case 2:
		{
			return static_cast<unsigned int>(p * 255.0) << 16u | static_cast<unsigned int>(v * 255.0) << 8u | static_cast<unsigned int>(t * 255.0);
			break;
		}
		case 3:
		{
			return static_cast<unsigned int>(p * 255.0) << 16u | static_cast<unsigned int>(q * 255.0) << 8u | static_cast<unsigned int>(v * 255.0);
			break;
		}
		case 4:
		{
			return static_cast<unsigned int>(t * 255.0) << 16u | static_cast<unsigned int>(p * 255.0) << 8u | static_cast<unsigned int>(v * 255.0);
			break;
		}
		case 5:
		{
			return static_cast<unsigned int>(v * 255.0) << 16u | static_cast<unsigned int>(p * 255.0) << 8u | static_cast<unsigned int>(q * 255.0);
			break;
		}
		default:
		{
			return 0u;
			break;
		}
	}
}

double CPP::getColorHue(const unsigned int color)
{
	const auto r = (color >> 16u) & 0xFFu;
	const auto g = (color >> 8u) & 0xFFu;
	const auto b = color & 0xFFu;
	
	const auto max = std::max({r, g, b});
	const auto min = std::min({r, g, b});
	
	auto hue = 0u;
	
	if (max == min)
	{
		hue = 0u;
	}
	else if (max == r)
	{
		hue = (static_cast<unsigned int>(static_cast<double>(60 * (static_cast<int>(g) - static_cast<int>(b))) / static_cast<double>(max - min)) + 360u) % 360u;
	}
	else if (max == g)
	{
		hue = (static_cast<unsigned int>(static_cast<double>(60 * (static_cast<int>(b) - static_cast<int>(r))) / static_cast<double>(max - min)) + 120u);
	}
	else if (max == b)
	{
		hue = (static_cast<unsigned int>(static_cast<double>(60 * (static_cast<int>(r) - static_cast<int>(g))) / static_cast<double>(max - min)) + 240u);
	}
	
	return static_cast<double>(hue) / 360.0;
}

double CPP::getColorSaturation(const unsigned int color)
{
	const auto r = (color >> 16u) & 0xFFu;
	const auto g = (color >> 8u) & 0xFFu;
	const auto b = color & 0xFFu;
	
	const auto max = std::max({r, g, b});
	const auto min = std::min({r, g, b});
	
	if (max == 0u)
	{
		return 0.0;
	}
	else
	{
		return static_cast<double>(max - min) / static_cast<double>(max);
	}
}

double CPP::getColorValue(const unsigned int color)
{
	const auto r = (color >> 16u) & 0xFFu;
	const auto g = (color >> 8u) & 0xFFu;
	const auto b = color & 0xFFu;
	
	return static_cast<double>(std::max({r, g, b})) / 255.0;
}

unsigned int CPP::getRed(const unsigned int color)
{
	return color >> 16u & 0xFFu;
}

unsigned int CPP::getGreen(const unsigned int color)
{
	return color >> 8u & 0xFFu;
}

unsigned int CPP::getBlue(const unsigned int color)
{
	return color & 0xFFu;
}

std::unique_ptr<CPP_BitmapDataIF> CPP::getBitmapData(const std::string& filename) const
{
	return bitmapDataFactory ? bitmapDataFactory->getBitmapData(filename) : nullptr;
}

std::unique_ptr<CPP_BitmapDataIF> CPP::getBitmapData(const int width, const int height, const bool transparent, const unsigned int fillColor) const
{
	return bitmapDataFactory ? bitmapDataFactory->getBitmapData(width, height, transparent, fillColor) : nullptr;
}

bool CPP::check(const CPP_Key key) const
{
	return input.check(key);
}

bool CPP::pressed(const CPP_Key key) const
{
	return input.pressed(key);
}

bool CPP::released(const CPP_Key key) const
{
	return input.released(key);
}

double CPP::getPan(const std::experimental::optional<CPP_SfxType>& type) const
{
	return soundManager.getPan(type);
}

double CPP::getVolume(const std::experimental::optional<CPP_SfxType>& type) const
{
	return soundManager.getVolume(type);
}

void CPP::setPan(const std::experimental::optional<CPP_SfxType>& type, const double pan)
{
	soundManager.setPan(type, pan);
}

void CPP::setVolume(const std::experimental::optional<CPP_SfxType>& type, const double volume)
{
	soundManager.setVolume(type, volume);
}

void CPP::resetPan(const std::experimental::optional<CPP_SfxType>& type)
{
	soundManager.resetPan(type);
}

void CPP::resetVolume(const std::experimental::optional<CPP_SfxType>& type)
{
	soundManager.resetVolume(type);
}

std::chrono::steady_clock::time_point CPP::getTimer()
{
	return std::chrono::steady_clock::now();
}

std::vector<int> CPP::frames(int from, const int to, int skip)
{
	std::vector<decltype(from)> a;
	++skip;
	if (from < to)
	{
		while (from <= to)
		{
			a.emplace_back(from);
			from += skip;
		}
	}
	else
	{
		while (from >= to)
		{
			a.emplace_back(from);
			from -= skip;
		}
	}
	return a;
}
