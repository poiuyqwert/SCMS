//
//  CHKSectionUnknown.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHK;

class CHKSectionUnknown : public CHKSection {
	u32 _sectionID;
	u8 *data;
	int size;
public:
	CHKSectionUnknown(CHK *chk, u32 sectionID)
		: CHKSection(chk), _sectionID(sectionID), data(nullptr) {}
	
	u32 sectionID()
		{ return this->_sectionID; }

	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};