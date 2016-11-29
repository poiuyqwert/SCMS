//
//  CHKSectionTYPE.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionTYPE : public CHKSection {
	u32 type;
public:
	static const u32 ID = L('TYPE');
	static const CHKRequirements Requirements;
	
	enum : u32 {
		StarCraft	= L('RAWS'),
		BroodWar	= L('RAWB')
	};
	
	CHKSectionTYPE(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionTYPE::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
	
	u32 get_type()
		{ return this->type; }
};
