//
//  CHKSectionMRGN.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionMRGN.h"
#include "CHK.h"
#include "CHKSectionVER.h"

#include <string>

const CHKRequirements CHKSectionMRGN::Requirements = {CHKVer::All, CHKGameMode::UseMapSettings};
CHKSectionMRGN::CHKSectionMRGN(CHK *chk)
	: CHKSection(chk)
{
	memset(&this->locations, 0, sizeof(CHKSectionMRGN::locations));
}
void CHKSectionMRGN::load_data(const u8 *data, u32 size) {
	memcpy(&this->locations, data, size);
}
u8* CHKSectionMRGN::save_data(u32 &size) {
	size = sizeof(CHKLocation) * this->max_locations();
	u8 *buffer = new u8[size];
	memcpy(buffer, &this->locations, size);
	return buffer;
}

int CHKSectionMRGN::max_locations() {
	CHKSectionVER *ver = chk->get_section<CHKSectionVER>();
	if (ver == NULL || ver->get_version() == CHKSectionVER::SC104 || ver->get_version() == CHKSectionVER::BroodWar) {
		return 255;
	}
	return 64;
}
