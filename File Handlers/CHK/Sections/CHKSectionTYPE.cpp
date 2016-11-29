//
//  CHKSectionTYPE.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionTYPE.h"

#include "CHK.h"
#include "CHKSectionVER.h"

const CHKRequirements CHKSectionTYPE::Requirements = {CHKVer::None, CHKGameMode::None};
CHKSectionTYPE::CHKSectionTYPE(CHK *chk)
	: CHKSection(chk)
{
	this->type = CHKSectionTYPE::StarCraft;
	if (this->chk) {
		CHKSectionVER *verSect = this->chk->get_section<CHKSectionVER>(false, false);
		if (verSect != nullptr && verSect->get_version() == CHKSectionVER::BroodWar) {
			this->type = CHKSectionTYPE::BroodWar;
		}
	}
}
void CHKSectionTYPE::load_data(const u8 *data, u32 size) {
	this->type = *(u16 *)data;
}
u8* CHKSectionTYPE::save_data(u32 &size) {
	size = sizeof(u16);
	u16 *buffer = new u16;
	*buffer = this->type;
	return (u8*)buffer;
}
