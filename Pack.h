/*
 *  Pack.h
 *  SCMS
 *
 *  Created by poiuy_qwert on 08/07/09.
 *
 */

#pragma once

#include "Exception.h"
#include "Types.h"

#include <cstdio>
#include <cstring>

using namespace std;

namespace ENDIAN {
	enum Enum {
		BIG,
		LITTLE
	};
};

//static char tmp[2] = {1,0};
extern ENDIAN::Enum OS_ENDIAN;// = *(short*)tmp == 1 ? ENDIAN::BIG : ENDIAN::LITTLE;

int lineLength(const char *buffer);
char* nextLine(const char *buffer, int &len);

char* decompileflags(void *buffer, int bits);
void compileflags(void *buffer, int bits, char *flags);

int strprintf(string *str, const char *format, ... );

void reverse(u8 *bytes, int len);
void unpack(const u8 *buffer, int size, const char *format, ... );
void pack(u8 *buffer, int size, const char *format, ... );