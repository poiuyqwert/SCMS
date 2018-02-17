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
		: palette(nullptr)
		{ pixels.pixels = nullptr; pixels.size = {0,0}; }
	BMP(const char *filename)
		{ this->open_file(filename); }
	BMP(const u8 *buffer, int length)
		{ this->open_data(buffer, length); }
	BMP(Pixels pixels, Palette *palette)
		{ this->set_pixels(pixels); this->set_palette(palette); }
	
	static Pixels rle8_decompress(const u8 *cmd, int length, Size<u32> size);
	static u8* rle8_compress(Pixels pixels, int &length);

	void open_file(const char *filename);
	void open_data(const u8 *buffer, int length);
	void save_file(const char *filename, BMP_COMPRESSION::Enum compression = BMP_COMPRESSION::NONE);
	u8* save_data(int &length, BMP_COMPRESSION::Enum compression = BMP_COMPRESSION::NONE);

	Size<u32> get_size()
		{ return this->pixels.size; }
	Pixels get_pixels()
		{ return pixels; }
	void set_pixels(Pixels pixels)
		{ this->pixels = pixels; }
	Palette* get_palette()
		{ return this->palette; }
	void set_palette(Palette *palette)
		{ this->palette = palette; }
};