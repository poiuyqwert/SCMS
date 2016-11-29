//
//  CHKSectionIVE2.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionIVE2 : public CHKSection {
	u16 version;
public:
	static const u32 ID = L('IVE2');
	static const CHKRequirements Requirements;
	
	enum : u16 {
		Release = 11
	};
	
	CHKSectionIVE2(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionIVE2::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
