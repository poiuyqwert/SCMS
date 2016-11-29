//
//  CHKSectionSPRP.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionSPRP.h"

#include <string>

const CHKRequirements CHKSectionSPRP::Requirements = {CHKVer::All, CHKGameMode::All};
CHKSectionSPRP::CHKSectionSPRP(CHK *chk)
	: CHKSection(chk)
{
	memset(&this->scenario, 0, sizeof(CHKSectionSPRP::scenario));
}
void CHKSectionSPRP::load_data(const u8 *data, u32 size) {
	memcpy(&this->scenario, data, sizeof(CHKSectionSPRP::scenario));
}
u8* CHKSectionSPRP::save_data(u32 &size) {
	size = sizeof(CHKSectionSPRP::scenario);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->scenario, size);
	return buffer;
}
