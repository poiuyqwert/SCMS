//
//  CHKSectionUPRP.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionUPRP.h"

#include <string>

const CHKRequirements CHKSectionUPRP::Requirements = {CHKVer::All, CHKGameMode::UseMapSettings};
CHKSectionUPRP::CHKSectionUPRP(CHK *chk)
	: CHKSection(chk)
{
	memset(&this->properties, 0, sizeof(CHKSectionUPRP::properties));
}
void CHKSectionUPRP::load_data(const u8 *data, u32 size) {
	memcpy(&this->properties, data, sizeof(CHKSectionUPRP::properties));
}
u8* CHKSectionUPRP::save_data(u32 &size) {
	size = sizeof(CHKSectionUPRP::properties);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->properties, size);
	return buffer;
}
