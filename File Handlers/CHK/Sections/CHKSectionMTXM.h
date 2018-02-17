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
#include "Geometry.h"

class CHKSectionMTXM : public CHKSection {
public:
	CHKTile *tiles;

	static const u32 ID = L('MTXM');
	static const CHKRequirements Requirements;
	
	CHKSectionMTXM(CHK *chk)
		: CHKSection(chk),tiles(nullptr) {}
	
	u32 sectionID()
		{ return CHKSectionMTXM::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
	
	CHKTile* get_tiles()
		{ return this->tiles; }
	void set_tiles(CHKTile *tiles)
		{ this->tiles = tiles; }
	
	CHKTile get_tile(Point<u8> point);
	void set_tile(CHKTile tile, Point<u8> point);
};
