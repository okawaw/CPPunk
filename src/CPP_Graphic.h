//
//  CPP_Graphic.h
//  CPPunk
//
//  Created by Wade Okawa-Scannell on 8/28/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_Graphic_h
#define CPP_Graphic_h

#include <functional>

class CPP_Point;

// Base class for all graphical types that can be drawn by CPPEntity.
class CPP_Graphic
{
public:
	CPP_Graphic();
	virtual ~CPP_Graphic() = default;
	CPP_Graphic(const CPP_Graphic& other) = default;
	CPP_Graphic(CPP_Graphic&& other) = default;
	CPP_Graphic& operator=(const CPP_Graphic& other) = default;
	CPP_Graphic& operator=(CPP_Graphic&& other) = default;
	
	// If the graphic should update.
	bool isActive() const;
	void setActive(bool value);
	bool active;
	
	// If the graphic should render.
	bool isVisible() const;
	void setVisible(bool value);
	bool visible;
	
	// X offset.
	double x;
	
	// Y offset.
	double y;
	
	// X scrollfactor, effects how much the camera offsets the drawn graphic.
	// Can be used for parallax effect, eg. Set to 0.0 to follow the camera,
	// 0.5 to move at half-speed of the camera, or 1.0 (default) to stay still.
	double scrollX;
	
	// Y scrollfactor, effects how much the camera offsets the drawn graphic.
	// Can be used for parallax effect, eg. Set to 0.0 to follow the camera,
	// 0.5 to move at half-speed of the camera, or 1.0 (default) to stay still.
	double scrollY;
	
	// If the graphic should render at its position relative to its parent CPPEntity's position.
	bool isRelative() const;
	void setRelative(bool value);
	bool relative;
	
	// Updates the graphic.
	virtual void update();
	
	// Renders the graphic to the screen buffer.
	virtual void render(const CPP_Point& point, const CPP_Point& camera) const;
	
	std::function<void()> assign;
};

#endif /* CPP_Graphic_h */
