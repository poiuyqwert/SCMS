//
//  CHKSectionTECx.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionTECx.h"

#include <string>

const CHKRequirements CHKSectionTECx::Requirements = {CHKVer::VanillaHybrid, CHKGameMode::UseMapSettings};
CHKSectionTECx::CHKSectionTECx(CHK *chk)
	: CHKSection(chk)
{
#warning COMPLEX DEFAULTS
}
void CHKSectionTECx::load_data(const u8 *data, u32 size) {
	memcpy(&this->technology, data, sizeof(CHKSectionTECx::technology));
}
u8* CHKSectionTECx::save_data(u32 &size) {
	size = sizeof(CHKSectionTECx::technology);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->technology, size);
	return buffer;
}
