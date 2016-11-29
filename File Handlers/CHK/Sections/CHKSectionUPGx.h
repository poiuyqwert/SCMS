//
//  CHKSectionUPGx.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionUPGx : public CHKSection {
#pragma pack(push, 1)
	struct {
		u8 useGlobal[BroodWar::Upgrade::COUNT];
		u8 unused;
		struct {
			struct {
				u16 base[BroodWar::Upgrade::COUNT];
				u16 upgrade[BroodWar::Upgrade::COUNT];
			} minerals;
			struct {
				u16 base[BroodWar::Upgrade::COUNT];
				u16 upgrade[BroodWar::Upgrade::COUNT];
			} gas;
			struct {
				u16 base[BroodWar::Upgrade::COUNT];
				u16 upgrade[BroodWar::Upgrade::COUNT];
			} buildTime;
		} cost;
	} upgrade;
#pragma pack(pop)
public:
	static const u32 ID = L('UPG ');
	static const CHKRequirements Requirements;
	
	CHKSectionUPGx(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionUPGx::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
