//
//  CHKSectionSWNM.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionSWNM : public CHKSection {
	u32 stringID[256];
public:
	static const u32 ID = L('SWNM');
	static const CHKRequirements Requirements;
	
	CHKSectionSWNM(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionSWNM::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
