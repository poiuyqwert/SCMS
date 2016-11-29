//
//  CHKSectionFORC.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionFORC : public CHKSection {
#pragma pack(push, 1)
	struct {
		u8 player[StarCraft::Player::COUNT_PLAYABLE];
		u16 stringID[4];
		u8 flags[4];
	} force;
#pragma pack(pop)
public:
	static const u32 ID = L('FORC');
	static const CHKRequirements Requirements;
	
	enum : u8 {
		RandomStartLocation	= (1<<0),
		Allies				= (1<<1),
		AlliedVictory		= (1<<2),
		SharedVision		= (1<<3)
	};
	
	CHKSectionFORC(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionFORC::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
