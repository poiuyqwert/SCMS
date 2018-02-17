//
//  UnitsDAT.h
//  SCMS
//
//  Created by Zach Zahos on 2018-02-13.
//

#pragma once

#include "Types.h"
#include "Geometry.h"

namespace StarEditGroupFlags {
	enum Enum : u8 {
		RaceZerg    = (1 << 0),
		RaceTerran  = (1 << 1),
		RaceProtoss = (1 << 2)
	};
};

#pragma pack(push, 1)
struct UnitsDAT
{
	u8 graphics[228];
	u16 subunit1[228];
	u16 subunit2[228];
	u16 infestation[96]; // ID 106-201 only
	u32 constructionAnimation[228];
	u8 unitDirection[228];
	struct {
		u8 enable[228];
		s16 amount[228];
	} shield;
	s32 hitPoints[228];
	u8 elevationLevel[228];
	u8 unknown[228];
	u8 sublabel[228];
	struct {
		struct {
			u8 comp[228];
			u8 human[228];
		} idle;
		u8 returntoIdle[228];
		struct {
			u8 unit[228];
			u8 move[228];
		} attack;
	} order;
	u8 groundWeapon[228];
	u8 maxGroundHits[228];
	u8 airWeapon[228];
	u8 maxAirHits[228];
	u8 aIInternal[228];
	u32 specialAbilityFlags[228];
	struct {
		u8 targetAcquisition[228];
		u8 sight[228];
	} range;
	u8 armorUpgrade[228];
	u8 sizeClass[228];
	u8 armor[228];
	u8 rightClickAction[228];
	struct {
		u16 ready[106]; // ID 0-105 only
		struct {
			u16 start[228];
			u16 end[228];
		} what;
		struct {
			u16 start[106]; // ID 0-105 only
			u16 end[106]; // ID 0-105 only
		} piss;
		struct {
			u16 start[106]; // ID 0-105 only
			u16 end[106]; // ID 0-105 only
		} yes;
	} sound;
	Size<u16> placeboxSize[228];
	struct {
		u16 horizontal;
		u16 vertical;
	} addonOffset[96]; // ID 106-201 only
	Extents<u16> unitSize[228];
	u16 portrait[228];
	struct {
		u16 mineral[228];
		u16 vespene[228];
	} cost;
	u16 buildTime[228];
	u16 requirementIndex[228];
	u8 starEditGroupFlags[228];
	struct {
		u8 provided[228];
		u8 required[228];
	} supply;
	struct {
		u8 required[228];
		u8 provided[228];
	} space;
	struct {
		u16 build[228];
		u16 destroy[228];
	} score;
	u16 unitMapString[228];
	u8 broodwarUnitFlag[228];
	u16 starEditAvailabilityFlags[228];

	UnitsDAT() {}
	UnitsDAT(const char *filename)
		{ this->open_file(filename); }
	UnitsDAT(const u8 *buffer, int size)
		{ this->open_data(buffer, size); }
	
	void open_file(const char *filename);
	void open_data(const u8 *buffer, int size);
	void save_file(const char *filename);
	u8* save_data(int &size);
};
#pragma pack(pop)

static_assert(sizeof(UnitsDAT) == 19876, "UnitsDAT is not the correct size");
