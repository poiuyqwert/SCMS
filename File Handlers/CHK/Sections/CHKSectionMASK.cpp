//
//  CHKSectionMASK.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionMASK.h"

#include "CHK.h"
#include "CHKSectionDIM.h"

#include <string>
#include <algorithm>

const CHKRequirements CHKSectionMASK::Requirements = {CHKVer::All, CHKGameMode::UseMapSettings};
void CHKSectionMASK::load_data(const u8 *data, u32 size) {
	CHKSectionDIM *dims = this->chk->get_section<CHKSectionDIM>();
	u32 mapSize = dims->get_width() * dims->get_height();
	this->map = new u8[mapSize];
	memcpy(this->map, data, sizeof(u8) * std::min(mapSize,size));
	if (size < mapSize) {
		memset(this->map+size, 0xFF, mapSize-size);
	}
}
u8* CHKSectionMASK::save_data(u32 &size) {
	CHKSectionDIM *dims = chk->get_section<CHKSectionDIM>();
	size = sizeof(u8) * (dims->get_width() * dims->get_height());
	u8 *buffer = new u8[size];
	memcpy(buffer, this->map, size);
	return buffer;
}
