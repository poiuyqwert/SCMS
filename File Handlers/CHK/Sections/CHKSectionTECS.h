//
//  CHKSectionTECS.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionTECS : public CHKSection {
#pragma pack(push, 1)
	struct {
		u8 useGlobal[StarCraft::Technology::COUNT];
		struct {
			u16 minerals[StarCraft::Technology::COUNT];
			u16 gas[StarCraft::Technology::COUNT];
			u16 buildTime[StarCraft::Technology::COUNT];
		} cost;
		u16 castEnergy[StarCraft::Technology::COUNT];
	} technology;
#pragma pack(pop)
public:
	static const u32 ID = L('TECS');
	static const CHKRequirements Requirements;
	
	CHKSectionTECS(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionTECS::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
