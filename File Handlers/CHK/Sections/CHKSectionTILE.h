//
//  CHKSectionTILE.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "CHKTile.h"

class CHKSectionTILE : public CHKSection {
	CHKTile *map;
public:
	static const u32 ID = L('TILE');
	static const CHKRequirements Requirements;
	
	CHKSectionTILE(CHK *chk)
		: CHKSection(chk),map(nullptr) {}
	
	u32 sectionID()
		{ return CHKSectionTILE::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
	
	CHKTile get_tile(int x, int y);
};
