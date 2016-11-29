/*
 *  Palettes.h
 *  SCMS
 *
 *  Created by poiuy_qwert on 17/07/09.
 *
 */

#pragma once

#include "Exception.h"
#include "Types.h"
#include "Pack.h"

#include <list>
#include <fstream>
#include <cstring>

using namespace std;

namespace PALETTE_TYPE {
	enum Enum {
		PCX = 0,
		RIFF,
		JASC,
		WPE,
		SCPAL
	};
}

struct RGB {
	u8 r;
	u8 g;
	u8 b;
};

class Palette {
	RGB *colors;
	PALETTE_TYPE::Enum type;
public:
	Palette()
		: colors(NULL),type(PALETTE_TYPE::SCPAL) {}
	Palette(RGB *colors, int count, PALETTE_TYPE::Enum type = PALETTE_TYPE::SCPAL);
	Palette(const char *filename)
		: colors(NULL)
		{ this->open_file(filename); }
	Palette(const u8 *buffer, int size)
		: colors(NULL)
		{ this->open_data(buffer, size); }
	~Palette()
		{ this->close(); }

	static char* rgb_to_html(RGB rgb);
	static RGB* html_to_rgb(char* html);

	void open_file(const char *filename);
	void open_data(const u8 *buffer, int size);
	void open_riff_pal(const u8 *buffer, int size);
	void open_jasc_pal(const u8 *buffer, int size);
	void open_zsoft_pcx(const u8 *buffer, int size);
	void open_sc_wpe(const u8 *buffer, int size);
	void open_sc_pal(const u8 *buffer, int size);
	void save_file(const char *filename, PALETTE_TYPE::Enum type = PALETTE_TYPE::SCPAL);
	u8* save_data(int &size, PALETTE_TYPE::Enum type = PALETTE_TYPE::SCPAL);
	u8* save_riff_pal(int &size);
	u8* save_jasc_pal(int &size);
	u8* save_zsoft_pcx(int &size);
	u8* save_sc_wpe(int &size);
	u8* save_sc_pal(int &size);

	PALETTE_TYPE::Enum get_type()
		{ return this->type; }
	RGB get_color(u8 n);
	void set_color(u8 n, RGB color);
	void close();
};