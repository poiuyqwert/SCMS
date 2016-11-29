//
//  CHKSectionOWNR.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionOWNR : public CHKSection {
	u8 owners[StarCraft::Player::COUNT];
public:
	static const u32 ID = L('OWNR');
	static const CHKRequirements Requirements;
	
	enum : u8 {
		Inactive,
		OccupiedComouter, // INVALID
		OccupiedHuman, // INVALID
		ReusePassive,
		Unused,
		Computer,
		Human,
		Neutral,
		Closed // INVALID
	};
	
	CHKSectionOWNR(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionOWNR::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
