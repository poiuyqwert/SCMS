//
//  CHKSectionTILE.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionTILE.h"

#include "CHK.h"
#include "CHKSectionDIM.h"

#include <string>
#include <algorithm>

const CHKRequirements CHKSectionTILE::Requirements = {CHKVer::None, CHKGameMode::None};
void CHKSectionTILE::load_data(const u8 *data, u32 size) {
	CHKSectionDIM *dims = this->chk->get_section<CHKSectionDIM>();
	u32 mapSize = dims->get_width() * dims->get_height();
	this->map = new CHKTile[mapSize];
	memcpy(this->map, data, sizeof(CHKTile) * std::min(mapSize,size));
	if (size < mapSize) {
		memset(this->map+size, 0, mapSize-size);
	}
}
u8* CHKSectionTILE::save_data(u32 &size) {
	CHKSectionDIM *dims = chk->get_section<CHKSectionDIM>();
	size = sizeof(u16) * (dims->get_width() * dims->get_height());
	u8 *buffer = new u8[size];
	memcpy(buffer, this->map, size);
	return buffer;
}
CHKTile CHKSectionTILE::get_tile(int x, int y) {
	CHKSectionDIM *dims = chk->get_section<CHKSectionDIM>();
	return *(this->map + y * dims->get_width() + x);
}
