//
//  CHKSectionPTEx.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionPTEx.h"

#include <string>

const CHKRequirements CHKSectionPTEx::Requirements = {CHKVer::VanillaHybrid, CHKGameMode::UseMapSettings};
CHKSectionPTEx::CHKSectionPTEx(CHK *chk)
	: CHKSection(chk)
{
#warning COMPLEX DEFAULTS
}
void CHKSectionPTEx::load_data(const u8 *data, u32 size) {
	memcpy(&this->technology, data, sizeof(CHKSectionPTEx::technology));
}
u8* CHKSectionPTEx::save_data(u32 &size) {
	size = sizeof(CHKSectionPTEx::technology);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->technology, size);
	return buffer;
}
