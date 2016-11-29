//
//  CHKSectionIOWN.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionIOWN.h"

#include <string>

const CHKRequirements CHKSectionIOWN::Requirements = {CHKVer::None, CHKGameMode::None};
CHKSectionIOWN::CHKSectionIOWN(CHK *chk)
	: CHKSection(chk)
{
	memset(this->owners, CHKSectionIOWN::Human, 8);
	memset(this->owners+8, CHKSectionIOWN::Inactive, 3);
	this->owners[11] = CHKSectionIOWN::Neutral;
}
void CHKSectionIOWN::load_data(const u8 *data, u32 size) {
	memcpy(this->owners, data, sizeof(CHKSectionIOWN::owners));
}
u8* CHKSectionIOWN::save_data(u32 &size) {
	size = sizeof(CHKSectionIOWN::owners);
	u8 *buffer = new u8[size];
	memcpy(buffer, this->owners, size);
	return buffer;
}
