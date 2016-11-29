//
//  CHKSectionUPGS.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"
#include "BroodWar.h"

class CHKSectionUPGS : public CHKSection {
#pragma pack(push, 1)
	struct {
		u8 useGlobal[StarCraft::Upgrade::COUNT];
		struct {
			struct {
				u16 base[StarCraft::Upgrade::COUNT];
				u16 upgrade[StarCraft::Upgrade::COUNT];
			} minerals;
			struct {
				u16 base[StarCraft::Upgrade::COUNT];
				u16 upgrade[StarCraft::Upgrade::COUNT];
			} gas;
			struct {
				u16 base[StarCraft::Upgrade::COUNT];
				u16 upgrade[StarCraft::Upgrade::COUNT];
			} buildTime;
		} cost;
	} upgrade;
#pragma pack(pop)
public:
	static const u32 ID = L('UPGS');
	static const CHKRequirements Requirements;
	
	CHKSectionUPGS(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionUPGS::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
