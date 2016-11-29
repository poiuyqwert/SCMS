//
//  CHKSectionDD2.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

#include <vector>

#pragma pack(push, 1)
struct CHKDoodadUnit {
	u16 doodadID;
	struct {
		u16 x;
		u16 y;
	} pos;
	u8 owner;
	u8 disabled;
};
#pragma pack(pop)
class CHKSectionDD2 : public CHKSection {
	std::vector<CHKDoodadUnit> doodads;
public:
	static const u32 ID = L('DD2 ');
	static const CHKRequirements Requirements;
	
	CHKSectionDD2(CHK *chk)
		: CHKSection(chk) {}
	
	u32 sectionID()
		{ return CHKSectionDD2::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
