//
//  PCX.cpp
//  SCMS
//
//  Created by Zach Zahos on 13-03-01.
//
//

#include "PCX.h"
#include "Palette.h"

#include "Logging.h"

#pragma pack(push, 1)
struct PCX_HEADER {
	u32 signature;
	u16 xMin;
	u16 yMin;
	u16 xMax;
	u16 yMax;
	u16 hdpi;
	u16 vdpi;
	u8 unused1[49];
	u8 planes;
	u16 bytesperline;
	u16 palinfo;
	u16 hscreensize;
	u16 vscreensize;
	u8 unused2[54];
};
#pragma pack(pop)

void PCX::open_file(const char *filename, bool specialPalette) {
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
		this->open_data(buffer, size, specialPalette);
	} catch (exception) {
		throw;
	}
}

void PCX::open_data(const u8 *buffer, int size, bool specialPalette) {
	if (size < sizeof(PCX_HEADER)+1+769) {
		SCMSError err("Open", "Not enough data to be a valid PCX");
		throw err;
	}
	if (memcmp(buffer, "\x0A\x05\x01\x08", 4)) {
		SCMSError err("Open", "Invalid PCX file (missing signature)");
		throw err;
	}
	const unsigned char *paletteStart = (const unsigned char*)buffer+(size-769);
	if (*paletteStart != '\x0C') {
		SCMSError err("Open", "Invalid PCX file (missing palette)");
		throw err;
	}
	PCX_HEADER header;
	unpack(buffer, size, "<[L6s49xc4s]", &header);
	if (header.xMax < header.yMin || header.yMax < header.yMin) {
		SCMSError err("Open", "Invalid PCX file (invalid dimensions)");
		throw err;
	}
	if (header.planes != 1) {
		SCMSError err("Open", "Invalid PCX file (unsupported number of planes)");
		throw err;
	}
	int width = header.xMax - header.xMin + 1;
	int height = header.yMax - header.yMin + 1;
	if (header.bytesperline < width) {
		SCMSError err("Open", "Invalid PCX file (not enough data for image)");
		throw err;
	}
	if (specialPalette && (width > 256 || height > 256)) {
		SCMSError err("Open", "Invalid special palette PCX file (invalid dimensions)");
		throw err;
	}
	this->specialPalette = specialPalette;
	this->palette = new Palette((RGB *)(paletteStart+1), 256);
	this->pixels.pixels = new u8[width*height];
	memset(this->pixels.pixels, 0, sizeof(u8)*width*height);
	this->pixels.width = width;
	this->pixels.height = height;
	u8 *pixel = this->pixels.pixels;
	const u8 *cmd = buffer + sizeof(PCX_HEADER);
	while (cmd < paletteStart && pixel-this->pixels.pixels < width*height) {
		u8 c = *cmd;
		cmd++;
		if ((c & 0xC0) == 0xC0 && cmd < paletteStart) {
			int len = (c & 0x3F);
			if (pixel+len-this->pixels.pixels > width*height) {
				len = (this->pixels.pixels+width*height)-pixel;
			}
			memset(pixel, *cmd, len);
			pixel += len;
			cmd++;
		} else {
			*pixel = c;
			pixel++;
		}
	}
}

void PCX::save_file(const char *filename) {
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

u8* PCX::save_data(int &size) {
	return NULL;
//	int len = 0,dataoffset = sizeof(PCX_HEADER)+4+sizeof(PCX_V3_INFO_HEADER)+1024,padwidth = this->width;
//	if (padwidth%4)
//		padwidth += 4-padwidth%4;
//	char *data,*compressed;
//	if (compression == PCX_COMPRESSION::NONE) {
//		size = dataoffset+padwidth*this->height;
//	} else {
//		compressed = (char*)rle8_compress(this->planes, len, this->width, this->height);
//		size = dataoffset+len;
//	}
//	data = new char[size];
//	memset(data, 0, size);
//	PCX_HEADER header = {'B','M', size, 0,0, dataoffset};
//	PCX_V3_INFO_HEADER infoheader = {this->width,this->height, 1,8, compression, size-dataoffset,0,0,0,0};
//	pack(data, size, "<[2cL2sL]L[2l2S6L]", &header, 40, &infoheader);
//	int palsize;
//	char *pal;
//	try {
//		pal = this->palette->save_sc_wpe(palsize);
//	} catch (exception) {
//		delete [] data;
//		throw;
//	}
//	memcpy(data+dataoffset-1024, pal, palsize);
//	delete [] pal;
//	if (compression == PCX_COMPRESSION::NONE) {
//		for (int n = this->height; n > 0; n--) {
//			memcpy(data+dataoffset+padwidth*(this->height-n), this->planes+this->width*n, this->width);
//		}
//	} else {
//		memcpy(data+dataoffset, compressed, len);
//		delete [] compressed;
//	}
//	return data;
}

Palette* PCX::get_palette(unsigned int specialPaletteRow) {
	if (!this->specialPalette) {
		SCMSError err("Internal", "PCX file was not loaded as a special palette");
		throw err;
	}
	if (specialPaletteRow >= this->pixels.height) {
		SCMSError err("Internal", "Special palette row out of bounds");
		throw err;
	}
	RGB colors[this->pixels.width];
	memset(colors, 0, sizeof(RGB)*this->pixels.width);
	for (int x = 0; x < this->pixels.width; x++) {
		colors[x] = this->palette->get_color(this->pixels.pixels[x+specialPaletteRow*this->pixels.width]);
	}
	return new Palette(colors, this->pixels.width);
}