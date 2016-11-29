//
//  CHKSectionIVE2.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionIVE2.h"

const CHKRequirements CHKSectionIVE2::Requirements = {CHKVer::None, CHKGameMode::None};
CHKSectionIVE2::CHKSectionIVE2(CHK *chk)
	: CHKSection(chk)
{
	this->version = CHKSectionIVE2::Release;
}
void CHKSectionIVE2::load_data(const u8 *data, u32 size) {
	this->version = *(u16 *)data;
}
u8* CHKSectionIVE2::save_data(u32 &size) {
	size = sizeof(u16);
	u8 *buffer = new u8[sizeof(u16)];
	*(u16 *)buffer = this->version;
	return buffer;
}
