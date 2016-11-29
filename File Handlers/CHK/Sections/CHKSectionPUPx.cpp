//
//  CHKSectionPUPx.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionPUPx.h"

#include <string>

const CHKRequirements CHKSectionPUPx::Requirements = {CHKVer::BroodwarHybrid, CHKGameMode::UseMapSettings};
CHKSectionPUPx::CHKSectionPUPx(CHK *chk)
	: CHKSection(chk)
{
#warning COMPLEX DEFAULTS
}
void CHKSectionPUPx::load_data(const u8 *data, u32 size) {
	memcpy(&this->levels, data, sizeof(CHKSectionPUPx::levels));
}
u8* CHKSectionPUPx::save_data(u32 &size) {
	size = sizeof(CHKSectionPUPx::levels);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->levels, size);
	return buffer;
}
