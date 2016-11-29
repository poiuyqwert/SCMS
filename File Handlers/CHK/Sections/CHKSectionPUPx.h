//
//  CHKSectionPUPx.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionPUPx : public CHKSection {
#pragma pack(push, 1)
	struct {
		struct {
			u8 max[StarCraft::Player::COUNT][BroodWar::Upgrade::COUNT];
			u8 start[StarCraft::Player::COUNT][BroodWar::Upgrade::COUNT];
		} player;
		struct {
			u8 max[BroodWar::Upgrade::COUNT];
			u8 start[BroodWar::Upgrade::COUNT];
		} global;
		u8 useGlobal[StarCraft::Player::COUNT][BroodWar::Upgrade::COUNT];
	} levels;
#pragma pack(pop)
public:
	static const u32 ID = L('PUP ');
	static const CHKRequirements Requirements;
	
	CHKSectionPUPx(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionPUPx::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
