//
//  CHKSectionSTR.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionSTR.h"

CHKString CHKStringNULL = {0};

const CHKRequirements CHKSectionSTR::Requirements = {CHKVer::All, CHKGameMode::All};
void CHKSectionSTR::load_data(const u8 *data, u32 size) {
	u16 strings = *(u16 *)data;
	CHKString str;
	for (u16 i = 0; i < strings; i++) {
		u16 offset = *((u16 *)data + i + 1);
		const u8 *chars = data + offset;
		str.length = strlen((char *)chars);
		int len = str.length+1;
		str.string = new u8[len];
		memcpy(str.string, chars, len);
		this->strings[i] = str;
	}
}
u8* CHKSectionSTR::save_data(u32 &size) {
	size = sizeof(u16);
	for (auto iter = this->strings.begin(); iter != this->strings.end(); iter++) {
		size += iter->second.length+1 + sizeof(u16);
	}
	u8 *buffer = new u8[size];
	*(u16 *)buffer = this->strings.size();
	u16 *offset = (u16 *)buffer + 1;
	u8 *chars = buffer + sizeof(u16) * (this->strings.size() + 1);
	for (auto iter = this->strings.begin(); iter != this->strings.end(); iter++) {
		*offset = chars-buffer;
		int len = iter->second.length + 1;
		memcpy(chars, iter->second.string, len);
		chars += len;
	}
	return buffer;
}

CHKString CHKSectionSTR::get_string(u16 stringID) {
	if (this->strings.count(stringID)) {
		return this->strings[stringID];
	}
	return CHKStringNULL;
}
