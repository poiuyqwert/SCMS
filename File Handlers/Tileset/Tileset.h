//
//  Tileset.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-01.
//
//

#pragma once

#include "Images.h"

#include <vector>

using namespace std;


#pragma pack(push, 1)
struct CV5Group {
	u16 index;
	union {
		struct {
			struct {
				u8 flags : 4;
				u8 buildable : 4;
			} info1;
			struct {
				u8 groundHeight : 4;
				u8 buildable2 : 4;
			} info2;
			struct {
				u16 left;
				u16 top;
				u16 right;
				u16 bottom;
			} edge;
			u16 unk1;
			u16 hasUp;
			u16 unk2;
			u16 hasDown;
		} tile;
		struct {
			struct {
				u8 unk1 : 4;
				u8 buildable : 4;
			} info1;
			struct {
				u8 groundHeight : 4;
				u8 overlayFlags : 4;
			} info2;
			u16 overlayID;
			u16 unk2;
			u16 groupStringID;
			u16 unk3;
			u16 dddataID;
			u16 width;
			u16 height;
			u16 unk4;
		} doodad;
	};
	u16 megatiles[16];
};
#pragma pack(pop)
class CV5 {
	vector<CV5Group> tileGroups;
	vector<CV5Group> doodadGroups;
public:
	CV5() {}
	CV5(const char *filename)
		{ this->open_file(filename); }
	CV5(const u8 *buffer, int size)
		{ this->open_data(buffer, size); }
	
	static bool isDoodadGroup(int group);
	
	void open_file(const char *filename);
	void open_data(const u8 *buffer, int size);
	void save_file(const char *filename);
	u8* save_data(int &size);
	
	CV5Group get_group(int group);
};

#pragma pack(push, 1)
struct VF4Group {
	u16 flags[16];
};
#pragma pack(pop)
class VF4 {
	vector<VF4Group> groups;
public:
	VF4() {}
	VF4(const char *filename)
		{ this->open_file(filename); }
	VF4(const u8 *buffer, int size)
		{ this->open_data(buffer, size); }
	
	void open_file(const char *filename);
	void open_data(const u8 *buffer, int size);
	void save_file(const char *filename);
	u8* save_data(int &size);
};

#pragma pack(push, 1)
struct VX4MinitileRef {
	u16 flipped : 1;
	u16 minitile : 15;
};
struct VX4Megatile {
	VX4MinitileRef minitiles[16];
};
#pragma pack(pop)
class VX4 {
	vector<VX4Megatile> megatiles;
public:
	VX4() {}
	VX4(const char *filename)
		{ this->open_file(filename); }
	VX4(const u8 *buffer, int size)
		{ this->open_data(buffer, size); }
	
	void open_file(const char *filename);
	void open_data(const u8 *buffer, int size);
	void save_file(const char *filename);
	u8* save_data(int &size);

	VX4Megatile get_megatile(int n);
};

#pragma pack(push, 1)
struct VR4Minitile {
	u8 pixels[8][8];
};
#pragma pack(pop)
class VR4 {
	vector<VR4Minitile> minitiles;
public:
	VR4() {}
	VR4(const char *filename)
		{ this->open_file(filename); }
	VR4(const u8 *buffer, int size)
		{ this->open_data(buffer, size); }
	
	void open_file(const char *filename);
	void open_data(const u8 *buffer, int size);
	void save_file(const char *filename);
	u8* save_data(int &size);
	
	VR4Minitile get_minitile(int n);
};

#pragma pack(push, 1)
struct DDDataPlaceability {
	u16 groupIDs[256];
};
#pragma pack(pop)
class DDData {
	vector<DDDataPlaceability> placeability;
public:
	DDData() {}
	DDData(const char *filename)
		{ this->open_file(filename); }
	DDData(const u8 *buffer, int size)
		{ this->open_data(buffer, size); }
	
	void open_file(const char *filename);
	void open_data(const u8 *buffer, int size);
	void save_file(const char *filename);
	u8* save_data(int &size);
};

class Palette;

struct Tileset {
	CV5 *cv5;
	VF4 *vf4;
	VX4 *vx4;
	VR4 *vr4;
	DDData *dddata;
	Palette *wpe;

	Tileset()
		: cv5(NULL),vf4(NULL),vx4(NULL),vr4(NULL),dddata(NULL),wpe(NULL) {}
	Tileset(CV5 *cv5, VF4 *vf4, VX4 *vx4, VR4 *vr4, DDData *dddata, Palette *wpe)
		: cv5(cv5),vf4(vf4),vx4(vx4),vr4(vr4),dddata(dddata),wpe(wpe) {}
	
	Pixels get_minitile(unsigned int minitile, bool flipped = false);
	Pixels get_megatile(unsigned int megatile);
};
