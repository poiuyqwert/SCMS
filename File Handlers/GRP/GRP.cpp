//
//  GRP.cpp
//  SCMS
//
//  Created by Zach Zahos on 2015-12-31.
//
//

#include "GRP.h"
#include "Pack.h"
#include "Images.h"
#include <math.h>


u8 RLE_NONE_FUNC(u8 draw, Point<u32> point, Pixels pixels, __unused void *context) {
	return draw;
}

u8 RLE_NORMAL_FUNC(u8 draw, Point<u32> point, Pixels pixels, void *playerContext) {
	if (playerContext != nullptr && 8 <= draw && draw <= 15) {
		RLE_NORMAL_CONTEXT *context = (RLE_NORMAL_CONTEXT *)playerContext;
		u8 player = min((u8)context->player, (u8)floor(context->tunit.size.width / 8.0 - 1));
		return context->tunit.get({(u32)player*8 + draw-8, 0});
	}
	return draw;
}

#pragma pack(push, 1)
struct GRP_HEADER {
	u16 frames;
	Size<u16> size;
};
#pragma pack(pop)


GRP::GRP(const char *filename, bool compressed)
	: compressed(compressed)
{
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Open", "Could not open file '%s'", filename);
		throw err;
	}
	file.seekg(0, ios::end);
	this->length = file.tellg();
	file.seekg(0);
	this->grp = new u8[this->length];
	file.read((char *)this->grp, this->length);
	file.close();
}

GRP::GRP(const u8 *buffer, long long length, bool compressed)
	: length(length), compressed(compressed)
{
	this->grp = new u8[this->length];
	memcpy(this->grp, buffer, this->length);
}

u16 GRP::get_frames() {
	GRP_HEADER *header = (GRP_HEADER *)grp;
	return header->frames;
}
Size<u16> GRP::get_size() {
	GRP_HEADER *header = (GRP_HEADER *)grp;
	return header->size;
}

static const u8 TRANSPARENT = 0x80;
static const u8 REPEATING = 0x40;

void GRP::draw_frame(u16 f, Point<s32> point, Pixels pixels, RLE_FUNC rleFunction, void *rleContext) {
	if (f < 0 || f >= this->get_frames()) {
		SCMSError err("Internal", "Frame index out of range (got %u, expected number in range 0-%u)", f, this->get_frames());
		throw err;
	}
	
	GRP_FRAME_HEADER *header = (GRP_FRAME_HEADER *)(grp + sizeof(GRP_HEADER) + sizeof(GRP_FRAME_HEADER) * f);
	point.x += header->rect.origin.x;
	point.y += header->rect.origin.y;
	if (point.x+header->rect.size.width < 0 || point.x > pixels.size.width || point.y+header->rect.size.height < 0 || point.y > pixels.size.height) {
		return;
	}
	
	s32 startY = 0;
	if (point.y < 0) {
		startY = -point.y;
		point.y = 0;
	}
	u32 endX = point.x + min((u32)header->rect.size.width, pixels.size.width - point.x);
	u32 height = min((u32)header->rect.size.height, pixels.size.height - point.y);
	
	u16 *lineOffsets = (u16 *)(grp + header->framedataOffset);
	for (u32 line = startY, y = point.y; line < height; line++, y++) {
		u8 *lineData = (u8 *)lineOffsets + lineOffsets[line];
		// TODO: Uncompressed
		for (s32 x = point.x, lineOffset = 0; x < endX;) {
			if (lineData[lineOffset] & TRANSPARENT) {
				x += lineData[lineOffset++] & (TRANSPARENT-1);
			} else if (lineData[lineOffset] & REPEATING) {
				u8 repeat = lineData[lineOffset++] & (REPEATING-1);
				repeat = min((u32)repeat, pixels.size.width-x);
				u8 index = lineData[lineOffset++];
				while (repeat--) {
					if (x >= 0) {
						pixels.set({(u32)x,y}, rleFunction(index, {(u32)x,y}, pixels, rleContext));
					}
					x++;
				}
			} else {
				u8 length = lineData[lineOffset++];
				length = min((u32)length, pixels.size.width-x);
				while (length--) {
					if (x >= 0) {
						pixels.set({(u32)x,y}, rleFunction(lineData[lineOffset], {(u32)x,y}, pixels, rleContext));
					}
					lineOffset++;
					x++;
				}
			}
		}
	}
}
