//
//  CHKSectionTRIG.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "TRG.h"

#include <vector>

class CHKSectionTRIG : public CHKSection {
	std::vector<TRGTrigger> triggers;
public:
	static const u32 ID = L('TRIG');
	static const CHKRequirements Requirements;
	
	CHKSectionTRIG(CHK *chk)
		: CHKSection(chk) {}
	
	u32 sectionID()
		{ return CHKSectionTRIG::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
