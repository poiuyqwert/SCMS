//
//  CHKSectionUPGR.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionUPGR.h"

#include <string>

const CHKRequirements CHKSectionUPGR::Requirements = {CHKVer::VanillaHybrid, CHKGameMode::UseMapSettings};
CHKSectionUPGR::CHKSectionUPGR(CHK *chk)
	: CHKSection(chk)
{
#warning COMPLEX DEFAULTS
}
void CHKSectionUPGR::load_data(const u8 *data, u32 size) {
	memcpy(&this->levels, data, sizeof(CHKSectionUPGR::levels));
}
u8* CHKSectionUPGR::save_data(u32 &size) {
	size = sizeof(CHKSectionUPGR::levels);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->levels, size);
	return buffer;
}
