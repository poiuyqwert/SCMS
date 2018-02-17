//
//  CHKSectionERA.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionERA : public CHKSection {
	u16 tileset;
public:
	static const u32 ID = L('ERA ');
	static const CHKRequirements Requirements;
	
	enum : u16 {
		Badlands,
		Space,
		Installation,
		Ashworld,
		Jungle,
		Desert,
		Arctic,
		Twilight,
		
		COUNT
	};
	static const char *TilesetFilenames[COUNT];
	
	CHKSectionERA(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionERA::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
	
	u16 get_tileset()
		{ return this->tileset; }
	void set_tileset(u16 tileset)
		{ this->tileset = tileset; }
};
