//
//  CHKSection.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "Types.h"
#include "CHKRequirements.h"


class CHK;

class CHKSection {
protected:
	CHK *chk;
public:
	CHKSection(CHK *chk)
		: chk(chk) {}
	
	virtual u32 sectionID() = 0;
	
	virtual void load_data(const u8 *data, u32 size) = 0;
	virtual u8* save_data(u32 &size) = 0;
};
