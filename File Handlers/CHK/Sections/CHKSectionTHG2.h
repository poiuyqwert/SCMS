//
//  CHKSectionTHG2.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

#include <vector>

#pragma pack(push, 1)
struct CHKSprite {
	union {
		u16 unit;
		u16 sprite;
	} id;
	u16 x;
	u16 y;
	u8 owner;
	u8 unused;
	u16 flags;
	
	enum Flag : u16 {
		Sprite		= (1<<12),
		Disabled	= (1<<15)
	};
};
#pragma pack(pop)
class CHKSectionTHG2 : public CHKSection {
	std::vector<CHKSprite> sprites;
public:
	static const u32 ID = L('THG2');
	static const CHKRequirements Requirements;
	
	CHKSectionTHG2(CHK *chk)
		: CHKSection(chk) {}
	
	u32 sectionID()
		{ return CHKSectionTHG2::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
