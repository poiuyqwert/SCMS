//
//  CHKSectionDD2.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionDD2.h"

const CHKRequirements CHKSectionDD2::Requirements = {CHKVer::None, CHKGameMode::None};
void CHKSectionDD2::load_data(const u8 *data, u32 size) {
	int doodads = size / sizeof(CHKDoodadUnit);
	this->doodads.assign((CHKDoodadUnit *)data, (CHKDoodadUnit *)data + doodads);
}
u8* CHKSectionDD2::save_data(u32 &size) {
	size = sizeof(CHKDoodadUnit) * this->doodads.size();
	u8 *buffer = new u8[size];
	memcpy(buffer, this->doodads.data(), size);
	return buffer;
}
