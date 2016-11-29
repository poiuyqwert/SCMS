//
//  CHKSectionTECx.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionTECx : public CHKSection {
#pragma pack(push, 1)
	struct {
		u8 useGlobal[BroodWar::Technology::COUNT];
		struct {
			u16 minerals[BroodWar::Technology::COUNT];
			u16 gas[BroodWar::Technology::COUNT];
			u16 buildTime[BroodWar::Technology::COUNT];
		} cost;
		u16 castEnergy[BroodWar::Technology::COUNT];
	} technology;
#pragma pack(pop)
public:
	static const u32 ID = L('TEC ');
	static const CHKRequirements Requirements;
	
	CHKSectionTECx(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionTECx::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
