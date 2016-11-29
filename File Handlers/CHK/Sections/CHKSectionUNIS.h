//
//  CHKSectionUNIS.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionUNIS : public CHKSection {
#pragma pack(push, 1)
	struct {
		struct {
			u8 useGlobal[StarCraft::Unit::COUNT];
			u32 health[StarCraft::Unit::COUNT];
			u16 shields[StarCraft::Unit::COUNT];
			u8 armor[StarCraft::Unit::COUNT];
			struct {
				u16 buildTime[StarCraft::Unit::COUNT];
				u16 minerals[StarCraft::Unit::COUNT];
				u16 gas[StarCraft::Unit::COUNT];
			} cost;
			u16 stringID;
		} unit;
		struct {
			u16 baseDamage[StarCraft::Weapon::COUNT];
			u16 upgradeDamage[StarCraft::Weapon::COUNT];
		} weapon;
	} settings;
#pragma pack(pop)
public:
	static const u32 ID = L('UNIS');
	static const CHKRequirements Requirements;
	
	CHKSectionUNIS(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionUNIS::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
