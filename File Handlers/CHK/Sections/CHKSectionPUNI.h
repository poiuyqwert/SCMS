//
//  CHKSectionPUNI.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionPUNI : public CHKSection {
#pragma pack(push, 1)
	struct {
		u8 player[StarCraft::Player::COUNT][StarCraft::Unit::COUNT];
		u8 global[StarCraft::Unit::COUNT];
		u8 useGlobal[StarCraft::Player::COUNT][StarCraft::Unit::COUNT];
	} availability;
#pragma pack(pop)
public:
	static const u32 ID = L('PUNI');
	static const CHKRequirements Requirements;
	
	CHKSectionPUNI(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionPUNI::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
