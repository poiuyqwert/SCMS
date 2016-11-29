/*
 *  Logging.cpp
 *  SCMS
 *
 *  Created by poiuy_qwert on 09/07/09.
 *
 */

#include "Logging.h"

Logger SCMSLog;

Logger::~Logger() {
	this->close();
}

void Logger::set(const char *error, const char *output) {
	ofstream *err = new ofstream(error);
	ofstream *out = new ofstream(output);
	this->set(*err, *out);
}

void Logger::set(const char *fileName) {
	ofstream *file = new ofstream(fileName);
	this->set(*file, *file);
}

void Logger::set(ofstream &error, ofstream &output) {
	this->close();
	this->errorFile = &error;
	this->outputFile = &output;
}

void Logger::error(const char *format, ... ) {
	if (this->errorFile->is_open()) {
		va_list args;
		va_start(args, format);
		char buffer[1000];
		int size = vsprintf(buffer, format, args);
		this->errorFile->write(buffer, size);
		printf("%s", buffer);
		va_end(args);
	}
}

void Logger::output(const char *format, ... ) {
	if (this->outputFile->is_open()) {
		va_list args;
		va_start(args, format);
		char buffer[1000];
		int size = vsprintf(buffer, format, args);
		this->outputFile->write(buffer, size);
		printf("%s", buffer);
		va_end(args);
	}
}

void Logger::close() {
	if (this->errorFile != NULL && this->errorFile->is_open())
		this->errorFile->close();
	if (this->outputFile != NULL && this->outputFile->is_open())
		this->outputFile->close();
}
