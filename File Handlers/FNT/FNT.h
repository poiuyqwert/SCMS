/*
 *  FNT.h
 *  SCMS
 *
 *  Created by poiuy_qwert on 14/07/09.
 *
 */

#pragma once

#include "Exception.h"
#include "Types.h"
#include "Pack.h"
#include "Palette.h"
#include "BMP.h"

#include <vector>
#include <cstring>

#pragma pack(push, 1)
struct FNT_CHR_HEADER {
	u8 width;
	u8 height;
	u8 xOffset;
	u8 yOffset;
};
#pragma pack(pop)

class FNT {
	u8 lowIndex, width, height;
	vector<u8 *> letters;
public:
	FNT()
		: lowIndex(0),width(0),height(0) {}
	FNT(vector<u8 *> letters, u8 width, u8 height, u8 low = 32);
	FNT(const char *filename)
		{ this->open_file(filename); }
	FNT(u8 *buffer, int size)
		{ this->open_data(buffer, size); }
	~FNT()
		{ this->close(); }

	static FNT_CHR_HEADER letter_dims(Pixels letter);

	void open_file(const char *filename);
	void open_data(const u8 *buffer, int size);
	void export_file(const char *filename, Palette *palette);
	BMP* export_data(Palette *palette);
	void save_file(const char *filename);
	u8* save_data(int &size);

	u8 get_low()
		{ return this->lowIndex; }
	u8 get_width()
		{ return this->width; }
	u8 get_height()
		{ return this->height; }
	u8 get_chars()
		{ return this->letters.size(); }
	Pixels get_letter(u8 n);
	void set_letter(u8 n, Pixels pixels);
	
	void close();
};