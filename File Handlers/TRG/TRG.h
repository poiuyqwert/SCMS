//
//  TRG.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-01.
//
//

#pragma once

#include "Types.h"

namespace TRGGroup {
	enum Enum : u8 {
		Player1					= 0,
		Player2					= 1,
		Player3					= 2,
		Player4					= 3,
		Player5					= 4,
		Player6					= 5,
		Player7					= 6,
		Player8					= 7,
		Player9					= 8,
		Player10				= 9,
		Player11				= 10,
		Player12				= 11,
		CurrentPlayer			= 13,
		Foes					= 14,
		Allies					= 15,
		NeutralPlayers			= 16,
		AllPlayers				= 17,
		Force1					= 18,
		Force2					= 19,
		Force3					= 20,
		Force4					= 21,
		NonAlliedVictoryPlayers	= 26
	};
}
namespace TRGUnitType {
	enum Enum : u8 {
		None		= 228,
		AnyUnit		= 229,
		Men			= 230,
		Buildings	= 231,
		Factories	= 232
	};
}
namespace TRGComparison {
	enum Enum : u8 {
		AtLeast	= 0,
		AtMost	= 1,
		Exactly	= 10
	};
}
namespace TRGSwitchState {
	enum Enum : u8 {
		Set		= 2,
		Clear	= 3
	};
}
namespace TRGResourceType {
	enum Enum : u8 {
		Ore			= 0,
		Gas			= 1,
		OreAndGas	= 2
	};
}
namespace TRGScoreType {
	enum Enum : u8 {
		Total				= 0,
		Units				= 1,
		Buildings			= 2,
		UnitsAndBuildings	= 3,
		Kills				= 4,
		Razings				= 5,
		KillsAndRazings		= 6,
		Custom				= 7
	};
}
namespace TRGAllianceStats {
	enum Enum : u8 {
		Enemy			= 0,
		Ally			= 1,
		AlliedVictory	= 2
	};
}
namespace TRGSwitchAction {
	enum Enum : u8 {
		Set			= 4,
		Clear		= 5,
		Toggle		= 6,
		Randomize	= 11
	};
}
namespace TRGLeaderboardAction {
	enum Enum : u8 {
		Set			= 4,
		Clear		= 5,
		Toggle		= 6
	};
}
namespace TRGUnitOrder {
	enum Enum : u8 {
		Move	= 0,
		Patrol	= 1,
		Attack	= 2
	};
}
namespace TRGModifier {
	enum Enum : u8 {
		Set			= 7,
		Add			= 8,
		Subtract	= 9
	};
}

namespace TRGConditionID {
	enum Enum : u8 {
		NoCondition,
		CountdownTimer,
		Command,
		Bring,
		Accumulate,
		Kill,
		CommandTheMost,
		CommandTheMostAt,
		MostKills,
		HighestScore,
		MostResources,
		Switch,
		ElapsedTime,
		MissionBriefing,
		Opponents,
		Deaths,
		CommandTheLeast,
		CommandTheLeastAt,
		LeastKills,
		LowestScore,
		LeastResources,
		Score,
		Always,
		Never
	};
}
namespace TRGConditionFlags {
	enum Enum : u8 {
		Disabled			= (1<<1),
		AlwaysDisplay		= (1<<2),
		UnitPropertiesUsed	= (1<<3),
		UnitTypeUsed		= (1<<4),
		UnitIDUsed			= (1<<5),
	};
}

namespace TRGActionID {
	enum Enum : u8 {
		NoAction,
		Victory,
		Defeat,
		PreserveTrigger,
		Wait,
		PauseGame,
		UnpauseGame,
		Transmission,
		PlayWAV,
		DisplayTextMessage,
		CenterView,
		CreateUnitWithProperties,
		SetMissionObjectives,
		SetSwitch,
		SetCountdownTimer,
		RunAIScript,
		RunAIScriptAtLocation,
		LeaderBoardControl,
		LeaderBoardControlAtLocation,
		LeaderBoardResources,
		LeaderBoardKills,
		LeaderBoardPoints,
		KillUnit,
		KillUnitAtLocation,
		RemoveUnit,
		RemoveUnitAtLocation,
		SetResources,
		SetScore,
		MinimapPing,
		TalkingPortrait,
		MuteUnitSpeech,
		UnmuteUnitSpeech,
		LeaderboardComputerPlayers,
		LeaderboardGoalControl,
		LeaderboardGoalControlAtLocation,
		LeaderboardGoalResources,
		LeaderboardGoalKills,
		LeaderboardGoalPoints,
		MoveLocation,
		MoveUnit,
		LeaderboardGreed,
		SetNextScenarioText,
		SetDoodadState,
		SetInvincibility,
		CreateUnit,
		SetDeaths,
		Order,
		Comment,
		GiveUnitsToPlayer,
		ModifyUnitHitPoints,
		ModifyUnitEnergy,
		ModifyUnitShieldPoints,
		ModifyUnitResourceAmount,
		ModifyUnitHangerCount,
		PauseTimer,
		UnpauseTimer,
		Draw,
		SetAllianceStatus,
		DisableDebugMode,
		EnableDebugMode
	};
}
namespace MBRFActionID {
	enum Enum : u8 {
		NoAction,
		Wait,
		PlayWAV,
		TextMessage,
		MissionObjectives,
		ShowPortrait,
		HidePortrait,
		DisplaySpeakingPortrait,
		Transmission,
		SkipTutorialEnabled
	};
}
namespace TRGActionFlags {
	enum Enum : u8 {
		IgnoreWatOnce		= (1<<0),
		Disabled			= (1<<1),
		AlwaysDisplay		= (1<<2),
		UnitPropertiesUsed	= (1<<3),
		UnitTypeUsed		= (1<<4),
		UnitIDUsed			= (1<<5),
	};
}

namespace TRGExecutionFlags {
	enum Enum : u8 {
		AllConditionsMet	= (1<<0),
		IgnoreGameEnd		= (1<<1),
		PreserveTrigger		= (1<<2),
		Ignore				= (1<<3),
		IgnoreDelays		= (1<<4),
		IgnorePause			= (1<<5),
		WaitSkippDisabled	= (1<<6)
	};
}

#pragma pack(push, 1)
struct TRGCondition {
	u32 locationID;
	u32 group;
	u32 amount;
	u16 unitID;
	union {
		u8 comparison;
		u8 switchState;
	};
	u8 conditionID;
	union {
		u8 resourceType;
		u8 scoreType;
		u8 switchID;
	};
	u8 flags;
	u16 unused;
};
struct TRGAction {
	u32 locationID;
	u32 textStringID;
	u32 wavStringID;
	u32 time;
	union {
		u32 playerID;
		u32 slotID;
	};
	union {
		union {
			u32 playerID;
			u32 locationID;
		} destination;
		u32 unitPropsID;
		u32 amount;
		u32 aiscriptID;
		u32 switchID;
	};
	union {
		u16 unitType;
		u16 scoreType;
		u16 resourceType;
		u16 allianceStatus;
	};
	u8 actionID;
	union {
		u8 unitAmount;
		u8 switchAction;
		u8 leaderboardAction;
		u8 unitOrder;
		u8 amountModifier;
	};
	u8 flags;
	u8 unused[3];
};
struct TRGExecution {
	u32 flags;
	u8 executes[28];
};
struct TRGTrigger {
	TRGCondition conditions[16];
	TRGAction actions[64];
	TRGExecution execution;
};
#pragma pack(pop)
