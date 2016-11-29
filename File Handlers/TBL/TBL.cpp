/*
 *  TBL.cpp
 *  SCMS
 *
 *  Created by poiuy_qwert on 06/07/09.
 *
 */

#include "TBL.h"
#include <list>

char* TBL::decompile_string(const char *str, int &len, const char *include) {
	int size = len;
	for (int n = 0; n < len; n++) {
		if (strchr(include, str[n]))
			size += (str[n] < 10) ? 3 : 4;
	}
	char* result = new char[size+1];	
	result[0] = '\0';
	for (int n = 0; n < len; n++) {
		if (strchr(include, str[n])) {
			char ascii[5];
			sprintf(ascii, "<%i>", str[n]);
			strcat(result, ascii);
		} else {
			char chr[2] = "\0";
			chr[0] = str[n];
			strcat(result, chr);
		}
	}
	len = size;
	return result;
}

char* TBL::compile_string(const char *str, int &len) {
	int size = len, ascii = 0, state = 0;
	for (int n = 0; n < len; n++) {
		if (state) {
			if (ascii < 3 && str[n] >= '0' && ((ascii == 1 && str[n] < '3') || (ascii > 1 && str[n] <= '9'))) {
				ascii++;
				continue;
			} else if (str[n] == '>') {
				size -= ascii + 1;
			}
			state = ascii = 0;
		} else if (str[n] == '<') {
			state = ascii = 1;
		}
	}
	state = ascii = 0;
	int pos = 0;
	char tmp[4] = "\0\0\0";
	char* result = new char[size+1];	
	result[size] = '\0';
	for (int n = 0; n < len; n++) {
		if (state) {
			if (ascii < 3 && str[n] >= '0' && ((ascii == 1 && str[n] < '3') || (ascii > 1 && str[n] <= '9'))) {
				tmp[ascii-1] = str[n];
				ascii++;
				continue;
			} else if (str[n] == '>') {
				tmp[ascii] = '\0';
				result[pos] = (char)(atoi(tmp));
				pos++;
			}
			state = ascii = 0;
		} else if (str[n] == '<') {
			state = ascii = 1;
		} else {
			result[pos] = str[n];
			pos++;
		}
	}
	len = size;
	return result;
}

void TBL::open_file(const char *filename) {
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

void TBL::open_data(const u8 *buffer, int size) {
	u16 strs, offset;
	unpack(buffer, 2, "<S", &strs);
	list<u16> offsets;
	for (int n = 0; n < strs; n++)  {
		unpack(&buffer[n*2+2], 2, "<S", &offset);
		if (offset >= size) {
			SCMSError err("Open", "Invalid TBL file");
			throw err;
		}
		offsets.push_front(offset);
	}
	offsets.push_front(size);
	offsets.sort();
	this->strings.clear();
	int len;
	string str;
	for (list<unsigned short>::iterator start = offsets.begin(); start != --(offsets.end()); start++) {
		len = *(++start)-*(--start);
		str.assign((char *)&buffer[*start], len);
		this->strings.push_back(str);
	}
}

void TBL::save_file(const char *filename) {
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

u8* TBL::save_data(int &size) {
	u16 offset = 2+2*this->strings.size();
	size = offset;
	for (vector<string>::iterator str = this->strings.begin(); str != this->strings.end(); str++)
		size += (*str).length();
	u8 *data = new u8[size];
	u8 *cur = data+2;
	pack(data, 2, "<S", this->strings.size());
	for (vector<string>::iterator str = this->strings.begin(); str != this->strings.end(); str++) {
		pack(cur, 2, "<S", offset);
		memcpy(&data[offset], (*str).c_str(), (*str).length() * sizeof(char));
		cur += 2;
		offset += (*str).length();
	}
	return data;
}

string TBL::get_string(int n) {
	if (n < 0 || n >= this->strings.size()) {
		SCMSError err("Internal", "String index out of range (got %u, expected number in range 0-%u)", n, this->strings.size());
		throw err;
	}
	return this->strings[n];
}

void TBL::set_string(int n, string newStr) {
	if (n < 0 || n >= this->strings.size()) {
		SCMSError err("Internal", "String index out of range (got %u, expected number in range 0-%u)", n, this->strings.size());
		throw err;
	}
	this->strings[n] = newStr;
}