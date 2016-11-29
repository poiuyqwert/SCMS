//
//  CHKSectionSIDE.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionSIDE : public CHKSection {
	u8 sides[StarCraft::Player::COUNT];
public:
	static const u32 ID = L('SIDE');
	static const CHKRequirements Requirements;
	
	enum : u8 {
		Zerg,
		Terran,
		Protoss,
		UnusedIndependent,
		UnusedNeutral,
		UserSelect,
		Random,
		Inactive
	};
	
	CHKSectionSIDE(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionSIDE::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
