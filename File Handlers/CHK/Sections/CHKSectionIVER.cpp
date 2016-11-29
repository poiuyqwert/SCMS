//
//  CHKSectionIVER.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionIVER.h"

#include "CHK.h"
#include "CHKSectionVER.h"

const CHKRequirements CHKSectionIVER::Requirements = {CHKVer::None, CHKGameMode::None};
CHKSectionIVER::CHKSectionIVER(CHK *chk)
	: CHKSection(chk)
{
	this->version = CHKSectionIVER::Release;
	if (this->chk) {
		CHKSectionVER *verSect = this->chk->get_section<CHKSectionVER>(false, false);
		if (verSect != nullptr && verSect->get_version() == CHKSectionVER::Beta) {
			this->version = CHKSectionIVER::Beta;
		}
	}
}
void CHKSectionIVER::load_data(const u8 *data, u32 size) {
	this->version = *(u16 *)data;
}
u8* CHKSectionIVER::save_data(u32 &size) {
	size = sizeof(u16);
	u16 *buffer = new u16;
	*buffer = this->version;
	return (u8*)buffer;
}
