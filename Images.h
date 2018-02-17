//
//  Images.h
//  SCMS
//
//  Created by Zach Zahos on 2015-12-31.
//
//

#pragma once

#include "Types.h"
#include "Geometry.h"


struct Pixels {
	u8 *pixels;
	Size<u32> size;
	
	Pixels()
		: pixels(nullptr),size({0,0}) {}
	Pixels(Size<u32> size, u8 pixel = 0);
	Pixels(u8 *pixels, Size<u32> size)
		: pixels(pixels),size(size) {}
	
	void paste(Pixels pixels, Point<s32> offset);
	void paste(Pixels pixels)
		{ this->paste(pixels, {0,0}); }
	
	u8 get(Point<u32> point)
		{ return this->pixels[point.y * size.width + point.x]; }
	void set(Point<u32> point, u8 pixel)
		{ this->pixels[point.y * size.width + point.x] = pixel; }
};
