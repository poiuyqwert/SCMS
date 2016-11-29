//
//  CHKSectionMASK.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionMASK : public CHKSection {
	u8 *map;
public:
	static const u32 ID = L('MASK');
	static const CHKRequirements Requirements;
	
	CHKSectionMASK(CHK *chk)
		: CHKSection(chk),map(nullptr) {}
	
	u32 sectionID()
		{ return CHKSectionMASK::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
