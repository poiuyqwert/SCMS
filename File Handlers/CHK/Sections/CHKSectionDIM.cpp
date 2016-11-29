//
//  CHKSectionDIM.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionDIM.h"

#include <string>

const CHKRequirements CHKSectionDIM::Requirements = {CHKVer::All, CHKGameMode::All};
CHKSectionDIM::CHKSectionDIM(CHK *chk)
	: CHKSection(chk)
{
	this->size.width = CHKSectionDIM::Medium;
	this->size.height = CHKSectionDIM::Medium;
}
void CHKSectionDIM::load_data(const u8 *data, u32 size) {
	memcpy(&this->size, data, sizeof(CHKSectionDIM::size));
}
u8* CHKSectionDIM::save_data(u32 &size) {
	size = sizeof(CHKSectionDIM::size);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->size, size);
	return buffer;
}
