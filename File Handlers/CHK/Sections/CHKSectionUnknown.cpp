//
//  CHKSectionUnknown.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-04.
//
//

#include "CHKSectionUnknown.h"

#include <string>


void CHKSectionUnknown::load_data(const u8 *data, u32 size) {
	this->data = new u8[size];
	memcpy(this->data, data, size);
	this->size = size;
}

u8* CHKSectionUnknown::save_data(u32 &size) {
	size = this->size;
	u8 *buffer = new u8[size];
	memcpy(this->data, buffer, size);
	return buffer;
}
