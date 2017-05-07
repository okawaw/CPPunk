//
//  CPP.h
//  Test
//
//  Created by Wade Okawa-Scannell on 9/20/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_h
#define CPP_h

#include "CPP_BitmapDataFactoryIF.h"
#include "CPP_Input.h"
#include "CPP_Point.h"
#include "CPP_Rectangle.h"
#include "CPP_SoundManager.h"

#include <chrono>
#include <cmath>
#include <memory>
#include <experimental/optional>
#include <random>
#include <string>
#include <vector>

class CPP_Engine;
class CPP_World;
class CPP_BitmapDataIF;
class CPP_Sfx;

enum class CPP_Key;
enum class CPP_SfxType;

class CPP
{
	friend CPP_Engine;
	friend CPP_Sfx; // TODO: Remove this when soundManager is a reference, since the CPP_Sfx can call the public reference.
	
	// TODO: Reorganize this.
private:
	const std::string VERSION;
	std::string title;
	unsigned int width;
	unsigned int height;
	double halfWidth;
	double halfHeight;
	bool fixed;
	bool timeInFrames;
	std::chrono::steady_clock::duration frameTime;
	// TODO: Maybe remove frameRate and favor using frameTime.
	double frameRate;
	// TODO: Maybe remove assignedFrameRate and favor using assignedFrameTime.
	std::chrono::steady_clock::duration assignedFrameTime;
	double assignedFrameRate;
	std::chrono::steady_clock::duration elapsed;
	double rate;
	CPP_Rectangle bounds;
	CPP_Point camera;
	bool focused;
	CPP_Engine* engine;
	
public:
	CPP();
	// TODO: Other constructors?
	
	// The CPPunk major version.
	std::string getVersion() const;
	
	// Title of the game.
	std::string getTitle() const;
	
	// Width of the game.
	unsigned int getWidth() const;
	void setWidth(unsigned int value);
	
	// Height of the game.
	unsigned int getHeight() const;
	void setHeight(unsigned int value);
	
	// Half width of the game.
	double getHalfWidth() const;
	
	// Half height of the game.
	double getHalfHeight() const;
	
	// If the game is running at a fixed framerate.
	bool isFixed() const;
	// TODO: Set fixed?
	
	// If times should be given in frames (as opposed to seconds).
	// Default is true in fixed timestep mode and false in variable timestep mode.
	bool isTimeInFrames() const;
	// TODO: Set timeInFrames?
	
	// The framerate assigned to the stage.
	double getFrameRate() const;
	// TODO: Set frameRate?
	
	// The framerate assigned to the stage.
	double getAssignedFrameRate() const;
	// TODO: Set assignedFrameRate?
	
	// Time elapsed since the last frame (in seconds).
	double getElapsed() const;
	// TODO: Is this meant to be read-only?
	
	// Timescale applied to CPP::elapsed.
	double getRate() const;
	// TODO: Set rate?
	
	// A rectangle representing the size of the screen.
	CPP_Rectangle getBounds() const;
	void setBounds(const CPP_Rectangle& value);
	
	// If the game currently has input focus or not. Note: may not be correct initially.
	bool isFocused() const;
	// TODO: Is this meant to be read-only?
	
	void resize(int width, int height);
	
	std::shared_ptr<CPP_World> getWorld() const;
	void setWorld(std::shared_ptr<CPP_World> value);
	
	// Point used to determine drawing offset in the render loop.
	CPP_Point getCamera() const;
	void setCamera(const CPP_Point& value);
	void resetCamera();
	
	double getVolume() const;
	void setVolume(double value);
	
	double getPan() const;
	void setPan(double value);
	
	static double approach(double value, double target, double amount);
	
	static double lerp(double a, double b, double t=1.0);
	
	static unsigned int colorLerp(unsigned int fromColor, unsigned int toColor, double t=1.0);
	
	template <typename T>
	static void stepTowards(T& object, double x, double y, double distance=1.0);
	
	template <typename T, typename U>
	static void anchorTo(T& object, const U& anchor, double distance=0.0);
	
	static double radiansToDegrees(double value);
	static double degreesToRadians(double value);
	
	static double angle(double x1, double y1, double x2, double y2);
	
	template <typename T>
	static void angleXY(T& object, double angle, double length=1.0, double x=0.0, double y=0.0);
	
	template <typename T, typename U>
	static void rotateAround(T& object, const U& anchor, double angle=0.0, bool relative=true);
	
	static double angleDiff(double a, double b);
	
	static double distance(double x1, double y1, double x2=0.0, double y2=0.0);
	
	static double distanceRects(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);
	
	static double distanceRectPoint(double pX, double pY, double rX, double rY, double rW, double rH);
	
	static double clamp(double value, double min, double max);
	
	template <typename T>
	static void clampInRect(T& object, double x, double y, double width, double height, double padding=0.0);
	
	static double scale(double value, double min, double max, double min2, double max2);
	
	static double scaleClamp(double value, double min, double max, double min2, double max2);
	
	std::minstd_rand0::result_type getRandomSeed() const;
	void setRandomSeed(std::minstd_rand0::result_type value);
	void randomizeSeed();
	std::uniform_int_distribution<>::result_type getRandom();
	unsigned int rand(unsigned int amount);
	
	static unsigned int getColorRGB(unsigned int r, unsigned int g, unsigned int b);
	
	static unsigned int getColorHSV(double h, double s, double v);
	
	static double getColorHue(unsigned int color);
	
	static double getColorSaturation(unsigned int color);
	
	static double getColorValue(unsigned int color);
	
	static unsigned int getRed(unsigned int color);
	
	static unsigned int getGreen(unsigned int color);
	
	static unsigned int getBlue(unsigned int color);
	
	std::unique_ptr<CPP_BitmapDataIF> getBitmapData(const std::string& filename) const;
	std::unique_ptr<CPP_BitmapDataIF> getBitmapData(int width, int height, bool transparent=true, unsigned int fillColor=0xFFFFFFFFu) const;
	
	bool check(CPP_Key key) const;
	bool pressed(CPP_Key key) const;
	bool released(CPP_Key key) const;
	
	// TODO: Remove these when soundManager is a reference.
	double getPan(const std::experimental::optional<CPP_SfxType>& type) const;
	double getVolume(const std::experimental::optional<CPP_SfxType>& type) const;
	void setPan(const std::experimental::optional<CPP_SfxType>& type, double pan);
	void setVolume(const std::experimental::optional<CPP_SfxType>& type, double volume);
	void resetPan(const std::experimental::optional<CPP_SfxType>& type);
	void resetVolume(const std::experimental::optional<CPP_SfxType>& type);
	
	
	// TODO: timeFlag()
	static std::chrono::steady_clock::time_point getTimer();
	
	// TODO: Console stuff.
	
	// TODO: XML stuff.
	
	// TODO: Tween stuff.
	
	static std::vector<int> frames(int from, int to, int skip=0);
	
	// TODO: getEngine(); ?
	// TODO: setEngine(); ?
	
	std::chrono::steady_clock::time_point getUpdateTime();
	
private:
	// TODO: Make these objects that have impl pointers set via functions.
	std::unique_ptr<CPP_BitmapDataFactoryIF> bitmapDataFactory;
	CPP_Input input;
	CPP_SoundManager soundManager;
	
	std::shared_ptr<CPP_World> world;
	std::shared_ptr<CPP_World> gotoWorld;
	
	// TODO: Console.
	
	// TODO: Time information, some should be public or friend acquired though...
	std::chrono::steady_clock::time_point _time;
public:
	std::chrono::steady_clock::duration updateTime;
	std::chrono::steady_clock::duration renderTime;
	std::chrono::steady_clock::duration gameTime;
	std::chrono::steady_clock::duration flashTime; // TODO: See if I actually need this...
private:
	
	// TODO: Volume control.
	double _volume;
	double _pan;
	
	// Pseudo-random number generation.
	std::random_device rd;
	std::minstd_rand0 rnEngine;
	std::uniform_real_distribution<> dist;
	std::minstd_rand0::result_type _getSeed;
};

template <typename T>
void CPP::stepTowards(T &object, const double x, const double y, double distance)
{
	CPP_Point point{x - static_cast<double>(object.x), y - static_cast<double>(object.y)};
	if (point.getLength() <= distance)
	{
		object.x = static_cast<decltype(object.x)>(x);
		object.y = static_cast<decltype(object.y)>(y);
		return;
	}
	point.normalize(distance);
	object.x += static_cast<decltype(object.x)>(point.x);
	object.y += static_cast<decltype(object.y)>(point.y);
}

template <typename T, typename U>
void CPP::anchorTo(T& object, const U& anchor, const double distance)
{
	CPP_Point point{static_cast<double>(object.x) - static_cast<double>(anchor.x), static_cast<double>(object.y) - static_cast<double>(anchor.y)};
	if (point.getLength() > distance)
	{
		point.normalize(distance);
	}
	object.x = static_cast<decltype(object.x)>(static_cast<double>(anchor.x) + point.x);
	object.y = static_cast<decltype(object.y)>(static_cast<double>(anchor.y) + point.x);
}

template <typename T>
void CPP::angleXY(T &object, const double angle, const double length, const double x, const double y)
{
	const auto a = degreesToRadians(angle);
	object.x = static_cast<decltype(object.x)>(std::cos(a) * length + x);
	object.y = static_cast<decltype(object.y)>(std::sin(a) * length + y);
}

template <typename T, typename U>
void CPP::rotateAround(T& object, const U& anchor, const double _angle, const bool relative)
{
	const auto a = _angle + ((relative) ? angle(static_cast<double>(anchor.x), static_cast<double>(anchor.y), static_cast<double>(object.x), static_cast<double>(object.y)) : 0.0);
	angleXY(object, a, distance(static_cast<double>(anchor.x), static_cast<double>(anchor.y), static_cast<double>(object.x), static_cast<double>(object.y)), static_cast<double>(anchor.x), static_cast<double>(anchor.y));
}

template <typename T>
void CPP::clampInRect(T& object, const double x, const double y, const double width, const double height, const double padding)
{
	object.x = static_cast<decltype(object.x)>(clamp(static_cast<double>(object.x), x + padding, x + width - padding));
	object.y = static_cast<decltype(object.y)>(clamp(static_cast<double>(object.y), y + padding, y + height - padding));
}



#endif /* CPP_h */
