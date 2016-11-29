/*
 *  ByteCodeHandler.cpp
 *  SCMS
 *
 *  Created by poiuy_qwert on 13/08/09.
 *
 */

#include "ByteCodeHandler.h"

void VariableHandler::open_definition(const char *filename) {
	this->clear_globals();
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Internal", "Could not open variable definition file '%s'", filename);
		throw err;
	}
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.seekg(0);
	char *buffer = new char[size],*cur = buffer;
	file.read(buffer, size);
	file.close();
	for (TOKEN token = next_token(&cur, size); (token.type == TOKEN_TYPE::IDENTIFIER || token.type == TOKEN_TYPE::OTHER); token = next_token(&cur, size)) {
		while (token.type == TOKEN_TYPE::OTHER) {
			if (*token.text == '#') {
				token = next_token(&cur, size, true);
				token = next_token(&cur, size);
			} else {
				SCMSError err("Internal", "Unexpected token '%s' (expected a variable decleration) in variable definition file '%s'", token.text, filename);
				throw err;
			}
		}
		string type(token.text);
		int tid = this->byteCodeHandler->get_typeid(type);
		if (!tid) {
			SCMSError err("Internal", "Invalid variable type '%s' in variable definition file '%s'", token.text, filename);
			throw err;
		}
		token = next_token(&cur, size);
		if (token.type != TOKEN_TYPE::IDENTIFIER) {
			SCMSError err("Internal", "Unexpected token '%s' (expected a variable name) in variable definition file '%s'", token.text, filename);
			throw err;
		}
		string name(token.text);
		if (this->variables.count(name)) {
			SCMSError err("Internal", "Duplicate variable name '%s' in variable definition file '%s'", token.text, filename);
			throw err;
		}
		token = next_token(&cur, size);
		if (token.type != TOKEN_TYPE::OTHER || *token.text != '=') {
			SCMSError err("Internal", "Unexpected token '%s' (expected an '=') in variable definition file '%s'", token.text, filename);
			throw err;
		}
		token = next_token(&cur, size);
		VALUE* val = NULL;
		try {
			val = this->byteCodeHandler->interpret_token(token, tid, this, NULL);
		} catch (SCMSError e) {
			e.set_type("Internal");
			throw e;
		}
		this->add_global(name, val);
	}
}

void VariableHandler::add_global(string &name, VALUE *value) {
	this->variables[name] = value;
	if (value->str)
		this->stringValues.insert(pair<string,string>(*value->value.str,name));
	else
		this->numValues.insert(pair<int,string>(value->value.num,name));
}

//void VariableHandler::add_local(string &name, string &value);
//void VariableHandler::add_local(string &name, int value);
void VariableHandler::clear_globals() {
	for (map<string,VALUE*>::iterator v = this->variables.begin(); v != this->variables.end(); v++) {
		if (!this->locals.count((*v).first)) {
			if ((*v).second->str) 
				this->stringValues.erase(*(*v).second->value.str);
			else
				this->numValues.erase((*v).second->value.num);
			delete (*v).second;
			this->variables.erase(v);
		}
	}
}

VALUE* VariableHandler::get_value(string &name) {
	if (!this->variables.count(name))
		return NULL;
	return this->variables[name];
}

string VariableHandler::get_name(VALUE *value) {
	if (value->str) {
		if (this->stringValues.count(*value->value.str)) {
			pair<multimap<string,string>::iterator,multimap<string,string>::iterator> range = this->stringValues.equal_range(*value->value.str);
			for (multimap<string,string>::iterator v = range.first; v != range.second; v++) {
				if (this->variables[(*v).second]->tid & this->byteCodeHandler->get_typeinfo(value->tid)->accepts)
					return (*v).second;
			}
		}
		SCMSError err("Internal", "There is no variable with value '%s'", value->value.str->c_str());
		throw err;
	} else {
		if (this->numValues.count(value->value.num)) {
			pair<multimap<int,string>::iterator,multimap<int,string>::iterator> range = this->numValues.equal_range(value->value.num);
			for (multimap<int,string>::iterator v = range.first; v != range.second; v++) {
				if (this->variables[(*v).second]->tid & this->byteCodeHandler->get_typeinfo(value->tid)->accepts) {
					return (*v).second;
				}
			}
		}
		SCMSError err("Internal", "There is no variable with value '%i'", value->value.num);
		throw err;
	}
}

#include <cerrno>

void ByteCodeHandler::open_definition(const char* filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		perror(strerror(errno));
		SCMSError err("Internal", "Could not open byte code definition file '%s'", filename);
		throw err;
	}
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.seekg(0);
	char *buffer = new char[size],*cur = buffer;
	file.read(buffer, size);
	file.close();
	for (TOKEN token = next_token(&cur, size); token.type == TOKEN_TYPE::IDENTIFIER; token = next_token(&cur, size)) {
		string name(token.text);
		if (this->commandNames.count(name)) {
			SCMSError err("Internal", "Duplicate command '%s' in byte code definition file '%s'", token.text, filename);
			throw err;
		}
		token = next_token(&cur, size);
		if (token.type != TOKEN_TYPE::OTHER || *token.text != '(') {
			SCMSError err("Internal", "Unexpected token '%s' (expected a '(') in byte code definition file '%s'", token.text, filename);
			throw err;
		}
		COMMAND_DEF *def = new COMMAND_DEF;
		memset(def, 0, sizeof(COMMAND_DEF));
		vector<unsigned int> params;
		token = next_token(&cur, size);
		bool repeat = false;
		if (token.type == TOKEN_TYPE::OTHER && *token.text == '*') {
			repeat = true;
			token = next_token(&cur, size);
		} else {
			def->size = 1;
		}
		for (; token.type == TOKEN_TYPE::IDENTIFIER; token = next_token(&cur, size)) {
			string paramtype(token.text);
			if (!this->typeNames.count(paramtype)) {
				SCMSError err("Internal", "Invalid type '%s' in byte code definition file '%s'", token.text, filename);
				throw err;
			}
			def->params += 1;
			if (!repeat)
				def->size += this->types[this->typeNames[paramtype]]->size;
			params.push_back(this->typeNames[paramtype]);
			token = next_token(&cur, size);
			if (token.type == TOKEN_TYPE::OTHER && *(token.text) == ')')
				break;
			if (token.type != TOKEN_TYPE::OTHER || *(token.text) != ',') {
				SCMSError err("Internal", "Unexpected token '%s' (expected a ',' or ')') in byte code definition file '%s'", token.text, filename);
				throw err;
			}
		}
		if (def->params) {
			unsigned int *t = def->types = new unsigned int[def->params];
			for (vector<unsigned int>::iterator param = params.begin(); param != params.end(); param++,t++)
				*t = *param;
		}
		this->commandNames[name] = this->commands.size();
		this->commands.push_back(def);
	}
//	for (unsigned char c = 0; c < this->commands.size(); c++) {
//		printf("%s(", this->get_cmdname(c).c_str());
//		COMMAND_DEF* cmd = this->commands[c];
//		if (cmd->params) {
//			for (int p = 0; p < cmd->params; p++) {
//				if (p)
//					printf(", ");
//				printf(this->get_typename(cmd->types[p]).c_str());
//			}
//		}
//		printf(")\n");
//	}
}

int ByteCodeHandler::add_type(const char *name, TYPE_SIZES::Enum size, int accepts) {
	TYPE_INFO *info = new TYPE_INFO;
	info->size = size;
	info->flag = this->flag;
	info->accepts = accepts | this->flag;
	this->flag <<= 1;
	string str(name);
	this->typeNames[str] = info->flag;
	this->types[info->flag] = info;
	return info->flag;
}

int ByteCodeHandler::add_type_accepts(unsigned int tid, int accepts) {
	TYPE_INFO *info = this->get_typeinfo(tid);
	info->accepts |= accepts;
	return info->accepts;
}

//COMMAND_DEF* ByteCodeHandler::load_command(const char *buffer) {
//	unsigned char cmd = buffer[this->cmdIDOffset];
//	return this->commands[cmd];
//}

unsigned char ByteCodeHandler::get_cid(string name) {
	if (!this->commandNames.count(name)) {
		SCMSError err("Internal", "Invalid command name '%s'", name.data());
		throw err;
	}
	return this->commandNames[name];
}

COMMAND_DEF* ByteCodeHandler::get_command(unsigned char cid) {
	if (cid >= this->commands.size())
		return NULL;
	return this->commands[cid];
}

string ByteCodeHandler::get_cmdname(unsigned char cid) {
	for (map<string,unsigned char>::iterator n = this->commandNames.begin(); n != this->commandNames.end(); n++) {
		if ((*n).second == cid)
			return (*n).first;
	}
	SCMSError err("Internal", "Invalid byte code command ID '%u'", cid);
	throw err;
}

TYPE_INFO* ByteCodeHandler::get_typeinfo(unsigned int tid) {
	// check error
	return this->types[tid];
}

string ByteCodeHandler::get_typename(unsigned int tid) {
	for (map<string,unsigned int>::iterator n = this->typeNames.begin(); n != this->typeNames.end(); n++) {
		if ((*n).second == tid)
			return (*n).first;
	}
	SCMSError err("Internal", "Invalid byte code type ID '%u'", tid);
	throw err;
}

unsigned int ByteCodeHandler::get_typeid(COMMAND_DEF *def, int param) {
	//if (param >= def->params)
	return def->types[param];
}

unsigned int ByteCodeHandler::get_typeid(string name) {
	// check error
	return this->typeNames[name];
}

int ByteCodeHandler::get_int(const char *code, TYPE_SIZES::Enum type) {
	switch (type) {
		case TYPE_SIZES::CHAR:
			return *(char*)code;
		case TYPE_SIZES::UCHAR:
			return *(unsigned char*)code;
		case TYPE_SIZES::SHORT:
			return *(short*)code;
		case TYPE_SIZES::USHORT:
			return *(unsigned short*)code;
		case TYPE_SIZES::LONG:
			return *(long*)code;
		case TYPE_SIZES::ULONG:
			return *(unsigned long*)code;
		default:
			break;
	}
	SCMSError err("Internal", "Invalid byte code type size '%i'", type);
	throw err;
}

void ByteCodeHandler::set_int(char *code, int n, TYPE_SIZES::Enum type) {
//	printf("\t\tset %d = %d (%d)\n", (int)code, n, abs(type));
	switch (type) {
		case TYPE_SIZES::CHAR:
			*(char*)code = (char)n;
			return;
		case TYPE_SIZES::UCHAR:
			*(unsigned char*)code = (unsigned char)n;
			return;
		case TYPE_SIZES::SHORT:
			*(short*)code = (short)n;
			return;
		case TYPE_SIZES::USHORT:
			*(unsigned short*)code = (unsigned short)n;
			return;
		case TYPE_SIZES::LONG:
			*(long*)code = (long)n;
			return;
		case TYPE_SIZES::ULONG:
			*(unsigned long*)code = (unsigned long)n;
			return;
		default:
			break;
	}
	SCMSError err("Internal", "Invalid byte code type size '%i'", type);
	throw err;
}


string ByteCodeHandler::decompile_param(char **code, COMMAND_DEF *def, int param, VariableHandler *variables, void *data) {
	VALUE value;
	memset(&value, 0, sizeof(VALUE));
	value.tid = def->types[param];
	TYPE_SIZES::Enum type = this->types[value.tid]->size;
	if (type == TYPE_SIZES::STRING) {
		value.str = true;
		int size = strlen(*code);
		value.value.str = new string(TBL::decompile_string(*code, size));
		*code += size;
	} else {
		value.value.num = this->get_int(*code, type);
		*code += abs(type);
	}
	string str = this->decompile_value(&value, type, variables, data);
	return str;
}

string ByteCodeHandler::decompile_value(VALUE *value, TYPE_SIZES::Enum type, VariableHandler *variables, void *data) {
	string str;
	try {
		str = variables->get_name(value);
	} catch (SCMSError) {
		if (value->str)
			return *value->value.str;
		if (type > 0)
			strprintf(&str, "%u", value->value.num);
		else
			strprintf(&str, "%i", value->value.num);
	}
	return str;
}

VALUE* ByteCodeHandler::interpret_param(char **code, int size, unsigned int tid, VariableHandler *variables, void *data) {
	TOKEN token = next_token(code, size);
	VALUE* val = this->interpret_token(token, tid, variables, data);
	return val;
}

VALUE* ByteCodeHandler::interpret_token(TOKEN token, unsigned int tid, VariableHandler* variables, void *data) {
	SCMSError err("Internal", "No parameter interpreter defined");
	throw err;
}