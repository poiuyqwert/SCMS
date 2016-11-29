//
//  Images.h
//  SCMS
//
//  Created by Zach Zahos on 2015-12-31.
//
//

#pragma once

#include "Types.h"

struct Pixels {
	u8 *pixels;
	int width, height;
	
	Pixels()
		: pixels(nullptr),width(0),height(0) {}
	Pixels(int width, int height, u8 pixel = 0);
	Pixels(u8 *pixels, int width, int height)
		: pixels(pixels),width(width),height(height) {}
	
	void paste(Pixels pixels, int xOffset, int yOffset);
	void paste(Pixels pixels)
		{ this->paste(pixels, 0, 0); }
};
