//
//  CHKSectionWAV.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionWAV : public CHKSection {
	u32 stringID[512];
public:
	static const u32 ID = L('WAV ');
	static const CHKRequirements Requirements;
	
	CHKSectionWAV(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionWAV::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
