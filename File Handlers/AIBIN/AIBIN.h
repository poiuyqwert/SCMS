/*
 *  AIBIN.h
 *  SCMS
 *
 *  Created by poiuy_qwert on 04/08/09.
 *
 */

#pragma once

#include "Exception.h"
#include "Pack.h"
#include "ByteCodeHandler.h"
#include "TBL.h"
#include "Logging.h"

#include <list>
#include <map>
#include <set>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

struct AI_BLOCK {
	unsigned short id;
	char *code;
	long offset, length;
	string name;
	set<unsigned long> references;
};
	
struct AI_SCRIPT {
	AI_BLOCK *block;
	unsigned long string, flags;
	bool broodwar;
	set<AI_BLOCK*> blocks;
};

class AIByteCode: public ByteCodeHandler {
	int blockType, stringType, byteType, wordType;
public:
	AIByteCode();

	virtual string decompile_value(VALUE *value, TYPE_SIZES::Enum type, VariableHandler *variables, void *data);
	virtual VALUE* interpret_token(TOKEN token, unsigned int tid, VariableHandler *variables, void *data);
	
	int get_blockType();
};

extern AIByteCode AIByteCodeHandler;
extern const char *flowEndings;

class BWAIBIN;

class AIBIN {
	BWAIBIN *bwScript;
	TBL *strings;
	unsigned short blockID;
	map<unsigned long, AI_SCRIPT*> scripts;
	map<unsigned short,AI_BLOCK*> idBlocks;
	map<char*,AI_BLOCK*> codeBlocks;
	VariableHandler *variables;

	void decompile_block(string *code, AI_BLOCK *block, set<AI_BLOCK*> *done, bool start);
public:
	AIBIN(TBL *strs, VariableHandler *vars, BWAIBIN *bwai = NULL)
		: strings(strs),variables(vars),bwScript(bwai) {}
	AIBIN(const char *filename, TBL *strs, VariableHandler *vars, BWAIBIN *bwai = NULL)
		: strings(strs),variables(vars),bwScript(bwai)
		{ this->open_file(filename); }
	AIBIN(const u8 *buffer, int size, TBL *strs, VariableHandler *vars, BWAIBIN *bwai = NULL)
		: strings(strs),variables(vars),bwScript(bwai)
		{ this->open_data(buffer, size); }
	~AIBIN()
		{ this->close(); }
	
	void open_file(const char *filename);
	void open_data(const u8 *buffer, int size);
	void export_file(const char *filename);
	void export_file(const char *filename, set<unsigned long> &ids);
	char* export_data(int &size);
	char* export_data(int &size, set<unsigned long> &ids);
	void save_file(const char *filename);
	void import_file(const char *filename);
	void import_data(char *data, int size);
	u8* save_data(int &size);
	AI_BLOCK* get_block(int bid);
	AI_BLOCK* get_block(string name);

	void close();
};