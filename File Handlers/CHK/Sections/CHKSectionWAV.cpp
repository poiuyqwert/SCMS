//
//  CHKSectionWAV.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionWAV.h"

#include <string>

const CHKRequirements CHKSectionWAV::Requirements = {CHKVer::None, CHKGameMode::None};
CHKSectionWAV::CHKSectionWAV(CHK *chk)
	: CHKSection(chk)
{
	memset(this->stringID, 0, sizeof(CHKSectionWAV::stringID));
}
void CHKSectionWAV::load_data(const u8 *data, u32 size) {
	memcpy(this->stringID, data, sizeof(CHKSectionWAV::stringID));
}
u8* CHKSectionWAV::save_data(u32 &size) {
	size = sizeof(CHKSectionWAV::stringID);
	u8 *buffer = new u8[size];
	memcpy(buffer, this->stringID, size);
	return buffer;
}
