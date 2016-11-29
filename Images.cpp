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

Pixels::Pixels(int width, int height, u8 pixel) {
	this->pixels = new u8[width * height];
	memset(pixels, pixel, width*height);
	this->width = width;
	this->height = height;
}

void Pixels::paste(Pixels pixels, int xOffset, int yOffset) {
	int copyWidth = min(this->width - xOffset, pixels.width);
	int copyHeight = min(this->height - yOffset, pixels.height);
	for (int y = 0; y < copyHeight; y++) {
		memcpy(this->pixels+(y+yOffset)*this->width+xOffset, pixels.pixels+y*pixels.width, copyWidth);
	}
}