/*
 *  AIBIN.cpp
 *  SCMS
 *
 *  Created by poiuy_qwert on 04/08/09.
 *
 */

#include "AIBIN.h"

AIByteCode AIByteCodeHandler;
const char *flowEndings = "\x24\x27\x39\x41";

AIByteCode::AIByteCode() {
	this->blockType = this->add_type("BLOCK", TYPE_SIZES::USHORT);
	this->stringType = this->add_type("STRING", TYPE_SIZES::STRING);
	this->byteType = this->add_type("BYTE", TYPE_SIZES::UCHAR);
	this->wordType = this->add_type("WORD", TYPE_SIZES::USHORT, this->byteType);
	int building = this->add_type("BUILDING", TYPE_SIZES::USHORT, this->byteType);
	int gg_military = this->add_type("GG_MILITARY", TYPE_SIZES::USHORT, this->byteType);
	int ag_military = this->add_type("AG_MILITARY", TYPE_SIZES::USHORT, this->byteType);
	int ga_military = this->add_type("GA_MILITARY", TYPE_SIZES::USHORT, this->byteType);
	int aa_military = this->add_type("AA_MILITARY", TYPE_SIZES::USHORT, this->byteType);
	int military = this->add_type("MILITARY", TYPE_SIZES::USHORT, this->byteType);// | gg_military | ag_military | ga_military | aa_military);
	int all_military = (military | gg_military | ag_military | ga_military | aa_military);
	this->add_type_accepts(gg_military, all_military);
	this->add_type_accepts(ag_military, all_military);
	this->add_type_accepts(ga_military, all_military);
	this->add_type_accepts(aa_military, all_military);
	this->add_type_accepts(military, all_military);
	this->add_type("UNIT", TYPE_SIZES::USHORT, this->byteType | building | all_military);
	this->add_type("UPGRADE", TYPE_SIZES::USHORT, this->byteType);
	this->add_type("TECHNOLOGY", TYPE_SIZES::USHORT, this->byteType);
	this->open_definition("AIdef.txt");
}

string AIByteCode::decompile_value(VALUE *value, TYPE_SIZES::Enum type,  VariableHandler *variables, void *data) {
	AIBIN *ai = (AIBIN*)data;
	if (value->tid == this->blockType && ai->get_block(value->value.num))
		return ai->get_block(value->value.num)->name;
	return ByteCodeHandler::decompile_value(value, type, variables, data);
}

VALUE* AIByteCode::interpret_token(TOKEN token, unsigned int tid, VariableHandler *variables, void *data) {
	AIBIN *ai = (AIBIN*)data;
	VALUE* val = NULL;
	if (token.type == TOKEN_TYPE::IDENTIFIER) {
		string name(token.text);
		if (tid == this->blockType) {
			val = new VALUE;
			val->tid = this->blockType;
			val->value.num = ai->get_block(name)->id;
		} else {
			val = variables->get_value(name);
		}
	} else if (token.type == TOKEN_TYPE::STRING) {
		val = new VALUE;
		val->tid = this->stringType;
		val->str = true;
		val->value.str = new string(token.text);
	} else if (token.type >= TOKEN_TYPE::BINARY) {
		val = new VALUE;
		if (token.nValue > 255 || token.nValue < -127)
			val->tid = this->wordType;
		else
			val->tid = this->byteType;
		val->str = false;
		val->value.num = token.nValue;
	}
	if (val == NULL) {
		SCMSError err("Interpreting", "Unexpected token '%s' (expected a '%s' paramater)", token.text, this->get_typename(tid).c_str());
		throw err;
	}
	if (!(val->tid & this->get_typeinfo(tid)->accepts)) {
		if (token.type != TOKEN_TYPE::IDENTIFIER)
			delete val;
		SCMSError err("Interpreting", "Type missmatch (expected a '%s' parameter but got a '%s' value)", this->get_typename(tid).c_str(), this->get_typename(val->tid).c_str());
		throw err;
	}
	val->tid = tid;
	return val;
}

int AIByteCode::get_blockType() {
	return this->blockType;
}

void AIBIN::open_file(const char *filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Open", "Could not open file '%s'", filename);
		throw err;
	}
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.seekg(0);
	u8 buffer[size];
	file.read((char *)buffer, size);
	file.close();
	try {
		this->open_data(buffer, size);
	} catch (exception) {
		throw;
	}
}

unsigned short load_block(char *buffer, int size, unsigned long offset, long scriptId, unsigned short &blockId, map<unsigned long,AI_SCRIPT*> *scripts, map<unsigned short,AI_BLOCK*> *blocks, map<unsigned short,unsigned short> *idMap) {
	unsigned short id = blockId++;
	AI_BLOCK *block = new AI_BLOCK;
	block->id = id;
	block->code = NULL;
	block->offset = 0;
	block->length = 0;
	strprintf(&block->name, "%.4s_%04i", &scriptId, id);
	block->references.insert(scriptId);
	(*scripts)[scriptId]->blocks.insert(block);
	(*blocks)[id] = block;
	(*idMap)[offset] = id;
	for (map<unsigned short,unsigned short>::iterator o = idMap->begin(); o != idMap->end(); o++) {
		unsigned short otherOffset = (*o).first;
		if (offset > otherOffset) {
			AI_BLOCK *other = (*blocks)[(*o).second];
			if (offset < otherOffset+other->length) {
//				printf("\t\tinside %s (%d < %ld < %ld)\n", other->name.c_str(), otherOffset, offset, otherOffset+other->length);
				block->length = (otherOffset+other->length) - offset;
//				other->length = other->length - block->length;
				return id;
			}
		}
	}
	char *cur = buffer + offset;
//	printf("\t\tstartload offset:%ld id:%d\n", (long)cur, id);
	bool processed = false;
	while (((unsigned long)cur - (unsigned long)buffer) < size) {
		unsigned char cmd = *cur;
		COMMAND_DEF* def = AIByteCodeHandler.get_command(cmd);
//		printf("\t\t\tcmd %d (%d)", cmd, (int)cur);
//		printf(" : %s\n", AIByteCodeHandler.get_cmdname(cmd).c_str());
		block->length++;
		cur++;
		if (def != NULL) {
			int repeat = 1;
			for (int p = 0; p < def->params; p++) {
				TYPE_SIZES::Enum type = AIByteCodeHandler.get_typeinfo(AIByteCodeHandler.get_typeid(def, p))->size;
//				printf("\t\t\t\tp %s (%d - %d)\n", AIByteCodeHandler.get_typename(AIByteCodeHandler.get_typeid(def, p)).c_str(), abs(type), (int)cur);
				if (type == TYPE_SIZES::STRING) {
					while (repeat--) {
						int len = strlen(cur)+1;
						block->length += len;
						cur += len;
					}
					repeat = 1;
				} else {
					int bytes = abs(type);
					if (p || def->size) {
						while (repeat--) {
							block->length += bytes;
							if (def->types[p] == AIByteCodeHandler.get_blockType() && !processed) { // ADDRESS
								unsigned short subId = blockId;
								unsigned long param = AIByteCodeHandler.get_int(cur, type);
								if (idMap->count(param)) {
									subId = (*idMap)[param];
//									printf("\t\thave2 offset:%ld id:%d\n", (long)(buffer+param), subId);
								} else {
//									printf("\t\tload2 param:%ld offset:%ld id:%d\n", param, (long)(buffer+param), blockId);
									subId = load_block(buffer, size, param, scriptId, blockId, scripts, blocks, idMap);
//									printf("\t\tloaded2 param:%ld offset:%ld id:%d\n", param, (long)(buffer+param), subId);
								}
								AIByteCodeHandler.set_int(cur, subId, type);
								(*blocks)[subId]->references.insert(scriptId);
							}
							cur += bytes;
						}
						repeat = 1;
					} else if (!def->size) {
						block->length += bytes;
						repeat = AIByteCodeHandler.get_int(cur, type);
						cur += bytes;
					}
				}
			}
			if (strchr(flowEndings, cmd))
				break;
		}
		if (!processed) {
			processed = idMap->count((unsigned long)cur - (unsigned long)buffer);
		}
	}
	//block->length = (int)cur - (int)buffer - offset;
	return id;
}

void AIBIN::open_data(const u8 *buffer, int size) {
	unsigned long idtable;
	try {
		unpack(buffer, size, "<L", &idtable);
	} catch (SCMSError) {
		SCMSError err("Open", "Invalid aiscript.bin");
		throw err;
	}
	if (size < idtable+20) {
		SCMSError err("Open", "Invalid aiscript.bin");
		throw err;
	}
	long *entries = (long*)(buffer+idtable);
	long codeSize = (long)entries-(long)buffer;
	//int(*strcmp_ptr)(const char*,const char*) = strcmp;
	unsigned short blockNum = 0;
	map<unsigned long,AI_SCRIPT*> scripts;
	map<unsigned short,AI_BLOCK*> blocks;
	map<unsigned short,unsigned short> idMap;
	//map<char*,char*> findjumps;
	while (*entries != 0) {
		AI_SCRIPT* aiinfo = new AI_SCRIPT;
		unsigned long id, loc;
		unpack((u8 *)entries, 16, "<4L", &id, &loc, &aiinfo->string, &aiinfo->flags);
//		printf("%.4s %lu %lu %lu\n", (char *)&id, loc, aiinfo->string, aiinfo->flags);
		aiinfo->string--;
		if (!scripts.count(id)) {
			scripts[id] = aiinfo;
			if (loc == 0) {
				aiinfo->block = NULL;
				aiinfo->broodwar = true;
			} else {
				aiinfo->broodwar = false;
				unsigned short num = blockNum;
				if (!idMap.count(loc)) {
//					printf("\tload1 offset:%ld id:%d\n", (long)(buffer+loc), blockNum);
					num = load_block((char*)buffer, codeSize, loc, id, blockNum, &scripts, &blocks, &idMap);
//					printf("\tloaded1 offset:%ld id:%d\n", (long)(buffer+loc), num);
				} else {
					num = idMap[loc];
//					printf("\thave offset:%ld id:%d\n", (long)(buffer+loc), num);
				}
				aiinfo->block = blocks[num];
			}
		} else {
			delete aiinfo;
		}
		entries += 4;
	}
	list<unsigned short> offsets;
	map<char*,AI_BLOCK*> codeblocks;
	for (map<unsigned short,unsigned short>::iterator o = idMap.begin(); o != idMap.end(); o++) {
		offsets.push_back((*o).first);
	}
	offsets.sort();
	for (list<unsigned short>::iterator n = offsets.begin(),f; n != offsets.end();) {
		unsigned short offset = *n;
		int length = 0;
		f = n;
		while (f != offsets.end() && *f <= offset+length) {
			unsigned short id = idMap[*f];
			if (*f+blocks[id]->length > offset+length)
				length += (*f+blocks[id]->length)-(offset+length);
			f++;
		}
		char *code = new char[length];
		memcpy(code, buffer+offset, length);
		while (n != offsets.end() && *n <= offset+length) {
			unsigned short id = idMap[*n];
			blocks[id]->code = code;
			blocks[id]->offset = *n-offset;
			codeblocks[code+*n-offset] = blocks[id];
			n++;
		}
	}
	this->scripts = scripts;
	this->idBlocks = blocks;
	this->codeBlocks = codeblocks;
}

void AIBIN::decompile_block(string *code, AI_BLOCK *block, set<AI_BLOCK*> *done, bool start) {
	done->insert(block);
	char *cur = block->code;
	cur += block->offset;// ^....( \d+ \d+ \d+)$
	set<AI_BLOCK*> next;// set 1170483
	while (true) {
		if (this->codeBlocks.count(cur) && (this->codeBlocks[cur] != block || !start)) {
			strprintf(code, "\n:%s\n", this->codeBlocks[cur]->name.c_str());
			done->insert(this->codeBlocks[cur]);
		}
		unsigned char cmd = *cur;
		COMMAND_DEF* def = AIByteCodeHandler.get_command(cmd);
//		printf("\t\t\tcmd %d (%d)", cmd, (int)cur);
//		printf(" : %s\n", AIByteCodeHandler.get_cmdname(cmd).c_str());
		cur++;
		if (def != NULL) {
			strprintf(code, "\t%s(", AIByteCodeHandler.get_cmdname(cmd).c_str());
			int repeat = 1;
			for (int p = 0; p < def->params; p++) {
				if (p)
					*code += ", ";
				TYPE_SIZES::Enum type = AIByteCodeHandler.get_typeinfo(AIByteCodeHandler.get_typeid(def, p))->size;
//				printf("\t\t\t\tp %s (%d - %d)\n", AIByteCodeHandler.get_typename(AIByteCodeHandler.get_typeid(def, p)).c_str(), abs(type), (int)cur);
				if (def->types[p] == AIByteCodeHandler.get_blockType()) {
					unsigned short id = AIByteCodeHandler.get_int(cur, type);
//					printf("\t\t\t\tNext: %d\n", id);
					next.insert(this->idBlocks[id]);
				}
				while (repeat--)
					*code += AIByteCodeHandler.decompile_param(&cur, def, p, this->variables, (void*)this);
				if (!p && !def->size)
					repeat = AIByteCodeHandler.get_int(cur, type);
				else
					repeat = 1;
			}
			*code += ")\n";
			if (strchr(flowEndings, cmd) || cmd == 2) {
				*code += "\n";
				if (cmd != 2)
					break;
			}
		}
	}
	for (set<AI_BLOCK*>::iterator b = next.begin(); b != next.end(); b++) {
		if (*b == NULL) {
			printf("\t\t\t\tnot found\n");
			printf("%s", code->c_str());
			//continue;
		}
		if (!done->count(*b)) {
//			printf("\t\t\t\twtf\n");
//			printf("\t\t\t\tdecomp %p\n", *b);
			decompile_block(code, *b, done, false);
		}
	}
}

void AIBIN::export_file(const char *filename) {
	ofstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Save", "Could not open file '%s'", filename);
		throw err;
	}
	int size;
	char *buffer = this->export_data(size);
	file.write(buffer, size);
	delete [] buffer;
	file.close();
}

void AIBIN::export_file(const char *filename, set<unsigned long> &ids) {
	ofstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Save", "Could not open file '%s'", filename);
		throw err;
	}
	int size;
	char *buffer = this->export_data(size, ids);
	file.write(buffer, size);
	delete [] buffer;
	file.close();
}

char* AIBIN::export_data(int &size) {
	set<unsigned long> ids;
	for (map<unsigned long,AI_SCRIPT*>::iterator i = this->scripts.begin(); i != this->scripts.end(); i++)
		ids.insert((*i).first); 
	return this->export_data(size, ids);
}	

char* AIBIN::export_data(int &size, set<unsigned long> &ids) {
	string code;
	set<AI_BLOCK*> done;
	for (set<unsigned long>::iterator i = ids.begin(); i != ids.end(); i++) {
		AI_SCRIPT *script = this->scripts[*i];
		if (script->block != NULL) {
		#warning REMOVE INLINE IF
			strprintf(&code, "# stat_txt.tbl entry %i: %s\n:%.4s(%i, 0b%.3s, %.2sscript)\n", script->string, this->strings->get_string((script->string > 5000 ? 1522 : script->string)).c_str(), &(*i), script->string, decompileflags(&script->flags, 3), (script->block != NULL) ? "ai" : "bw");
//			printf("%.4s\n", (char *)&(*i));
			this->decompile_block(&code, script->block, &done, true);
		}
	}
	size = code.size();
	char *buffer = new char[size];
	memcpy(buffer, code.c_str(), size);
	return buffer;
}	

void AIBIN::save_file(const char *filename) {
	ofstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Save", "Could not open file '%s'", filename);
		throw err;
	}
	int size;
	u8 *buffer = this->save_data(size);
	file.write((char *)buffer, size);
	delete [] buffer;
	file.close();	
}

void AIBIN::import_file(const char *filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Open", "Could not open file '%s'", filename);
		throw err;
	}
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.seekg(0);
	char buffer[size];
	file.read(buffer, size);
	file.close();
	this->import_data(buffer, size);
}

void add_code(AI_BLOCK *block, char **curCode, int &codeSize, char *code, int size) {
	if (block->length+size > codeSize) {
		codeSize *= 2;
		char *newCode = new char[codeSize];
		memcpy(newCode, *curCode, block->length);
		*curCode = newCode+block->length;
	}
	memcpy(*curCode, code, size);
	*curCode += size;
	block->length += size;
}

void AIBIN::import_data(char *data, int size) {
	long scriptId = 0;
	map<unsigned short,AI_BLOCK *> blocks;
	AI_SCRIPT *script = NULL;
	AI_BLOCK *block = NULL;
	int curSize = size, codeSize = 64;
	char *cur = data, *code = NULL, *curCode = NULL;
	for (TOKEN token = next_token(&cur, curSize); (token.type == TOKEN_TYPE::IDENTIFIER || token.type == TOKEN_TYPE::OTHER); token = next_token(&cur, curSize)) {
		while (token.type == TOKEN_TYPE::OTHER) {
			if (*token.text == '#') {
				next_token(&cur, size, true);
				token = next_token(&cur, size);
			} else if (*token.text == ':') {
				break;
			} else {
				SCMSError err("Import", "Unexpected token '%s' expected SOMETHING", token.text);
				throw err;
			}
		}
		if (token.type == TOKEN_TYPE::OTHER && *token.text == ':') {
			if (*(cur+4) == '(') {
				scriptId = *(long *)cur;
				cur += 5;
				size -= 5;
				token = next_token(&cur, size);
				if (token.type != TOKEN_TYPE::DECIMAL) {
					SCMSError err("Import", "Unexpected token '%s' expected SOMETHING", token.text);
					throw err;
				}
				long stringId = token.nValue;
				token = next_token(&cur, size);
				if (token.type != TOKEN_TYPE::OTHER || *token.text != ',') {
					SCMSError err("Import", "Unexpected token '%s' expected SOMETHING", token.text);
					throw err;
				}
				token = next_token(&cur, size);
				if (token.type != TOKEN_TYPE::BINARY || token.size != 3) {
					SCMSError err("Import", "Unexpected token '%s' expected SOMETHING", token.text);
					throw err;
				}
				long flags = token.nValue;
				token = next_token(&cur, size);
				if (token.type != TOKEN_TYPE::OTHER || *token.text != ',') {
					SCMSError err("Import", "Unexpected token '%s' expected SOMETHING", token.text);
					throw err;
				}
				token = next_token(&cur, size);
				if (token.type != TOKEN_TYPE::IDENTIFIER) {
					SCMSError err("Import", "Unexpected token '%s' expected SOMETHING", token.text);
					throw err;
				}
				bool bw = false;
				if (!memcmp(token.text, "bwscript", 8)) {
					bw = true;
				} else if (memcmp(token.text, "aiscript", 8)) {
					SCMSError err("Import", "Unexpected token '%s' expected SOMETHING", token.text);
					throw err;
				}
				token = next_token(&cur, size);
				if (token.type != TOKEN_TYPE::OTHER || *token.text != ')') {
					SCMSError err("Import", "Unexpected token '%s' expected SOMETHING", token.text);
					throw err;
				}
				script = new AI_SCRIPT;
				block = new AI_BLOCK;
				codeSize = 64;
				code = new char[codeSize];
				curCode = code;
				block->code = code;
				block->offset = 0;
				block->length = 0;
				strprintf(&block->name, "%.4s", &scriptId);
				script->block = block;
				script->string = stringId;
				script->flags = flags;
				script->broodwar = bw;
			} else {
				token = next_token(&cur, size);
				if (token.type != TOKEN_TYPE::IDENTIFIER) {
					SCMSError err("Import", "Unexpected token '%s' expected SOMETHING", token.text);
					throw err;
				}
				block = new AI_BLOCK;
				
			}
		} else if (token.type == TOKEN_TYPE::IDENTIFIER) {
			unsigned char cmd = 0;
			try {
				string str = token.text;
				cmd = AIByteCodeHandler.get_cid(str);
			} catch (exception) {
				SCMSError err("Import", "Unexpected token '%s' expected a command", token.text);
				throw err;
			}
			token = next_token(&cur, size);
			if (token.type != TOKEN_TYPE::OTHER || *token.text != '(') {
				SCMSError err("Import", "Unexpected token '%s' expected SOMETHING", token.text);
				throw err;
			}
			COMMAND_DEF *def = AIByteCodeHandler.get_command(cmd);
			add_code(block, &curCode, codeSize, (char *)&cmd, 1);
			for (int p = 0; p < def->params; p++) {
				int tid = AIByteCodeHandler.get_typeid(def, p);
				VALUE *value = AIByteCodeHandler.interpret_token(next_token(&cur, size), tid, this->variables, this);
				if (value->str) {
				} else {
					char val[4] = "\x00\x00\x00";
					TYPE_SIZES::Enum type = AIByteCodeHandler.get_typeinfo(tid)->size;
					AIByteCodeHandler.set_int(val, value->value.num, type);
					add_code(block, &curCode, codeSize, val, abs(type));
				}
				if (p+1 < def->params) {
					token = next_token(&cur, size);
					if (token.type != TOKEN_TYPE::OTHER || *token.text != ',') {
						SCMSError err("Import", "Unexpected token '%s' expected SOMETHING", token.text);
						throw err;
					}
				}
			}
			token = next_token(&cur, size);
			if (token.type != TOKEN_TYPE::OTHER || *token.text != ')') {
				SCMSError err("Import", "Unexpected token '%s' expected SOMETHING", token.text);
				throw err;
			}
		}
	}
}

u8* AIBIN::save_data(int &size) {
	return NULL;
}

AI_BLOCK* AIBIN::get_block(int bid) {
	if (!this->idBlocks.count(bid)) {
#warning SWITCH TO RETURN NULL AND ADD ERROR WHERE USED
		SCMSError err("Internal", "Invalid Block ID '%i'", bid);
		throw err;
	}
	return this->idBlocks[bid];
}

AI_BLOCK* AIBIN::get_block(string name) {
	for (map<unsigned short,AI_BLOCK*>::iterator iter = this->idBlocks.begin(); iter != this->idBlocks.end(); iter++) {
		AI_BLOCK *block = iter->second;
		if (block->name.compare(name) == 0) {
			return block;
		}
	}
	return NULL;
}

void AIBIN::close() {
}