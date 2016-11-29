//
//  CHKSectionPUNI.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionPUNI.h"

#include <string>

const CHKRequirements CHKSectionPUNI::Requirements = {CHKVer::All, CHKGameMode::UseMapSettings};
CHKSectionPUNI::CHKSectionPUNI(CHK *chk)
	: CHKSection(chk)
{
	memset(&this->availability, 1, sizeof(CHKSectionPUNI::availability));
}
void CHKSectionPUNI::load_data(const u8 *data, u32 size) {
	memcpy(&this->availability, data, sizeof(CHKSectionPUNI::availability));
}
u8* CHKSectionPUNI::save_data(u32 &size) {
	size = sizeof(CHKSectionPUNI::availability);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->availability, size);
	return buffer;
}
