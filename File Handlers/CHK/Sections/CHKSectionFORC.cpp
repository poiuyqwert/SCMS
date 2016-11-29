//
//  CHKSectionFORC.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionFORC.h"

#include <string>

const CHKRequirements CHKSectionFORC::Requirements = {CHKVer::All, CHKGameMode::All};
CHKSectionFORC::CHKSectionFORC(CHK *chk)
	: CHKSection(chk)
{
#warning COMPLEX DEFAULTS
}
void CHKSectionFORC::load_data(const u8 *data, u32 size) {
	memcpy(&this->force, data, sizeof(CHKSectionFORC::force));
}
u8* CHKSectionFORC::save_data(u32 &size) {
	size = sizeof(CHKSectionFORC::force);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->force, size);
	return buffer;
}
