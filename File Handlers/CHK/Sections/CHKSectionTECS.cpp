//
//  CHKSectionTECS.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionTECS.h"

#include <string>

const CHKRequirements CHKSectionTECS::Requirements = {CHKVer::VanillaHybrid, CHKGameMode::UseMapSettings};
CHKSectionTECS::CHKSectionTECS(CHK *chk)
	: CHKSection(chk)
{
#warning COMPLEX DEFAULTS
}
void CHKSectionTECS::load_data(const u8 *data, u32 size) {
	memcpy(&this->technology, data, sizeof(CHKSectionTECS::technology));
}
u8* CHKSectionTECS::save_data(u32 &size) {
	size = sizeof(CHKSectionTECS::technology);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->technology, size);
	return buffer;
}
