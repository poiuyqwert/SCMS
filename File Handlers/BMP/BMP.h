/*
 *  BMP.h
 *  SCMS
 *
 *  Created by poiuy_qwert on 21/07/09.
 *
 */

#pragma once

#include "Palette.h"
#include "Exception.h"
#include "Pack.h"
#include "Logging.h"
#include "Images.h"

#include <list>
#include <fstream>
#include <cstring>

using namespace std;

namespace BMP_COMPRESSION {
	enum Enum {
		NONE,
		RLE8,
		/*RLE4,
		BITFIELDS,
		JPEG,
		PNG*/
	};
}

class BMP {
	Palette *palette;
	Pixels pixels;
public:
	BMP()
		: palette(NULL)
		{ pixels.pixels = NULL; pixels.width = 0; pixels.height = 0; }
	BMP(const char *filename)
		{ this->open_file(filename); }
	BMP(const u8 *buffer, int size)
		{ this->open_data(buffer, size); }
	BMP(Pixels pixels, Palette *palette)
		{ this->set_pixels(pixels); this->set_palette(palette); }
	
	static Pixels rle8_decompress(const u8 *cmd, int size, int width, int height);
	static u8* rle8_compress(Pixels pixels, int &size);

	void open_file(const char *filename);
	void open_data(const u8 *buffer, int size);
	void save_file(const char *filename, BMP_COMPRESSION::Enum compression = BMP_COMPRESSION::NONE);
	u8* save_data(int &size, BMP_COMPRESSION::Enum compression = BMP_COMPRESSION::NONE);

	int get_width()
		{ return this->pixels.width; }
	int get_height()
		{ return this->pixels.height; }
	Pixels get_pixels()
		{ return pixels; }
	void set_pixels(Pixels pixels)
		{ this->pixels = pixels; }
	Palette* get_palette()
		{ return this->palette; }
	void set_palette(Palette *palette)
		{ this->palette = palette; }
};