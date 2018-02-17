//
//  Images.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-01.
//
//

#include "Images.h"

#include <string>

using namespace std;

Pixels::Pixels(Size<u32> size, u8 pixel)
	: size(size)
{
	this->pixels = new u8[size.width*size.height];
	memset(pixels, pixel, size.width*size.height);
}

void Pixels::paste(Pixels other, Point<s32> offset) {
	Rect<s32,u32> canvas = {{0,0}, size};
	Rect<s32,u32> to = {offset, other.size};
	Rect<s32,u32> drawTo = canvas.overlap(to);
	if (!drawTo.isEmpty()) {
		Point<s32> drawFrom = drawTo.origin - offset;
		for (s32 y = 0; y < drawTo.size.height; y++) {
			memcpy(pixels+(drawTo.origin.y+y)*size.width+drawTo.origin.x, other.pixels+(drawFrom.y+y)*other.size.width+drawFrom.x, drawTo.size.width);
		}
	}
}
