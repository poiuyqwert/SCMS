//
//  CHKSectionERA.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionERA.h"

const CHKRequirements CHKSectionERA::Requirements = {CHKVer::All, CHKGameMode::All};
const char* CHKSectionERA::TilesetFilenames[COUNT] = {
	"badlands",
	"platform",
	"install",
	"ashworld",
	"jungle",
	"desert",
	"ice",
	"twilight"
};
CHKSectionERA::CHKSectionERA(CHK *chk)
	: CHKSection(chk)
{
	this->tileset = CHKSectionERA::Badlands;
}
void CHKSectionERA::load_data(const u8 *data, u32 size) {
	this->tileset = *(u16 *)data;
}
u8* CHKSectionERA::save_data(u32 &size) {
	size = sizeof(u16);
	u8 *buffer = new u8[size];
	*(u16 *)buffer = this->tileset;
	return buffer;
}
