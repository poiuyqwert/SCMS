/*
 *  ByteCodeHandler.h
 *  SCMS
 *
 *  Created by poiuy_qwert on 13/08/09.
 *
 */

#pragma once

#include "Exception.h"
#include "Lexer.h"
#include "Pack.h"
#include "TBL.h"

#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

namespace TYPE_SIZES {
	enum Enum {
		STRING = -5,
		LONG = -4,
		SHORT = -2,
		CHAR = -1,
		UCHAR = 1,
		USHORT = 2,
		ULONG = 4
	};
};

struct TYPE_INFO {
	TYPE_SIZES::Enum size;
	unsigned int flag;
	unsigned int accepts;
};

struct COMMAND_DEF {
	unsigned int size, params, *types;
};

struct VALUE {
	unsigned int tid;
	bool str;
	union {
		int num;
		string *str;
	} value;
};

class ByteCodeHandler;

class VariableHandler {
	map<string,VALUE*> variables;
	set<string> locals;
	multimap<string,string> stringValues;
	multimap<int,string> numValues;
	ByteCodeHandler *byteCodeHandler;
public:
	VariableHandler(ByteCodeHandler *handler) : byteCodeHandler(handler) {}

	void open_definition(const char *filename);
	void add_global(string &name, VALUE *value);
	void add_local(string &name, string &value);
	void add_local(string &name, int value);
	void clear_globals();
	VALUE* get_value(string &name);
	string get_name(VALUE *value);
};

class ByteCodeHandler {
	int flag;
	map<unsigned int,TYPE_INFO*> types;
	map<string,unsigned int> typeNames;
	vector<COMMAND_DEF*> commands;
	map<string,unsigned char> commandNames;
	ENDIAN::Enum endian;
public:
	ByteCodeHandler()
		: endian(ENDIAN::BIG),flag(1) {}
	
	void open_definition(const char *filename);
	int add_type(const char *name, TYPE_SIZES::Enum size, int accepts = 0);
	int add_type_accepts(unsigned int tid, int accepts);
	unsigned char get_cid(string name);
	COMMAND_DEF* get_command(unsigned char cid);
	string get_cmdname(unsigned char cid);
	TYPE_INFO* get_typeinfo(unsigned int tid);
	string get_typename(unsigned int tid);
	unsigned int get_typeid(COMMAND_DEF *def, int param);
	unsigned int get_typeid(string name);
	int get_int(const char *code, TYPE_SIZES::Enum type);
	void set_int(char *code, int n, TYPE_SIZES::Enum type);
	string decompile_param(char **code, COMMAND_DEF *def, int param, VariableHandler *variables, void *data);
	virtual string decompile_value(VALUE *value, TYPE_SIZES::Enum type, VariableHandler *variables, void *data);
	VALUE* interpret_param(char **code, int size, unsigned int tid, VariableHandler *variables, void *data);
	virtual VALUE* interpret_token(TOKEN token, unsigned int tid, VariableHandler *variables, void *data);
};