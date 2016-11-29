/*
 *  Lexer.cpp
 *  SCMS
 *
 *  Created by poiuy_qwert on 20/07/09.
 *
 */

#include "Lexer.h"

void computenvalue(TOKEN *token) {
	token->nValue = 0;
	if (token->type == TOKEN_TYPE::BINARY)
		compileflags(&token->nValue, token->size, token->text);
	else if (token->type == TOKEN_TYPE::OCTAL)
		sscanf(token->text, "%o", &token->nValue);
	else if (token->type == TOKEN_TYPE::DECIMAL)
		sscanf(token->text, "%d", &token->nValue);
	else if (token->type == TOKEN_TYPE::HEXADECIMAL)
		sscanf(token->text, "%x", &token->nValue);
	//error
}

TOKEN next_token(char **buffer, int &size, bool eol) {
	if (buffer == NULL || *buffer == NULL || **buffer == '\x00') {
		TOKEN eof;
		memset(&eof, 0, sizeof(TOKEN));
		eof.type = TOKEN_TYPE::ENDOFFILE;
		return eof;
	}
	char *cur = *buffer;
	char strtype = '\0';
	while (*cur == ' ' || *cur == '\t' || (eol != true && (*cur == '\n' || *cur == '\r')))
		cur++;
	int offset = 0;
	TOKEN token;
	memset(&token, 0, sizeof(TOKEN));
	char *text = new char[size];
	token.size = 0;
	if (eol) {
		token.type = TOKEN_TYPE::OTHER;
	} else if ((*cur >= 'A' && *cur <= 'Z') || (*cur >= 'a' && *cur <= 'z')) {
		token.type = TOKEN_TYPE::IDENTIFIER;
	} else if ((*cur >= '0' && *cur <= '9') || *cur == '-' || *cur == '+') {
		if (*cur == '-' || *cur == '+') {
			text[token.size] = *cur;
			token.size++;
			(*cur)++;
			offset++;
		}
		if (*cur == '0' && (*(cur+1) == 'b' || *(cur+1) == 'o' || *(cur+1) == 'd' || *(cur+1) == 'x')) {
			if (*(cur+1) == 'b')
				token.type = TOKEN_TYPE::BINARY;
			else if (*(cur+1) == 'o')
				token.type = TOKEN_TYPE::OCTAL;
			else if (*(cur+1) == 'd')
				token.type = TOKEN_TYPE::DECIMAL;
			else
				token.type = TOKEN_TYPE::HEXADECIMAL;
			cur += 2;
			offset += 2;
		} else {
			token.type = TOKEN_TYPE::DECIMAL;
		}
	} else if (*cur == '\'' || *cur == '"') {
		strtype = *cur;
		token.type = TOKEN_TYPE::STRING;
		cur++;
	} else {
		token.type = TOKEN_TYPE::OTHER;
		token.text = new char[2];
		token.text[0] = *cur;
		token.text[1] = '\x00';
		*buffer = cur + 1;
		return token;
	}
	bool escape = false;
	text[token.size] = *cur;
	token.size++;
	for (cur++; *cur; cur++) {
		if (eol && (*cur == '\n' || *cur == '\r'))
			break;
		if (token.type == TOKEN_TYPE::IDENTIFIER && (*cur != '_' && (*cur < 'A' || *cur > 'Z') && (*cur < 'a' || *cur > 'z') && (*cur < '0' || *cur > '9')))
			break;
		if (token.type == TOKEN_TYPE::BINARY && *cur != '0' && *cur != '1')
			break;
		if (token.type == TOKEN_TYPE::OCTAL && (*cur < '0' || *cur > '7'))
			break;
		if (token.type == TOKEN_TYPE::DECIMAL && (*cur < '0' || *cur > '9'))
			break;
		if (token.type == TOKEN_TYPE::HEXADECIMAL && (*cur < '0' || *cur > '9') && (*cur < 'A' || *cur > 'F') && (*cur < 'a' || *cur > 'f'))
			break;
		if (token.type == TOKEN_TYPE::STRING) {
			if (*cur == strtype && !escape) {
				(*cur)++;
				break;
			} else if (escape) {
				escape = false;
				if (*cur == 't' || *cur == 'r' || *cur == 'n' || *cur == '\\') {
					if (*cur == 't')
						text[token.size] = '\t';
					else if (*cur == 'r')
						text[token.size] = '\r';
					else if (*cur == 'n')
						text[token.size] = '\n';
					else
						text[token.size] = '\\';
					token.size++;
					continue;
				}
			} else if (*cur == '\\') {
				escape = true;
				continue;
			}
		}
		text[token.size] = *cur;
		token.size++;
	}
	token.text = new char[token.size+1];
	memcpy(token.text, text, token.size);
	token.text[token.size] = '\x00';
	if (token.type >= TOKEN_TYPE::BINARY)
		computenvalue(&token);
	*buffer = cur;
	size -= token.size;
	return token;
}