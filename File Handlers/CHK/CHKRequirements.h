//
//  CHKRequirements.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#pragma once

#include "Types.h"


namespace CHKGameMode {
	enum Enum : u8 {
		None			= 0,
		
		Melee			= (1<<0),
		UseMapSettings	= (1<<1),
		
		All				= (Melee | UseMapSettings)
	};
}

namespace CHKVer {
	enum Enum : u8 {
		None				= 0,
		
		Vanilla				= (1<<0),
		Hybrid				= (1<<1),
		Broodwar			= (1<<2),
		VanillaHybrid		= (Vanilla | Hybrid),
		BroodwarHybrid		= (Broodwar | Hybrid),
		
		All					= (Vanilla | Hybrid | Broodwar)
	};
}

class CHK;

class CHKRequirements {
	CHKVer::Enum vers;
	CHKGameMode::Enum modes;
public:
	CHKRequirements(CHKVer::Enum vers = CHKVer::All, CHKGameMode::Enum modes = CHKGameMode::All)
		: vers(vers),modes(modes) {}
	
	bool is_required(CHK *chk) const;
};