//
//  CHKSectionISOM.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionISOM : public CHKSection {
	u16 *isom;
public:
	static const u32 ID = L('ISOM');
	static const CHKRequirements Requirements;
	
	CHKSectionISOM(CHK *chk)
		: CHKSection(chk),isom(nullptr) {}
	
	u32 sectionID()
		{ return CHKSectionISOM::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
