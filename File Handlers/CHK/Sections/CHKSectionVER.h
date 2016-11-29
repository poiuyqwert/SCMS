//
//  CHKSectionVER.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionVER : public CHKSection {
	u16 version;
public:
	static const u32 ID = L('VER ');;
	
	enum : u16 {
		Beta		= 57,
		SC100		= 59,
		SC104		= 63,
		BroodWar	= 205
	};
	
	CHKSectionVER(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionVER::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
	
	u16 get_version()
		{ return this->version; }
};
