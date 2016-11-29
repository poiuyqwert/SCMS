//
//  CHKSectionSTR.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

#include <map>
#include <set>

struct CHKString {
	int length;
	u8* string;
	
	bool isNull()
		{ return (this->length == 0 && this->string == 0); }
};
extern CHKString CHKStringNULL;
class CHKSectionSTR : public CHKSection {
	std::map<u16, CHKString> strings;
	std::set<u16> openIDs;
public:
	static const u32 ID = L('STR ');
	static const CHKRequirements Requirements;
	
	CHKSectionSTR(CHK *chk)
		: CHKSection(chk) {}
	
	u32 sectionID()
		{ return CHKSectionSTR::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
	
	CHKString get_string(u16 stringID);
};
