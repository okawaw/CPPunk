//
//  CPP_SDL_BitmapData.h
//  Test
//
//  Created by Wade Okawa-Scannell on 9/2/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SDL_BitmapData_h
#define CPP_SDL_BitmapData_h

#include "CPP_BitmapDataIF.h"

#include <memory>
#include <string>

class CPP_Rectangle;

class SDL_Surface;
class SDL_Texture;
class SDL_Renderer;

class CPP_SDL_BitmapData : public CPP_BitmapDataIF
{
public:
	CPP_SDL_BitmapData(const std::string& filename, SDL_Renderer* renderer=nullptr, bool transparent=true);
	CPP_SDL_BitmapData(int width, int height, SDL_Renderer* renderer=nullptr, bool transparent=true, unsigned int fillColor=0xFFFFFFFFu);
	~CPP_SDL_BitmapData() = default;
	// TODO: Make other constructors?
	
	virtual int getHeight() const override;
	virtual int getWidth() const override;
	
	virtual CPP_Rectangle getRect() const override;
	
	virtual bool isTransparent() const override;
	
	virtual void render(const CPP_Point& destPoint, const std::experimental::optional<CPP_Rectangle>& clipRect=std::experimental::nullopt) const override;
	
	virtual void lock() override;
	virtual void unlock() override;
	
private:
	SDL_Renderer* renderer; // TODO: Make this const.
	bool transparent;
	
	// TODO: Should include? Or is forward declaration enough?
	std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> surface;
	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture;
};

#endif /* CPP_SDL_BitmapData_h */
