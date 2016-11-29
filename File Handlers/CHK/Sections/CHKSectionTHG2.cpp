//
//  CHKSectionTHG2.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionTHG2.h"

const CHKRequirements CHKSectionTHG2::Requirements = {CHKVer::All, CHKGameMode::All};
void CHKSectionTHG2::load_data(const u8 *data, u32 size) {
	int sprites = size / sizeof(CHKSprite);
	this->sprites.assign((CHKSprite *)data, (CHKSprite *)data + sprites);
}
u8* CHKSectionTHG2::save_data(u32 &size) {
	size = sizeof(CHKSprite) * this->sprites.size();
	u8 *buffer = new u8[size];
	memcpy(buffer, this->sprites.data(), size);
	return buffer;
}
