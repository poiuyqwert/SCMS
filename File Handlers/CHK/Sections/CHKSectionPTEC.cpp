//
//  CHKSectionPTEC.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionPTEC.h"

#include <string>

const CHKRequirements CHKSectionPTEC::Requirements = {CHKVer::VanillaHybrid, CHKGameMode::UseMapSettings};
CHKSectionPTEC::CHKSectionPTEC(CHK *chk)
	: CHKSection(chk)
{
#warning COMPLEX DEFAULTS
}
void CHKSectionPTEC::load_data(const u8 *data, u32 size) {
	memcpy(&this->technology, data, sizeof(CHKSectionPTEC::technology));
}
u8* CHKSectionPTEC::save_data(u32 &size) {
	size = sizeof(CHKSectionPTEC::technology);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->technology, size);
	return buffer;
}
