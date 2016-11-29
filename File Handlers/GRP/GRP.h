//
//  GRP.h
//  SCMS
//
//  Created by Zach Zahos on 2015-12-31.
//
//

#pragma once

#include "Exception.h"
#include "Pack.h"
#include "Images.h"

#include <vector>

class Palette;

#pragma pack(push, 1)
struct GRP_FRAME_HEADER {
	u8 xoffset;
	u8 yoffset;
	u8 linewidth;
	u8 lines;
	u32 framedata;
};
#pragma pack(pop)

class GRP {
	vector<u8 *> frames;
	u8 width, height;
	bool compressed;
	u8 transindex;
public:
	GRP()
		: width(0),height(0),compressed(true),transindex(0) {}
	GRP(const char *filename, bool compressed = true)
		{ this->open_file(filename, compressed); }
	GRP(const u8 *buffer, int size, bool compressed = true)
		{ this->open_data(buffer, size, compressed); }
	
	static Pixels grp_decompress(const u8 *cmd, int size, int width, int height, GRP_FRAME_HEADER header, u8 transindex = 0);
	static u8* grp_compress(Pixels pixels, int &size, GRP_FRAME_HEADER *header, u8 transindex = 0);

	void open_file(const char *filename, bool compressed = true, u8 transindex = 0);
	void open_data(const u8 *buffer, int size, bool compressed = true, u8 transindex = 0);
	void save_file(const char *filename, bool compressed = true, u8 transindex = 0);
	u8* save_data(int &size, bool compressed = true, u8 transindex = 0);
	
	u8 get_width()
		{ return this->width; }
	u8 get_height()
		{ return this->height; }
	bool get_compressed()
		{ return this->compressed; }
	u8 get_transindex()
		{ return this->transindex; }
	int get_frames()
		{ return this->frames.size(); }
	Pixels get_frame(int n);
	void set_frame(int n, Pixels pixels);
};
