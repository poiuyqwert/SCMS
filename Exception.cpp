/*
 *  Exception.cpp
 *  SCMS
 *
 *  Created by poiuy_qwert on 08/07/09.
 *
 */

#include "Exception.h"

SCMSError::SCMSError(const char *type, const char *msg, ... ) {
	va_list args;
	va_start(args, msg);
	char tmp[strlen(msg)+1000];
	int len = vsprintf(tmp, msg, args);
	char *buffer = new char[len+1];
	memcpy(buffer, tmp, len);
	this->errorMessage = buffer;
	va_end(args);
	this->errorType = type;
	this->fileName = "";
	this->lineNumber = 0;
}

SCMSError::SCMSError(const char *file, int line, const char *type, const char *msg, ... ) {
	va_list args;
	va_start(args, msg);
	char tmp[strlen(msg)+1000];
	int len = vsprintf(tmp, msg, args);
	char *buffer = new char[len+1];
	memcpy(buffer, tmp, len);
	this->errorMessage = buffer;
	va_end(args);
	this->fileName = file;
	this->lineNumber = line;
	this->errorType = type;
}

void SCMSError::set_type(const char *type) {
	this->errorType = type;
}