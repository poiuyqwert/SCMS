//
//  CHKSectionPTEx.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionPTEx : public CHKSection {
#pragma pack(push, 1)
	struct {
		struct {
			u8 available[StarCraft::Player::COUNT][BroodWar::Technology::COUNT];
			u8 researched[StarCraft::Player::COUNT][BroodWar::Technology::COUNT];
		} player;
		struct {
			u8 available[BroodWar::Technology::COUNT];
			u8 researched[BroodWar::Technology::COUNT];
		} global;
		u8 useGlobal[StarCraft::Player::COUNT][BroodWar::Technology::COUNT];
	} technology;
#pragma pack(pop)
public:
	static const u32 ID = L('PTE ');
	static const CHKRequirements Requirements;
	
	CHKSectionPTEx(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionPTEx::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
