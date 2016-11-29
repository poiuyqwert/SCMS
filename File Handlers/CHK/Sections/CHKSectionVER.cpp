//
//  CHKSectionVER.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionVER.h"

#include "CHK.h"
#include "CHKSectionTYPE.h"

CHKSectionVER::CHKSectionVER(CHK *chk)
	: CHKSection(chk)
{
	this->version = CHKSectionVER::BroodWar;
	if (this->chk) {
		CHKSectionTYPE *typeSect = this->chk->get_section<CHKSectionTYPE>(false, false);
		if (typeSect != nullptr && typeSect->get_type() == CHKSectionTYPE::BroodWar) {
			this->version = CHKSectionVER::SC104;
		}
	}
}

void CHKSectionVER::load_data(const u8 *data, u32 size) {
	this->version = *(u16 *)data;
}

u8* CHKSectionVER::save_data(u32 &size) {
	size = sizeof(u16);
	u16 *buffer = new u16;
	*buffer = this->version;
	return (u8*)buffer;
}