//
//  CHKSectionSPRP.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionSPRP : public CHKSection {
	struct {
		u16 name;
		u16 description;
	} scenario;
public:
	static const u32 ID = L('SPRP');
	static const CHKRequirements Requirements;
	
	CHKSectionSPRP(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionSPRP::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
	
	u16 get_scenarioName()
		{ return this->scenario.name; }
	u16 get_scenarioDescription()
		{ return this->scenario.description; }
};
