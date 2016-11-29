/*
 *  Lexer.h
 *  SCMS
 *
 *  Created by poiuy_qwert on 20/07/09.
 *
 */

#pragma once

#include "Pack.h"

#include <fstream>
#include <cstring>

using namespace std;

namespace TOKEN_TYPE {
	enum Enum {
		ENDOFFILE = -1,
		OTHER,
		IDENTIFIER,
		STRING,
		BINARY,
		OCTAL,
		DECIMAL,
		HEXADECIMAL,
	};
};

struct TOKEN {
	TOKEN_TYPE::Enum type;
	char *text;
	unsigned int size;
	int nValue;
	//~TOKEN() { if (this->text != NULL) { delete [] this->text; } }
};

TOKEN next_token(char **buffer, int &size, bool eol = false);