/*
 *  BMP.cpp
 *  SCMS
 *
 *  Created by poiuy_qwert on 21/07/09.
 *
 */

#include "BMP.h"

#pragma pack(push, 1)
struct BMP_HEADER {
	u8 signature[2];
	u32 fileSize;
	u16 extra[2];
	u32 dataOffset;
};

struct BMP_V3_INFO_HEADER {
	Size<u32> size;
	u16 planes;
	u16 bitsPerPixel;
	BMP_COMPRESSION::Enum compression;
	u32 dataSize;
	u32 horizontalResolution;
	u32 verticalResolution;
	u32 colors;
	u32 importantColors;
};
#pragma pack(pop)

Pixels BMP::rle8_decompress(const u8 *cmd, int length, Size<u32> size) {
	Pixels pixels(size);
	const u8 *end = cmd+length;
	u8 *cur = pixels.pixels;
	memset(pixels.pixels, 0, size.width*size.height);
	while (cmd < end) {
		SCMSLog.error("%02X %02X\n", (unsigned int)cmd[0], (unsigned int)cmd[1]);
		if (cmd[0] == '\x00') {
			if (cmd[1] < '\x03') {
				if (cmd[1] == '\x02') {
					cur += cur[2]+cur[3]*size.width;
					cmd += 2;
				} else if (cur[1] == '\x01') {
					break;
				} else if ((cur-pixels.pixels)%size.width) {
					cur += size.width-(cur-pixels.pixels)%size.width;
				}
			} else {
				SCMSLog.error("\t");
				for (int n = 0; n < (unsigned int)cmd[1]; n++) SCMSLog.error("%02X ", *(cmd+2+n));
				SCMSLog.error("\n");
				memcpy(cur, cmd+2, cmd[1]);
				cur += cmd[1];
				cmd += cmd[1]+cmd[1]%2;
			}
		} else {
			memset(cur, cmd[1], cmd[0]);
			cur += cmd[0];
		}
		cmd += 2;
	}
	return pixels;
}

u8* BMP::rle8_compress(Pixels pixels, int &length) {
	bool repeats = false;
	u8 temp[pixels.size.width*pixels.size.height];
	u8 *cur = temp;
	const u8 *chr,*absstart = NULL,*line = pixels.pixels,*end = pixels.pixels+pixels.size.width*pixels.size.height;
	const u8 *pixel = pixels.pixels;
	while (pixel < end) {
		chr = pixel;
		do {
			pixel++;
		} while (*pixel == *chr && pixel-chr < 256 && pixel < end);
		if (pixel-chr > 2+(absstart != NULL)) {
			if (absstart != NULL) {
				if (chr-absstart < 3) {
					do {
						cur[0] = '\x01';
						cur[1] = *absstart;
						cur += 2;
					} while (++absstart < chr);
				} else {
					cur[0] = '\x00';
					cur[1] = chr-absstart;
					memcpy(&cur[2], absstart, chr-absstart);
					cur += chr-absstart+(chr-absstart)%2+2;
				}
				absstart = NULL;
			}
			cur[0] = pixel-chr;
			cur[1] = *chr;
			cur += 2;
		} else if (absstart == NULL) {
			repeats = (pixel-chr) == 2;
			absstart = chr;
		}
		if (!((pixel-line)%pixels.size.width) && pixel < end) {
			*(u16*)cur = 0;
			cur += 2;
			line = pixel;
		}
	}
	if (absstart != NULL) {
		cur[0] = '\x00';
		cur[1] = chr-absstart;
		memcpy(&cur[2], absstart, chr-absstart);
		cur += (chr-absstart)+(chr-absstart)%2+2;
	}
	cur[0] = '\x00';
	cur[1] = '\x01';
	length = cur-temp+2;
	u8 *buffer = new u8[length];
	memcpy(buffer, temp, length);
	return buffer;
}

void BMP::open_file(const char *filename) {
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

void BMP::open_data(const u8 *buffer, int length) {
	if (length < sizeof(BMP_HEADER)+sizeof(BMP_V3_INFO_HEADER)+1028) {
		SCMSError err("Open", "Not enough data to be a valid BMP");
		throw err;
	}
	if (memcmp(buffer, "BM", 2)) {
		SCMSError err("Open", "Invalid BMP file");
		throw err;
	}
	BMP_HEADER header;
	BMP_V3_INFO_HEADER infoheader;
	u32 len;
	unpack(buffer, length, "<[2cL2sL]L[2l2S6L]", &header, &len, &infoheader);
	if (len != 40) {
		SCMSError err("Open", "Unsupported BMP file (unknown BMP info header format)");
		throw err;
	}
	if (infoheader.planes != 1) {
		SCMSError err("Open", "Unsupported BMP file (unsupported amount of planes)");
		throw err;
	}
	if (infoheader.bitsPerPixel != 8) {
		SCMSError err("Open", "Unsupported BMP file (unsupported amount of bits per pixel)");
		throw err;
	}
	if (infoheader.compression != BMP_COMPRESSION::NONE && infoheader.compression != BMP_COMPRESSION::RLE8) {
		SCMSError err("Open", "Unsupported BMP file (unsupported compression type)");
		throw err;
	}
	const u8 *bufferend = (unsigned char*)(buffer+length);
	RGB colors[256];
	const u8 *paletteStart = (unsigned char*)buffer+sizeof(BMP_HEADER)+4+sizeof(BMP_V3_INFO_HEADER);
	for (int c = 0; c < 256; c++) {
		RGB *color = (RGB *)(paletteStart+4*c);
		colors[c].r = color->b;
		colors[c].g = color->g;
		colors[c].b = color->r;
	}
	Palette *palette = new Palette(colors, 256);
	buffer += header.dataOffset;
	if (infoheader.dataSize < bufferend-(unsigned char*)buffer) {
		delete palette;
		SCMSError err("Open", "Unsupported BMP file (pixel data is cut short");
		throw err;
	}
	if (infoheader.compression == BMP_COMPRESSION::NONE) {
		int width = ((infoheader.size.width/4)+1)*4;
		if (infoheader.dataSize != width*infoheader.size.height) {
			delete palette;
			SCMSError err("Open", "Unsupported BMP file (invalid data size)");
			throw err;
		}
		this->pixels.pixels = new u8[infoheader.size.width*infoheader.size.height];
		for (int n = 0; n < infoheader.size.height; n++)
			memcpy(&this->pixels.pixels[infoheader.size.width*n], &buffer[width*n], infoheader.size.width);
	} else {
		this->pixels = rle8_decompress(buffer, infoheader.dataSize, {infoheader.size.width,infoheader.size.height});
	}
	this->palette = palette;
	this->pixels.size.width = infoheader.size.width;
	this->pixels.size.height = infoheader.size.height;
}

void BMP::save_file(const char *filename, BMP_COMPRESSION::Enum compression) {
	ofstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Save", "Could not open file '%s'", filename);
		throw err;
	}
	int size;
	u8 *buffer = this->save_data(size, compression);
	file.write((char *)buffer, size);
	delete [] buffer;
	file.close();	
}

u8* BMP::save_data(int &size, BMP_COMPRESSION::Enum compression) {
	int len = 0,dataoffset = sizeof(BMP_HEADER)+4+sizeof(BMP_V3_INFO_HEADER)+1024,padwidth = this->pixels.size.width;
	if (padwidth%4)
		padwidth += 4-padwidth%4;
	u8 *data,*compressed;
	if (compression == BMP_COMPRESSION::NONE) {
		size = dataoffset+padwidth*this->pixels.size.height;
	} else {
		compressed = rle8_compress(this->pixels, len);
		size = dataoffset+len;
	}
	data = new u8[size];
	memset(data, 0, size);
	BMP_HEADER header = {'B','M', (u32)size, 0,0, (u32)dataoffset};
	BMP_V3_INFO_HEADER infoheader = {(u32)this->pixels.size.width,(u32)this->pixels.size.height, 1,8, compression, (u32)(size-dataoffset),0,0,0,0};
	pack(data, size, "<[2cL2sL]L[2l2S6L]", &header, 40, &infoheader);
	RGB colors[256];
	for (int c = 0; c < 256; c++) {
		RGB color = this->palette->get_color(c);
		colors[c].r = color.b;
		colors[c].g = color.g;
		colors[c].b = color.r;
	}
	Palette *savePalette = new Palette(colors, 256);
	int palsize;
	u8 *pal;
	try {
		pal = savePalette->save_sc_wpe(palsize);
	} catch (exception) {
		delete [] data;
		delete savePalette;
		throw;
	}
	delete savePalette;
	memcpy(data+dataoffset-1024, pal, palsize);
	delete [] pal;
	if (compression == BMP_COMPRESSION::NONE) {
		for (int n = this->pixels.size.height; n > 0; n--) {
			memcpy(data+dataoffset+padwidth*(this->pixels.size.height-n), this->pixels.pixels+this->pixels.size.width*(n-1), this->pixels.size.width);
		}
	} else {
		memcpy(data+dataoffset, compressed, len);
		delete [] compressed;
	}
	return data;
}