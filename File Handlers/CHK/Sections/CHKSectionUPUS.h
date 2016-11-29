//
//  CHKSectionUPUS.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionUPUS : public CHKSection {
	u8 propertiesUsed[64];
public:
	static const u32 ID = L('UPUS');
	static const CHKRequirements Requirements;
	
	CHKSectionUPUS(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionUPUS::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
