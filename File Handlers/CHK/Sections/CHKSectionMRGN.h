//
//  CHKSectionMRGN.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

#pragma pack(push, 1)
struct CHKLocation {
	struct {
		u32 left;
		u32 top;
		u32 right;
		u32 bottom;
	} rect;
	u16 stringID;
	u16 disabledElevations;
	
	enum Elevation : u16 {
		None		= 0,
		
		Low			= (1<<0),
		Medium		= (1<<1),
		High		= (1<<2),
		LowAir		= (1<<3),
		MediumAir	= (1<<4),
		HighAir		= (1<<5),
		
		All			= (Low | Medium | High | LowAir | MediumAir | HighAir)
	};
};
#pragma pack(pop)
class CHKSectionMRGN : public CHKSection {
	CHKLocation locations[255];
public:
	static const u32 ID = L('MRGN');
	static const CHKRequirements Requirements;
	
	static const int AnywhereID = 63;
	
	CHKSectionMRGN(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionMRGN::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
	
	CHKLocation get_location(int n)
		{ return this->locations[n]; }
	void set_location(int n, CHKLocation location)
		{ this->locations[n] = location; }
	
	int max_locations();
};
