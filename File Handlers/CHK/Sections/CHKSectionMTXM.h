//
//  CHKSectionMTXM.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "CHKTile.h"

class CHKSectionMTXM : public CHKSection {
	CHKTile *map;
public:
	static const u32 ID = L('MTXM');
	static const CHKRequirements Requirements;
	
	CHKSectionMTXM(CHK *chk)
		: CHKSection(chk),map(nullptr) {}
	
	u32 sectionID()
		{ return CHKSectionMTXM::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
	
	CHKTile get_tile(int x, int y);
};
