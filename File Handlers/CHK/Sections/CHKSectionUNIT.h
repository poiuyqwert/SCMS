//
//  CHKSectionUNIT.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "CHKSectionUPRP.h"

#include <vector>

#pragma pack(push, 1)
struct CHKUnit {
	u32 instanceID;
	struct {
		u16 x;
		u16 y;
	} pos;
	u16 unitID;
	u16 unitRelation;
	CHKUnitProperties properties;
	u32 relationInstanceID;
	
	enum Relation : u16 {
		NydusLink	= (1 << 9),
		AddonLink	= (1 << 10)
	};
};
#pragma pack(pop)
class CHKSectionUNIT : public CHKSection {
	std::vector<CHKUnit> units;
public:
	static const u32 ID = L('UNIT');
	static const CHKRequirements Requirements;
	
	CHKSectionUNIT(CHK *chk)
		: CHKSection(chk) {}
	
	u32 sectionID()
		{ return CHKSectionUNIT::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
