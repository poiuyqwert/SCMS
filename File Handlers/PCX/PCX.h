/*
 *  PCX.h
 *  SCMS
 *
 *  Created by poiuy_qwert on 01/03/13.
 *
 */

#pragma once

#include "Exception.h"
#include "Pack.h"
#include "Images.h"

class Palette;

class PCX {
	Palette *palette;
	Pixels pixels;
	bool specialPalette;
public:
	PCX()
		: palette(NULL) {}
	PCX(const char *filename, bool specialPalette = false)
		{ this->open_file(filename, specialPalette); }
	PCX(u8 *buffer, int size, bool specialPalette = false)
		{ this->open_data(buffer, size, specialPalette); }
	PCX(Pixels pixels, Palette *palette)
		{ this->set_pixels(pixels); this->set_palette(palette); }

	void open_file(const char *filename, bool specialPalette = false);
	void open_data(const u8 *buffer, int size, bool specialPalette = false);
	void save_file(const char *filename);
	u8* save_data(int &size);
	
	Size<u32> get_size()
		{ return this->pixels.size; }
	Pixels get_pixels()
		{ return this->pixels; }
	void set_pixels(Pixels pixels)
		{ this->pixels = pixels; }
	Palette* get_palette()
		{ return this->palette; }
	void set_palette(Palette *palette)
		{ this->palette = palette; }

	Palette *get_palette(unsigned int specialPaletteRow);
};