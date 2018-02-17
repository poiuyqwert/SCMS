//
//  GRP.h
//  SCMS
//
//  Created by Zach Zahos on 2015-12-31.
//
//

#pragma once

#include "Exception.h"
#include "Types.h"
#include "BroodWar.h"
#include "PCX.h"

#include <vector>

class Palette;
struct Pixels;

#pragma pack(push, 1)
struct GRP_FRAME_HEADER {
	Rect<u8,u8> rect;
	u32 framedataOffset;
};
#pragma pack(pop)

namespace RLE_TYPE {
	enum ENUM : u8 {
		RLE_NORMAL = 0,
		RLE_CLOAK = 5,
		RLE_CLOAKED = 6,
		RLE_DECLOAK = 7,
		RLE_EFFECT = 9,
		RLE_SHADOW = 10,
		RLE_HPFLOATDRAW = 11,
		RLE_WARP_IN = 12,
		RLE_OUTLINE = 13,
		RLE_PLAYER_SIDE = 14,
		RLE_SHIFT = 16,
		RLE_FIRE = 17
	};
}

typedef u8 (*RLE_FUNC)(u8 draw, Point<u32> point, Pixels pixels, void *context);

u8 RLE_NONE_FUNC(u8 draw, Point<u32> point, Pixels pixels, __unused void *context);

struct RLE_NORMAL_CONTEXT {
	SC::Player::ENUM player;
	Pixels tunit;
};
u8 RLE_NORMAL_FUNC(u8 draw, Point<u32> point, Pixels pixels, void *playerContext);



class GRP {
	u8 *grp;
	long long length;
	bool compressed;
public:
	GRP(const char *filename, bool compressed = true);
	GRP(const u8 *buffer, long long length, bool compressed = true);
	
	void save_file(const char *filename);
	u8* save_data(int &size);
	
	u16 get_frames();
	Size<u16> get_size();
	bool get_compressed()
		{ return this->compressed; }
	
	void draw_frame(u16 f, Point<s32> point, Pixels pixels, RLE_FUNC rleFunction = RLE_NORMAL_FUNC, void *rleContext = nullptr);
};
