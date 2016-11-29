//
//  CHKSectionUPUS.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionUPUS.h"

#include <string>

const CHKRequirements CHKSectionUPUS::Requirements = {CHKVer::None, CHKGameMode::None};
CHKSectionUPUS::CHKSectionUPUS(CHK *chk)
	: CHKSection(chk)
{
	memset(&this->propertiesUsed, 0, sizeof(CHKSectionUPUS::propertiesUsed));
}
void CHKSectionUPUS::load_data(const u8 *data, u32 size) {
	memcpy(&this->propertiesUsed, data, sizeof(CHKSectionUPUS::propertiesUsed));
}
u8* CHKSectionUPUS::save_data(u32 &size) {
	size = sizeof(CHKSectionUPUS::propertiesUsed);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->propertiesUsed, size);
	return buffer;
}
