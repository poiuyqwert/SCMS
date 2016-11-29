//
//  CHKSectionDIM.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionDIM : public CHKSection {
	struct {
		u16 width;
		u16 height;
	} size;
public:
	static const u32 ID = L('DIM ');
	static const CHKRequirements Requirements;
	
	enum : u16 {
		Tiny	= 64,
		Small	= 96,
		Medium	= 128,
		Large	= 192,
		Huge	= 256
	};
	
	CHKSectionDIM(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionDIM::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
	
	u16 get_width()
		{ return this->size.width; }
	u16 get_height()
		{ return this->size.height; }
};
