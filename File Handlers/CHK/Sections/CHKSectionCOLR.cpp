//
//  CHKSectionCOLR.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionCOLR.h"

#include <string>

u8 CHKSectionCOLR::DEFAULTS[SC::Player::COUNT_PLAYABLE] = {0,1,2,3,4,5,6,7};

const CHKRequirements CHKSectionCOLR::Requirements = {CHKVer::None, CHKGameMode::None};
CHKSectionCOLR::CHKSectionCOLR(CHK *chk)
	: CHKSection(chk)
{
	memset(this->colors, 0, sizeof(CHKSectionCOLR::colors));
}
void CHKSectionCOLR::load_data(const u8 *data, u32 size) {
	memcpy(this->colors, data, sizeof(CHKSectionCOLR::colors));
}
u8* CHKSectionCOLR::save_data(u32 &size) {
	size = sizeof(CHKSectionCOLR::colors);
	u8 *buffer = new u8[size];
	memcpy(buffer, this->colors, size);
	return buffer;
}
