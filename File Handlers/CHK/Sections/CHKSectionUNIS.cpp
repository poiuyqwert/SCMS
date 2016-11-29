//
//  CHKSectionUNIS.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionUNIS.h"

#include <string>

const CHKRequirements CHKSectionUNIS::Requirements = {CHKVer::VanillaHybrid, CHKGameMode::UseMapSettings};
CHKSectionUNIS::CHKSectionUNIS(CHK *chk)
	: CHKSection(chk)
{
#warning COMPLEX DEFAULTS
}
void CHKSectionUNIS::load_data(const u8 *data, u32 size) {
	memcpy(&this->settings, data, sizeof(CHKSectionUNIS::settings));
}
u8* CHKSectionUNIS::save_data(u32 &size) {
	size = sizeof(CHKSectionUNIS::settings);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->settings, size);
	return buffer;
}
