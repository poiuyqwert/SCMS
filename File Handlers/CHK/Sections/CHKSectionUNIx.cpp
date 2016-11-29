//
//  CHKSectionUNIx.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionUNIx.h"

#include <string>

const CHKRequirements CHKSectionUNIx::Requirements = {CHKVer::BroodwarHybrid, CHKGameMode::UseMapSettings};
CHKSectionUNIx::CHKSectionUNIx(CHK *chk)
	: CHKSection(chk)
{
#warning COMPLEX DEFAULTS
}
void CHKSectionUNIx::load_data(const u8 *data, u32 size) {
	memcpy(&this->settings, data, sizeof(CHKSectionUNIx::settings));
}
u8* CHKSectionUNIx::save_data(u32 &size) {
	size = sizeof(CHKSectionUNIx::settings);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->settings, size);
	return buffer;
}
