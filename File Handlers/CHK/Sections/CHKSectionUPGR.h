//
//  CHKSectionUPGR.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionUPGR : public CHKSection {
#pragma pack(push, 1)
	struct {
		struct {
			u8 max[StarCraft::Player::COUNT][StarCraft::Upgrade::COUNT];
			u8 start[StarCraft::Player::COUNT][StarCraft::Upgrade::COUNT];
		} player;
		struct {
			u8 max[StarCraft::Upgrade::COUNT];
			u8 start[StarCraft::Upgrade::COUNT];
		} global;
		u8 useGlobal[StarCraft::Player::COUNT][StarCraft::Upgrade::COUNT];
	} levels;
#pragma pack(pop)
public:
	static const u32 ID = L('UPGR');
	static const CHKRequirements Requirements;
	
	CHKSectionUPGR(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionUPGR::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
