/*
 *  main.cpp
 *  SCMS
 *
 *  Created by poiuy_qwert on 06/07/09.
 *
 */

#include "PCX.h"
#include "FNT.h"
#include "Palette.h"
#include "BMP.h"
#include "ByteCodeHandler.h"
#include "AIBIN.h"
#include "TBL.h"
#include "GRP.h"
#include "Tileset.h"
#include "CHK.h"
#include "CHKSectionSPRP.h"
#include "CHKSectionSTR.h"
#include "CHKSectionMRGN.h"
#include "CHKSectionDIM.h"
#include "CHKSectionMTXM.h"
#include "Exception.h"
#include "Logging.h"

#include <SFmpqapi.h>

#include <fstream>
#include <cstring>
#include <math.h>

#include "UnitsDAT.h"

int main(int argc, char * const argv[]) {
	SCMSLog.set("stdeo.txt");
//	FNT *fnt = new FNT("font16.fnt");
//	PCX *pcx = new PCX("tfontgam.pcx", true);
//	BMP *bmp = new BMP(pcx->get_pixels(), pcx->get_palette());
//	bmp->save_file("tfontgam.bmp");
//
//	Palette *pal = pcx->get_palette(0);
//	RGB color = {50,100,50};
//	pal->set_color(0, color);
//	bmp = new BMP();
//	bmp->set_palette(pal);
//	char filename[9];
//	filename[8] = 0;
//	for (int i = fnt->get_low(); i < fnt->get_low()+fnt->get_chars(); i++) {
//		bmp->set_pixels(fnt->get_letter(i));
//		sprintf(filename, "f%03u.bmp", i);
//		bmp->save_file(filename);
//	}
//	fnt->export_file("font16.bmp", pal);
//
//	TBL *tbl = new TBL("stat_txt.tbl");
//	VariableHandler *vars = new VariableHandler(&AIByteCodeHandler);
//	vars->open_definition("unitdef.txt");
//	AIBIN ai(tbl, vars);
//	ai.open_file("aiscript.bin");
////	set<unsigned long> ids;
////	char id[5] = "Ter3";
////	ids.insert(*(unsigned long*)id);
//	ai.export_file("test.txt");
//
////	AIBIN ai2(tbl, vars);
////	ai2.import_file("test.txt");
//
//	pal->open_file("Units.pal");
//	bmp->set_palette(pal);
////	for (int f = 0; f < grp->get_frames(); f++) {
////		bmp->set_pixels(grp->get_frame(f));
////		sprintf(filename, "u%03u.bmp", f);
////		bmp->save_file(filename);
////	}
//	PCX *tunit = new PCX("tunit.pcx");
//	RLE_NORMAL_CONTEXT context;
//	context.tunit = tunit->get_pixels();
//	GRP *grp = new GRP("marine.grp");
//	u32 groups = ceil(grp->get_frames() / 17.0);
//	u32 wide = min((u32)17,(u32)grp->get_frames());
//	Size<u16> size = grp->get_size();
//	Pixels marine({wide*size.width,groups*size.height});
//	for (int g = 0; g < groups; g++) {
//		s32 y = g * size.height;
//		wide = min(17,grp->get_frames()-17*g);
//		for (int f = 0; f < wide; f++) {
//			s32 x = f * size.width;
//			context.player = (SC::Player::ENUM)f;
//			grp->draw_frame(g*17+f, {x,y}, marine, RLE_NORMAL_FUNC, &context);
//		}
//	}
//	bmp->set_pixels(marine);
//	bmp->save_file("marine_raw.bmp");
//
//	CV5 *cv5 = new CV5("badlands.cv5");
//	VF4 *vf4 = new VF4("badlands.vf4");
//	VX4 *vx4 = new VX4("badlands.vx4");
//	VR4 *vr4 = new VR4("badlands.vr4");
//	DDData *dddata = new DDData("dddata.bin");
//	Palette *wpe = new Palette("badlands.wpe");
//
//	Tileset tileset(cv5, vf4, vx4, vr4, dddata, wpe);
//	CV5Group creep = tileset.cv5->get_group(1);
//	bmp->set_palette(wpe);
//	bmp->set_pixels(tileset.get_megatile(creep.megatiles[0]));
//	bmp->save_file("creep.bmp");
//	Pixels group({32*16,32});
//	for (s32 m = 0; m < 16; m++) {
//		Pixels mega = tileset.get_megatile(creep.megatiles[m]);
//		group.paste(mega, {32*m, 0});
//	}
//	bmp->set_pixels(group);
//	bmp->save_file("group.bmp");
//
	CHK *chk = new CHK();
	chk->open_file("scenario.chk");
//
//	CHKSectionSPRP *sprp = chk->get_section<CHKSectionSPRP>();
//	CHKSectionSTR *str = chk->get_section<CHKSectionSTR>();
//	printf("%s\n", str->get_string(sprp->get_scenarioName()).string);
//	printf("%s\n", str->get_string(sprp->get_scenarioDescription()).string);
//	CHKSectionMRGN *mrgn = chk->get_section<CHKSectionMRGN>();
//	for (int i = 0; i < 255; i++) {
//		CHKLocation location = mrgn->get_location(i);
//		if (location.stringID) {
//			printf("%s\n", str->get_string(location.stringID-1).string);
//		}
//	}
//
//	CHKSectionDIM *dim = chk->get_section<CHKSectionDIM>();
//	CHKSectionMTXM *mtxm = chk->get_section<CHKSectionMTXM>();
//
//	Pixels map({(u32)dim->get_width()*32, (u32)dim->get_height()*32});
//	for (u32 y = 0; y < dim->get_height(); y++) {
//		s32 py = y * 32;
//		for (u32 x = 0; x < dim->get_width(); x++) {
//			s32 px = x * 32;
//			CHKTile tile = mtxm->get_tile(x, y);
//			CV5Group group = tileset.cv5->get_group(tile.megatileGroup);
//			Pixels megatile = tileset.get_megatile(group.megatiles[tile.megatile]);
//			map.paste(megatile, {px, py});
//		}
//	}
//	bmp->set_pixels(map);
//	bmp->save_file("map.bmp");
	
//	UnitsDAT *units = new UnitsDAT("units.dat");

    return 0;
}
