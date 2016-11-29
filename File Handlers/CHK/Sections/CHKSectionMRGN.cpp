//
//  CHKSectionMRGN.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionMRGN.h"

#include <string>

const CHKRequirements CHKSectionMRGN::Requirements = {CHKVer::All, CHKGameMode::UseMapSettings};
CHKSectionMRGN::CHKSectionMRGN(CHK *chk)
	: CHKSection(chk)
{
	memset(&this->locations, 0, sizeof(CHKSectionMRGN::locations));
}
void CHKSectionMRGN::load_data(const u8 *data, u32 size) {
	memcpy(&this->locations, data, sizeof(CHKSectionMRGN::locations));
}
u8* CHKSectionMRGN::save_data(u32 &size) {
	size = sizeof(CHKSectionMRGN::locations);
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->locations, size);
	return buffer;
}
