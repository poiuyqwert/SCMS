//
//  CHKSectionPTEC.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionPTEC : public CHKSection {
#pragma pack(push, 1)
	struct {
		struct {
			u8 available[StarCraft::Player::COUNT][StarCraft::Technology::COUNT];
			u8 researched[StarCraft::Player::COUNT][StarCraft::Technology::COUNT];
		} player;
		struct {
			u8 available[StarCraft::Technology::COUNT];
			u8 researched[StarCraft::Technology::COUNT];
		} global;
		u8 useGlobal[StarCraft::Player::COUNT][StarCraft::Technology::COUNT];
	} technology;
#pragma pack(pop)
public:
	static const u32 ID = L('PTEC');
	static const CHKRequirements Requirements;
	
	CHKSectionPTEC(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionPTEC	::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
