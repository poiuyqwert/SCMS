//
//  CHKSectionMTXM.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionMTXM.h"

#include "CHK.h"
#include "CHKSectionDIM.h"

#include <string>
#include <algorithm>

const CHKRequirements CHKSectionMTXM::Requirements = {CHKVer::All, CHKGameMode::All};
void CHKSectionMTXM::load_data(const u8 *data, u32 size) {
	CHKSectionDIM *dims = this->chk->get_section<CHKSectionDIM>();
	u32 mapSize = dims->get_size().area();
	this->tiles = new CHKTile[mapSize];
	memcpy(this->tiles, data, sizeof(CHKTile) * std::min(mapSize,size));
	if (size < mapSize) {
		memset(this->tiles+size, 0, mapSize-size);
	}
}

u8* CHKSectionMTXM::save_data(u32 &size) {
	CHKSectionDIM *dims = chk->get_section<CHKSectionDIM>();
	size = sizeof(CHKTile) * dims->get_size().area();
	u8 *buffer = new u8[size];
	memcpy(buffer, this->tiles, size);
	return buffer;
}

CHKTile CHKSectionMTXM::get_tile(Point<u8> point) {
	CHKSectionDIM *dims = chk->get_section<CHKSectionDIM>();
	return *(this->tiles + point.y * dims->get_size().width + point.x);
}

void CHKSectionMTXM::set_tile(CHKTile tile, Point<u8> point) {
	CHKSectionDIM *dims = chk->get_section<CHKSectionDIM>();
	*(this->tiles + point.y * dims->get_size().width + point.x) = tile;
}
