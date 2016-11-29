//
//  CHKSectionSWNM.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionSWNM.h"

#include <string>

const CHKRequirements CHKSectionSWNM::Requirements = {CHKVer::None, CHKGameMode::None};
CHKSectionSWNM::CHKSectionSWNM(CHK *chk)
	: CHKSection(chk)
{
	memset(this->stringID, 0, sizeof(CHKSectionSWNM::stringID));
}
void CHKSectionSWNM::load_data(const u8 *data, u32 size) {
	memcpy(this->stringID, data, sizeof(CHKSectionSWNM::stringID));
}
u8* CHKSectionSWNM::save_data(u32 &size) {
	size = sizeof(CHKSectionSWNM::stringID);
	u8 *buffer = new u8[size];
	memcpy(buffer, this->stringID, size);
	return buffer;
}
