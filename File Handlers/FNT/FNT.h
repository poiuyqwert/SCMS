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
	Size<u8> size;
	Point<u8> offset;
};
#pragma pack(pop)

class FNT {
	u8 lowIndex;
	Size<u8> size;
	vector<u8 *> letters;
public:
	FNT()
		: lowIndex(0),size({0,0}) {}
	FNT(vector<u8 *> letters, Size<u8> size, u8 low = 32);
	FNT(const char *filename)
		{ this->open_file(filename); }
	FNT(u8 *buffer, int length)
		{ this->open_data(buffer, length); }
	~FNT()
		{ this->close(); }

	static FNT_CHR_HEADER letter_dims(Pixels letter);

	void open_file(const char *filename);
	void open_data(const u8 *buffer, long long length);
	void export_file(const char *filename, Palette *palette);
	BMP* export_data(Palette *palette);
	void save_file(const char *filename);
	u8* save_data(int &length);

	u8 get_low()
		{ return this->lowIndex; }
	Size<u8> get_size()
		{ return this->size; }
	u8 get_chars()
		{ return this->letters.size(); }
	Pixels get_letter(u8 n);
	void set_letter(u8 n, Pixels pixels);
	
	void close();
};