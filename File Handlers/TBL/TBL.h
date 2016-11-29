/*
 *  TBL.h
 *  SCMS
 *
 *  Created by poiuy_qwert on 06/07/09.
 *
 */

#pragma once

#include "Exception.h"
#include "Types.h"
#include "Pack.h"

#include <vector>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

class TBL {
	vector<string> strings;
public:
	TBL() {}
	TBL(vector<string> strs)
		{ this->strings.assign(strs.begin(),strs.end()); }
	TBL(const char *filename)
		{ this->open_file(filename); }
	TBL(const u8 *buffer, int size)
		{ this->open_data(buffer, size); }

	static char* decompile_string(const char *str, int &len, const char *include = "\x1\x2\x3\x4\x5\x6\x7\x8\x9\xA\xB\xC\xD\xE\xF\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1F\x3C\x3D");
	static char* compile_string(const char *str, int &len);

	void open_file(const char *filename);
	void open_data(const u8 *buffer, int size);
	void save_file(const char *filename);
	u8* save_data(int &size);

	int get_strings()
		{ return this->strings.size(); }
	string get_string(int n);
	void set_string(int n, string string);
};