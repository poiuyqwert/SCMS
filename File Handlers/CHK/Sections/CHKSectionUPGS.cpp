//
//  CHKSectionUPGS.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionUPGS.h"

#include <string>

const CHKRequirements CHKSectionUPGS::Requirements = {CHKVer::VanillaHybrid, CHKGameMode::UseMapSettings};
CHKSectionUPGS::CHKSectionUPGS(CHK *chk)
	: CHKSection(chk)
{
#warning COMPLEX DEFAULTS
}
void CHKSectionUPGS::load_data(const u8 *data, u32 size) {
	memcpy(&this->upgrade, data, sizeof(CHKSectionUPGS::upgrade));
}
u8* CHKSectionUPGS::save_data(u32 &size) {
	size = sizeof(CHKSectionUPGS::upgrade);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->upgrade, size);
	return buffer;
}
