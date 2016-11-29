//
//  CHKSectionUPRP.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "CHKSection.h"
#include "Types.h"

#pragma pack(push, 1)
struct CHKUnitProperties {
	u16 validAbilities;
	u16 validProperties;
	u8 owner;
	u8 health;
	u8 shields;
	u8 energy;
	u32 resources;
	u16 hangerUnits;
	u16 activeAbilities;
	u32 unused;
	
	enum Ability : u16 {
		Cloak			= (1<<0),
		Burrow			= (1<<1),
		InTransit		= (1<<2),
		Hullucinated	= (1<<3),
		Invincible		= (1<<4)
	};
	enum Property : u16 {
		Owner		= (1<<0),
		Health		= (1<<1),
		Shields		= (1<<2),
		Energy		= (1<<3),
		Resources	= (1<<4),
		Hanger		= (1<<5)
	};
};
#pragma pack(pop)
class CHKSectionUPRP : public CHKSection {
	CHKUnitProperties properties[64];
public:
	static const u32 ID = L('UPRP');
	static const CHKRequirements Requirements;
	
	CHKSectionUPRP(CHK *chk);
	
	u32 sectionID()
		{ return CHKSectionUPRP::ID; }
	
	void load_data(const u8 *data, u32 size);
	u8* save_data(u32 &size);
};
