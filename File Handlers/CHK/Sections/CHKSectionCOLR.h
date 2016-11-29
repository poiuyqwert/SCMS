//
//  CHKSectionCOLR.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionCOLR : public CHKSection {
	u8 colors[StarCraft::Player::COUNT_PLAYABLE];
public:
	static const u32 ID = L('COLR');
	static const CHKRequirements Requirements;
	
	enum : u8 {
		Red,
		Blue,
		Teal,
		Purple,
		Orange,
		Brown,
		White,
		Yellow,
		Green,
		PaleYellow,
		Tan,
		Azure,
		
		Neutral = Azure
	};
	
	CHKSectionCOLR(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionCOLR::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
