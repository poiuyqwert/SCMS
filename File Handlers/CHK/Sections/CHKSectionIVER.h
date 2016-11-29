//
//  CHKSectionIVER.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionIVER : public CHKSection {
	u16 version;
public:
	static const u32 ID = L('IVER');
	static const CHKRequirements Requirements;
	
	enum : u16 {
		Beta	= 9,
		Release	= 10
	};
	
	CHKSectionIVER(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionIVER::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
