/*
 *  Palettes.cpp
 *  SCMS
 *
 *  Created by poiuy_qwert on 17/07/09.
 *
 */

#include "Palette.h"

Palette::Palette(RGB *colors, int count, PALETTE_TYPE::Enum type)
	: type(type)
{
	this->colors = new RGB[256];
	memset(this->colors, 0, sizeof(RGB)*256);
	memcpy(this->colors, colors, sizeof(RGB)*count);
}

char* Palette::rgb_to_html(RGB rgb) {
	char *buffer = new char[9];
	sprintf(buffer, "#%02X%02X%02X;", rgb.r, rgb.g, rgb.b);
	return buffer;
}

RGB* Palette::html_to_rgb(char* html) {
	RGB *rgb = new RGB;
	sscanf(html, "#%02X%02X%02X;", (unsigned int *)&rgb->r, (unsigned int *)&rgb->g, (unsigned int *)&rgb->b);
	return rgb;
}

void Palette::open_file(const char *filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Open","Could not open file");
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

void Palette::open_data(const u8 *buffer, int size) {
	for (int n = 0; n < 5; n++) {
		try {
			switch (n) {
				case 0:
					this->open_zsoft_pcx(buffer, size);
					break;
				case 1:
					this->open_riff_pal(buffer, size);
					break;
				case 2:
					this->open_jasc_pal(buffer, size);
					break;
				case 3:
					this->open_sc_wpe(buffer, size);
					break;
				case 4:
					this->open_sc_pal(buffer, size);
			}
			return;
		} catch (SCMSError &err) {
			if (n == 4)
				throw;
		}
	}
}
			
void Palette::open_riff_pal(const u8 *buffer, int size) {
	if (size != 1047 || memcmp(buffer, "RIFF\x0\x0PAL data", 14)) {
		SCMSError err("Open","Invalid RIFF PAL");
		throw err;
	}
	this->close();
	this->colors = new RGB[256];
	memcpy(this->colors, &buffer[24], 768); //Verify format, is it 24 or 14?
	this->type = PALETTE_TYPE::RIFF;
}

void Palette::open_jasc_pal(const u8 *buffer, int size) {
	int len = lineLength((char *)buffer);
	if (len != 8 || memcmp(buffer, "JASC-PAL", 8)) {
		SCMSError err("Open","Invalid JASC PAL");
		throw err;
	}
	char *cur = nextLine((char *)buffer, len);
	if (len != 4 || memcpy(cur, "0100", 4)) {
		SCMSError err("Open","Invalid JASC PAL");
		throw err;
	}
	cur = nextLine(cur, len);
	if (len != 3 || memcpy(cur, "256", 3)) {
		SCMSError err("Open","Invalid JASC PAL");
		throw err;
	}
	RGB *pal = new RGB[256];
	int n = 0;
	for (cur = nextLine(cur, len); cur != NULL; cur = nextLine(cur, len)) {
		if (n == 256) {
			delete [] pal;
			SCMSError err("Open","Invalid JASC PAL");
			throw err;
		}
		unsigned int r, g, b;
		char tmp = cur[len];
		cur[len] = '\x0';
		sscanf(cur, "%u %u %u", &r, &g, &b);
		cur[len] = tmp;
		if (r > 255 || g > 255 || b > 255) {
			delete [] pal;
			SCMSError err("Open","Invalid color in JASC PAL");
			throw err;
		}
		pal[n].r = (u8)r;
		pal[n].g = (u8)g;
		pal[n].b = (u8)b;
	}
	this->close();
	this->colors = pal;
	this->type = PALETTE_TYPE::JASC;
}

void Palette::open_zsoft_pcx(const u8 *buffer, int size) {
	if (memcmp(buffer, "\xA\x5", 2) || buffer[3] != '\x8' || size < 768 || buffer[size-769] != '\xC') {
		SCMSError err("Open","Invalid PCX file");
		throw err;
	}
	this->close();
	this->colors = new RGB[256];
	memcpy(this->colors, &buffer[size-767], 768);
	this->type = PALETTE_TYPE::PCX;
}

void Palette::open_sc_wpe(const u8 *buffer, int size) {
	if (size != 1024) {
		SCMSError err("Open","Invalid palette size");
		throw err;
	}
	this->close();
	this->colors = new RGB[256];
	for (int n = 0; n < 256; n++)
		memcpy(&this->colors[n], buffer+4*n, 3);
	this->type = PALETTE_TYPE::WPE;
}

void Palette::open_sc_pal(const u8 *buffer, int size) {
	if (size != 768) {
		SCMSError err("Open","Invalid palette size");
		throw err;
	}
	this->close();
	this->colors = new RGB[256];
	memcpy(this->colors, buffer, 768);
	this->type = PALETTE_TYPE::SCPAL;
}

void Palette::save_file(const char *filename, PALETTE_TYPE::Enum type) {
	ofstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Save", "Could not open file '%s'", filename);
		throw err;
	}
	int size;
	u8 *buffer = this->save_data(size, type);
	file.write((char *)buffer, size);
	delete [] buffer;
	file.close();
}

u8* Palette::save_data(int &size, PALETTE_TYPE::Enum type) {
	switch (type) {
		case PALETTE_TYPE::RIFF:
			return this->save_riff_pal(size);
		case PALETTE_TYPE::JASC:
			return this->save_jasc_pal(size);
		case PALETTE_TYPE::WPE:
			return this->save_sc_wpe(size);
		case PALETTE_TYPE::SCPAL:
			return this->save_sc_pal(size);
		default:
			break;
	}
	SCMSError err("Save", "SCMS currently can't save PCX files");
	throw err;
}

u8* Palette::save_riff_pal(int &size) {
	u8 *buffer = new u8[1047];
	memcpy(buffer, "RIFF\00\00PAL data", 14);
	memcpy(buffer, this->colors, 768);
	return buffer;
}

u8* Palette::save_jasc_pal(int &size) {
	char tmp[3349];
	memcpy(tmp, "JASC-PAL\r\n0100\r\n256\r\n", 21);
	char *cur = tmp + 21;
	for (int n = 0; n < 256; n++)
		cur += sprintf(cur, "%u %u %u\r\n", this->colors[n].r, this->colors[n].g, this->colors[n].b);
	size = cur-tmp;
	u8 *buffer = new u8[size];
	memcpy(buffer, tmp, size);
	return buffer;
}

u8* Palette::save_sc_wpe(int &size) {
	u8 *buffer = new u8[1024],*cur = buffer;
	for (int n = 0; n < 256; n++) {
		memcpy(cur, &this->colors[n], 3);
		cur += 4;
	}
	size = 1024;
	return buffer;
}
	
u8* Palette::save_sc_pal(int &size) {
	u8 *buffer = new u8[768];
	memcpy(buffer, this->colors, 768);
	size = 768;
	return buffer;
}

RGB Palette::get_color(u8 n) {
	if (n < 0 || n > 255) {
		SCMSError err("Internal", "Color index out of range (got %u, expected number in range 0-255)", n);
		throw err;
	}
	return this->colors[n];
}

void Palette::set_color(u8 n, RGB color) {
	if (n < 0 || n > 255) {
		SCMSError err("Internal", "Color index out of range (got %u, expected number in range 0-255)", n);
		throw err;
	}
	this->colors[n] = color;
}

void Palette::close() {
	if (this->colors != NULL)
		delete [] this->colors;
}
