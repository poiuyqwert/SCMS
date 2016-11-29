/*
 *  Error.h
 *  SCMS
 *
 *  Created by poiuy_qwert on 08/07/09.
 *
 */
#pragma once

#include <exception>
#include <fstream>
#include <cstring>
#include <stdarg.h>

using namespace std;

class SCMSError : public exception {
	const char *errorType, *errorMessage, *fileName;
	int lineNumber;
public:
	SCMSError()
		: errorType(""),errorMessage(""),fileName(""),lineNumber(0) {}
	SCMSError(const char *type, const char *msg, ... );
	SCMSError(const char *file, int line, const char *type, const char *msg, ... );

	void set_type(const char *type);

	virtual const char* what() const throw()
		{ return this->errorMessage; }
};