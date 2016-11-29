//
//  CHKSectionOWNR.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionOWNR.h"

#include <string>

const CHKRequirements CHKSectionOWNR::Requirements = {CHKVer::None, CHKGameMode::None};
CHKSectionOWNR::CHKSectionOWNR(CHK *chk)
	: CHKSection(chk)
{
	memset(this->owners, CHKSectionOWNR::Human, 8);
	memset(this->owners+8, CHKSectionOWNR::Inactive, 3);
	this->owners[11] = CHKSectionOWNR::Neutral;
}
void CHKSectionOWNR::load_data(const u8 *data, u32 size) {
	memcpy(this->owners, data, sizeof(CHKSectionOWNR::owners));
}
u8* CHKSectionOWNR::save_data(u32 &size) {
	size = sizeof(CHKSectionOWNR::owners);
	u8 *buffer = new u8[size];
	memcpy(buffer, this->owners, size);
	return buffer;
}
