//
//  CHKSectionTRIG.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionTRIG.h"

const CHKRequirements CHKSectionTRIG::Requirements = {CHKVer::All, CHKGameMode::UseMapSettings};
void CHKSectionTRIG::load_data(const u8 *data, u32 size) {
	int triggers = size / sizeof(TRGTrigger);
	this->triggers.assign((TRGTrigger *)data, (TRGTrigger *)data + triggers);
}
u8* CHKSectionTRIG::save_data(u32 &size) {
	size = sizeof(TRGTrigger) * this->triggers.size();
	u8 *buffer = new u8[size];
	memcpy(buffer, this->triggers.data(), size);
	return buffer;
}
