//
//  CHKSectionUPGx.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionUPGx.h"

#include <string>

const CHKRequirements CHKSectionUPGx::Requirements = {CHKVer::VanillaHybrid, CHKGameMode::UseMapSettings};
CHKSectionUPGx::CHKSectionUPGx(CHK *chk)
	: CHKSection(chk)
{
#warning COMPLEX DEFAULTS
}
void CHKSectionUPGx::load_data(const u8 *data, u32 size) {
	memcpy(&this->upgrade, data, sizeof(CHKSectionUPGx::upgrade));
}
u8* CHKSectionUPGx::save_data(u32 &size) {
	size = sizeof(CHKSectionUPGx::upgrade);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->upgrade, size);
	return buffer;
}
