//
//  UnitsDAT.cpp
//  SCMS
//
//  Created by Zach Zahos on 2018-02-13.
//

#include "UnitsDAT.h"
#include "Exception.h"

#include <fstream>


using namespace std;

void UnitsDAT::open_file(const char *filename) {
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

void UnitsDAT::open_data(const u8 *buffer, int size) {
	if (size != sizeof(UnitsDAT)) {
		SCMSError err("Open", "Invalid units.dat (size is %d, expected %d)", size, sizeof(UnitsDAT));
		throw err;
	}
	memcpy(this, buffer, sizeof(UnitsDAT));
}


void UnitsDAT::save_file(const char *filename) {
	ofstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Save", "Could not open file '%s'", filename);
		throw err;
	}
	int size;
	u8 *buffer = this->save_data(size);
	file.write((char *)buffer, size);
	delete [] buffer;
	file.close();
}

u8* UnitsDAT::save_data(int &size) {
	size = sizeof(UnitsDAT);
	u8 *buffer = new u8[size];
	memcpy(buffer, this, size);
	return buffer;
}
