//
//  CHKSectionUNIT.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionUNIT.h"

const CHKRequirements CHKSectionUNIT::Requirements = {CHKVer::All, CHKGameMode::All};
void CHKSectionUNIT::load_data(const u8 *data, u32 size) {
	int units = size / sizeof(CHKUnit);
	this->units.assign((CHKUnit *)data, (CHKUnit *)data + units);
}
u8* CHKSectionUNIT::save_data(u32 &size) {
	size = sizeof(CHKUnit) * this->units.size();
	u8 *buffer = new u8[size];
	memcpy(buffer, this->units.data(), size);
	return buffer;
}
