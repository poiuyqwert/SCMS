/*
 *  Pack.cpp
 *  SCMS
 *
 *  Created by poiuy_qwert on 08/07/09.
 *
 */

#include "Pack.h"

static char tmp[2] = {1,0};
ENDIAN::Enum OS_ENDIAN = (*(short*)tmp == 1 ? ENDIAN::BIG : ENDIAN::LITTLE);

int lineLength(const char *buffer) {
	if (buffer == NULL) return NULL;
	const char *CR = strchr(buffer,'\r'),*LF = strchr(buffer,'\n');
	if (CR != NULL && (LF == NULL || CR < LF)) return CR-buffer;
	if (LF != NULL && (CR == NULL || LF < CR)) return LF-buffer;
	return strlen(buffer);
}

char* nextLine(const char *buffer, int &len) {
	len = 0;
	if (buffer == NULL) return NULL;
	const char *CR = strchr(buffer,'\r'),*LF = strchr(buffer,'\n');
	if (CR == NULL && LF == NULL) return NULL;
	const char *line = NULL;
	if (CR != NULL && (LF == NULL || CR < LF)) line = CR;
	else if (LF != NULL && (CR == NULL || LF < CR)) line = LF;
	else return NULL;
	do {
		line++;
	} while (*line == '\r' || *line == '\n');
	if (*line == '\x0') return NULL;
	len = lineLength(line);
	return (char*)line;
}

char* decompileflags(void *buffer, int bits) {
	char *flags = new char[bits+1];
	flags[bits] = '\0';
	for (int f = 1; bits--; f<<=1)
		flags[bits] = (*(long*)buffer & f) ? '1' : '0';
	return flags;
}

void compileflags(void *buffer, int bits, char *flags) {
	for (int f = 0; bits--; f<<=1)
		*(long*)buffer += f*(flags[bits]-48);
}

int strprintf(string *str, const char *format, ... ) {
	va_list args;
	va_start(args, format);
	char buffer[1000];
	memset(buffer, 0, sizeof(buffer));
	int size = vsprintf(buffer, format, args);
	*str += buffer;
	va_end(args);
	return size;
}

void reverse(u8 *bytes, int len) {
	if (bytes == NULL)
		return;
	u8 tmp;
	for (int a = len-1, b = 0; a >= len/2; a--, b++) {
		tmp = bytes[a];
		bytes[a] = bytes[b];
		bytes[b] = tmp;
	}
}

int format_size(const char *format, bool group = false) {
	bool ingroup = group;
	int size = 0;
	int len = 1;
	for (; *format != '\x00' && (!group || *format != ']'); format++) {
		if (*format >= '0' && *format <= '9') {
			int scanned;
			sscanf(format, "%u%n", &len, &scanned);
			format += scanned-1;
			continue;
		}
		if (*format == '[') {
			if (ingroup) {
				SCMSError err("Internal","Can not have sub-groups");
				throw err;
			}
			ingroup = true;
		} else if (*format == ']') {
			ingroup = false;
		} else if (*format == 'c' || *format == 'C' || *format == 'x' || *format == 'X') {
			size += 1 * len;
		} else if (*format == 's' || *format =='S') {
			size += 2 * len;
		} else if (*format == 'l' || *format == 'L') {
			size += 4 * len;
		} else if (*format != '<' && *format != '>') {
#warning Error
			throw;
		}
		len = 1;
	}
	return size;
}

void unpack(const u8 *buffer, int size, const char *format, ... ) {
	int len = format_size(format),groups;
	if (size < len) {
		SCMSError err("Internal","Not enough data to unpack (got %u bytes, expected at least %u)",size,len);
		throw err;
	}
	va_list args;
	va_start(args, format);
	ENDIAN::Enum endian = OS_ENDIAN;
	len = 1;
	bool group = false;
	u8 *arg = NULL;
	const char *back = NULL;
	for (; *format != '\x00'; format++) {
		if (*format == '>' || *format == '<') {
			if (*format == '>')
				endian = ENDIAN::LITTLE;
			else
				endian = ENDIAN::BIG;
			continue;
		}
		if (*format >= '0' && *format <= '9') {
			int scanned;
			sscanf(format, "%u%n", &len, &scanned);
			format += scanned-1;
			continue;
		}
		if (!group)
			arg = va_arg(args, u8*);
		if (*format == '[') {
			group = true;
			if (len > 1) {
				groups = len;
				back = format;
			}
		} else if (*format == ']') {
			group = false;
			if (back != NULL) {
				if (groups > 1)
					format = back-1;
				groups -= 1;
				back = NULL;
			}
		} else {
			char bytes = 0;
			if (*format == 'x' || *format == 'X') {
				buffer += len;
				if (group) {
					arg += len;
				}
			} else {
				if (*format == 'c' || *format == 'C') {
					bytes = 1;
				} else if (*format == 's' || *format =='S') {
					bytes = 2;
				} else if (*format == 'l' || *format == 'L') {
					bytes = 4;
				} else {
#warning Error
					throw;
				}
				if (group) {
					memcpy(arg, buffer, len*bytes);
					if (bytes > 1 && endian != OS_ENDIAN) {
						for (int n = 0; n < len; n++)
							reverse(arg+bytes*n, bytes);
					}
					buffer += len*bytes;
					arg += len*bytes;
				} else {
					for (; len > 0; len--) {
						memcpy(arg, buffer, bytes);
						if (bytes > 1 && endian != OS_ENDIAN)
							reverse(arg, bytes);
						buffer += bytes;
						arg = va_arg(args, u8*);
					}
				}
			}
		}
		len = 1;
	}
}

void pack(u8 *buffer, int size, const char *format, ... ) {
	int len = format_size(format),groups;
	if (size < len) {
		SCMSError err("Internal","Not enough buffer space to pack data (got %u bytes, expected %u)",size,len);
		throw err;
	}
	va_list args;
	va_start(args, format);
	ENDIAN::Enum endian = OS_ENDIAN;
	len = 1;
	char *group = NULL;
	const char *back = NULL;
	for (; *format != '\x00'; format++) {
		if (*format == '>' || *format == '<') {
			if (*format == '>')
				endian = ENDIAN::LITTLE;
			else
				endian = ENDIAN::BIG;
			continue;
		}
		if (*format >= '0' && *format <= '9') {
			format += sscanf(format, "%u", &len)-1;
			continue;
		}
		if (*format == '[') {
			group = va_arg(args, char*);
			if (len > 1) {
				groups = len;
				back = format;
			}
		} else if (*format == ']') {
			group = NULL;
			if (back) {
				if (groups > 1)
					format = back-1;
				groups -= 1;
				back = NULL;
			}
		} else {
			char bytes = 1;
			if (*format != 'x' || *format != 'X') {
				if (*format == 'c' || *format == 'C') {
					bytes = 1;
				} else if (*format == 's' || *format =='S') {
					bytes = 2;
				} else if (*format == 'l' || *format == 'L') {
					bytes = 4;
				} else {
#warning Error
					throw;
				}
				if (group != NULL) {
					memcpy(buffer, group, len*bytes);
					if (bytes > 1 && endian != OS_ENDIAN) {
						for (int n = 0; n < len; n++)
							reverse(buffer+bytes*n, bytes);
					}
					group += len*bytes;
				} else {
					for (int n = len; --n>=0;) {
						*(long*)buffer = va_arg(args, long);
						if (bytes > 1 && endian != OS_ENDIAN)
							reverse(buffer, bytes);
					}
				}
			}
			buffer += len*bytes;
		}
		len = 1;
	}
}