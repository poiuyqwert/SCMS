//
//  Tileset.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-01.
//
//

#include "Tileset.h"
#include "Exception.h"
#include "Pack.h"

#include <fstream>

bool CV5::isDoodadGroup(int group) {
	return (group > 1024);
}
void CV5::open_file(const char *filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Open", "Could not open file '%s'", filename);
		throw err;
	}
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.seekg(0);
	u8 buffer[size];
	file.read((char *)buffer, size);
	file.close();
	try {
		this->open_data(buffer, size);
	} catch (exception) {
		throw;
	}
}
void CV5::open_data(const u8 *buffer, int size) {
	if (size < sizeof(CV5Group) || size % sizeof(CV5Group)) {
		SCMSError err("Open", "Invalid CV5 file");
		throw err;
	}
	const u8 *cur = buffer, *end = buffer + size;
	int i = 0;
	CV5Group group;
	while (cur < end) {
		unpack(cur, end-cur, "<[SCC24S]", &group);
		if (i < 1024) {
			this->tileGroups.push_back(group);
		} else {
			this->doodadGroups.push_back(group);
		}
		cur += sizeof(CV5Group);
		i++;
	}
}
CV5Group CV5::get_group(int group) {
	if (CV5::isDoodadGroup(group)) {
		group -= 1024;
		if (group < 0 || group > this->doodadGroups.size()) {
			SCMSError err("Internal", "Doodad Group index out of range (got %u, expected number in range 0-%u)", group+1024, this->doodadGroups.size()+1024);
			throw err;
		}
		return this->doodadGroups[group];
	} else {
		if (group < 0 || group > this->tileGroups.size()) {
			SCMSError err("Internal", "Tile Group index out of range (got %u, expected number in range 0-%u)", group, this->tileGroups.size());
			throw err;
		}
		return this->tileGroups[group];
	}
}

void VF4::open_file(const char *filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Open", "Could not open file '%s'", filename);
		throw err;
	}
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.seekg(0);
	u8 buffer[size];
	file.read((char *)buffer, size);
	file.close();
	try {
		this->open_data(buffer, size);
	} catch (exception) {
		throw;
	}
}
void VF4::open_data(const u8 *buffer, int size) {
	if (size < sizeof(VF4Group) || size % sizeof(VF4Group)) {
		SCMSError err("Open", "Invalid VF4 file");
		throw err;
	}
	const u8 *cur = buffer, *end = buffer + size;
	VF4Group group;
	while (cur < end) {
		unpack(cur, end-cur, "<[16S]", &group);
		this->groups.push_back(group);
		cur += sizeof(VF4Group);
	}
}

void VX4::open_file(const char *filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Open", "Could not open file '%s'", filename);
		throw err;
	}
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.seekg(0);
	u8 buffer[size];
	file.read((char *)buffer, size);
	file.close();
	try {
		this->open_data(buffer, size);
	} catch (exception) {
		throw;
	}
}
void VX4::open_data(const u8 *buffer, int size) {
	if (size < sizeof(VX4Megatile) || size % sizeof(VX4Megatile)) {
		SCMSError err("Open", "Invalid VX4 file");
		throw err;
	}
	const u8 *cur = buffer, *end = buffer + size;
	VX4Megatile group;
	while (cur < end) {
		unpack(cur, end-cur, "<[16S]", &group);
		this->megatiles.push_back(group);
		cur += sizeof(VX4Megatile);
	}
}
VX4Megatile VX4::get_megatile(int n) {
	if (n < 0 || n > this->megatiles.size()) {
		SCMSError err("Internal", "Megatile index out of range (got %u, expected number in range 0-%u)", n, this->megatiles.size());
		throw err;
	}
	return this->megatiles[n];
}

void VR4::open_file(const char *filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Open", "Could not open file '%s'", filename);
		throw err;
	}
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.seekg(0);
	u8 buffer[size];
	file.read((char *)buffer, size);
	file.close();
	try {
		this->open_data(buffer, size);
	} catch (exception) {
		throw;
	}
}
void VR4::open_data(const u8 *buffer, int size) {
	if (size < sizeof(VR4Minitile) || size % sizeof(VR4Minitile)) {
		SCMSError err("Open", "Invalid VR4 file");
		throw err;
	}
	const u8 *cur = buffer, *end = buffer + size;
	VR4Minitile minitile;
	while (cur < end) {
		unpack(cur, end-cur, "<[64C]", &minitile);
		this->minitiles.push_back(minitile);
		cur += sizeof(VR4Minitile);
	}
}
VR4Minitile VR4::get_minitile(int n) {
	if (n < 0 || n > this->minitiles.size()) {
		SCMSError err("Internal", "Minitile index out of range (got %u, expected number in range 0-%u)", n, this->minitiles.size());
		throw err;
	}
	return this->minitiles[n];
}

void DDData::open_file(const char *filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Open", "Could not open file '%s'", filename);
		throw err;
	}
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.seekg(0);
	u8 buffer[size];
	file.read((char *)buffer, size);
	file.close();
	try {
		this->open_data(buffer, size);
	} catch (exception) {
		throw;
	}
}
void DDData::open_data(const u8 *buffer, int size) {
	if (size < sizeof(DDDataPlaceability) || size % sizeof(DDDataPlaceability)) {
		SCMSError err("Open", "Invalid DDData file");
		throw err;
	}
	const u8 *cur = buffer, *end = buffer + size;
	DDDataPlaceability placeablitity;
	while (cur < end) {
		unpack(cur, end-cur, "<[256S]", &placeablitity);
		this->placeability.push_back(placeablitity);
		cur += sizeof(DDDataPlaceability);
	}
}

Pixels Tileset::get_minitile(unsigned int minitile, bool flipped) {
	Pixels pixels(8,8);
	VR4Minitile tile = this->vr4->get_minitile(minitile);
	if (flipped) {
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				pixels.pixels[y*pixels.width+7-x] = tile.pixels[y][x];
			}
		}
	} else {
		Pixels toPaste((unsigned char *)tile.pixels,8,8);
		pixels.paste(toPaste);
	}
	return pixels;
}

Pixels Tileset::get_megatile(unsigned int megatile) {
	Pixels pixels(32,32);
	VX4Megatile info = this->vx4->get_megatile(megatile);
	for (int m = 0; m < 16; m++) {
		VX4MinitileRef ref = info.minitiles[m];
		Pixels minitile = this->get_minitile(ref.minitile, ref.flipped);
		pixels.paste(minitile, (m%4)*8, (m/4)*8);
		delete minitile.pixels;
	}
	return pixels;
}
