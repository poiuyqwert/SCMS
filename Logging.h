/*
 *  Logging.h
 *  SCMS
 *
 *  Created by poiuy_qwert on 09/07/09.
 *
 */

#pragma once

#include <fstream>
#include <stdarg.h>

using namespace std;

class Logger {
public:
	ofstream *errorFile, *outputFile;
	Logger() {}
	Logger(const char *error, const char *output)
		{ this->set(error, output); }
	Logger(const char *filename)
		{ this->set(filename); }
	~Logger();

	void set(const char *error, const char *output);
	void set(const char *filename);
	void set(ofstream &error, ofstream &output);
	void set(ofstream &file) { this->set(file, file); }
	void error(const char *format, ... );
	void output(const char *format, ... );
	void close();
};

extern Logger SCMSLog;