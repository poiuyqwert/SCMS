//
//  CHKSectionISOM.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionISOM.h"

#include "CHK.h"
#include "CHKSectionDIM.h"

#include <string>
#include <algorithm>

const CHKRequirements CHKSectionISOM::Requirements = {CHKVer::None, CHKGameMode::None};
void CHKSectionISOM::load_data(const u8 *data, u32 size) {
	CHKSectionDIM *dims = this->chk->get_section<CHKSectionDIM>();
	Size<u16> mapSize = dims->get_size();
	u32 isomSize = ((mapSize.width / 2 + 1) * (mapSize.height + 1) * 4);
	this->isom = new u16[isomSize];
	memcpy(this->isom, data, sizeof(u16) * std::min(isomSize,size));
	if (size < isomSize) {
		memset(this->isom+size, 0, isomSize-size);
	}
}
u8* CHKSectionISOM::save_data(u32 &size) {
	CHKSectionDIM *dims = chk->get_section<CHKSectionDIM>();
	Size<u16> mapSize = dims->get_size();
	size = sizeof(u16) * ((mapSize.width / 2 + 1) * (mapSize.height + 1) * 4);
	u8 *buffer = new u8[size];
	memcpy(buffer, this->isom, size);
	return buffer;
}
