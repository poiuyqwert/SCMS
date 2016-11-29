//
//  CHKSectionSIDE.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionSIDE.h"

#include <string>

const CHKRequirements CHKSectionSIDE::Requirements = {CHKVer::All, CHKGameMode::All};
CHKSectionSIDE::CHKSectionSIDE(CHK *chk)
	: CHKSection(chk)
{
	memset(this->sides, CHKSectionSIDE::Random, 8);
	memset(this->sides+8, CHKSectionSIDE::UnusedNeutral, 4);
}
void CHKSectionSIDE::load_data(const u8 *data, u32 size) {
	memcpy(this->sides, data, sizeof(CHKSectionSIDE::sides));
}
u8* CHKSectionSIDE::save_data(u32 &size) {
	size = sizeof(CHKSectionSIDE::sides);
	u8 *buffer = new u8[size];
	memcpy(buffer, this->sides, size);
	return buffer;
}
