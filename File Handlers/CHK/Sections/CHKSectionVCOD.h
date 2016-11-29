//
//  CHKSectionVCOD.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

class CHKSectionVCOD : public CHKSection {
#pragma pack(push, 1)
	struct {
		u8 seed[1024];
		u8 opcodes[16];
	} vcod;
#pragma pack(pop)
public:
	static const u32 ID = L('VCOD');
	static const CHKRequirements Requirements;
	
	static const u8 *defaultSeed;
	static const u8 defaultOpcodes[16];
	
	CHKSectionVCOD(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionVCOD::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
