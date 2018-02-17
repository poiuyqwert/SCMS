/*
 *  FNT.cpp
 *  SCMS
 *
 *  Created by poiuy_qwert on 14/07/09.
 *
 */

#include "FNT.h"
#include "BMP.h"

#include <list>

#pragma pack(push, 1)
struct FNT_HEADER {
	u32 signature;
	u8 lowIndex;
	u8 highIndex;
	Size<u8> maxSize;
};
#pragma pack(pop)

FNT::FNT(vector<u8 *> letters, Size<u8> size, u8 low)
	: size(size), lowIndex(low)
{
	this->close();
	this->letters.assign(letters.begin(), letters.end());
}

void FNT::open_file(const char *filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		SCMSError err("Open", "Could not open file '%s'", filename);
		throw err;
	}
	file.seekg(0, ios::end);
	long long length = file.tellg();
	file.seekg(0);
	u8 buffer[length];
	file.read((char *)buffer, length);
	file.close();
	try {
		this->open_data(buffer, length);
	} catch (exception) {
		throw;
	}
}

void FNT::open_data(const u8 *buffer, long long size) {
	FNT_HEADER header;
	unpack(buffer, sizeof(FNT_HEADER), "<[L4C]", &header);
	if (header.signature != L('FONT')) {
		SCMSError err("Open", "Invalid FNT file (invalid signature)");
		throw err;
	}
	this->letters.clear();
	const u8 *offsets = buffer+sizeof(FNT_HEADER);
	u32 offset;
	for (int n = 0; n <= header.highIndex-header.lowIndex; n++) {
		unpack(offsets, sizeof(u32), "<L", &offset);
		u8 *letter = new u8[header.maxSize.height*header.maxSize.width];
		memset(letter, 0, header.maxSize.height*header.maxSize.width);
		if (offset) {
			FNT_CHR_HEADER chr;
			unpack(buffer+offset, sizeof(FNT_CHR_HEADER), "<[4C]", &chr);
			const u8 *comp = buffer+offset+sizeof(FNT_CHR_HEADER);
			int pos = 0;
			while (pos < chr.size.height*chr.size.width) {
				pos += ((*comp & 0xF8) >> 3);
				letter[(chr.offset.y+(pos/chr.size.width))*header.maxSize.width+chr.offset.x+(pos%chr.size.width)] = (*comp & 0x07);
				pos++;
				comp++;
			}
		}
		this->letters.push_back(letter);
		offsets += sizeof(long);
	}
	this->lowIndex = header.lowIndex;
	this->size = header.maxSize;
}

void FNT::export_file(const char *filename, Palette *palette) {
	BMP *bmp = this->export_data(palette);
	bmp->save_file(filename);
	delete bmp;
}

BMP* FNT::export_data(Palette *palette) {
	u32 fullWidth = this->size.width*(256-this->lowIndex);
	Pixels pixels({fullWidth,this->size.height});
	for (int i = 0; i < 256-this->lowIndex; i++) {
		Pixels image = this->get_letter(i+this->lowIndex);
		for (int y = 0; y < this->size.height; y++) {
			memcpy(pixels.pixels+(fullWidth*y)+(this->size.width*i), image.pixels+(this->size.width*y), this->size.width);
		}
	}
	BMP *bmp = new BMP(pixels, palette);
	return bmp;
}

void FNT::save_file(const char *filename) {
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

u8* FNT::save_data(int &size) {
#warning SWITCH TO PACK?
	int offset = sizeof(FNT_HEADER) + 4*this->letters.size();
	int tmpsize = offset + sizeof(FNT_CHR_HEADER)*this->letters.size();
	list<FNT_CHR_HEADER> dims;
	for (int n = 0; n < this->letters.size(); n++) {
		Pixels letter = this->get_letter(n);
		FNT_CHR_HEADER dim = letter_dims(letter);
		dims.push_back(dim);
		tmpsize += dim.size.width*dim.size.height;
	}
	u8 buffer[tmpsize];
	memset(buffer, 0, tmpsize);
	FNT_HEADER *header = (FNT_HEADER*)buffer;
	header->signature = L('FONT');
	header->lowIndex = this->lowIndex;
	header->highIndex = this->lowIndex+this->letters.size()-1;
	header->maxSize = this->size;
	list<FNT_CHR_HEADER>::iterator dim = dims.begin();
	u8 *cur = buffer+sizeof(FNT_HEADER);
	for (vector<unsigned char*>::iterator letter = this->letters.begin(); letter != this->letters.end(); letter++) {
		if ((*dim).size.width) {
			pack(cur, 4, "<L", offset);
			memcpy(buffer+offset, &dim, sizeof(FNT_CHR_HEADER));
			offset += sizeof(FNT_CHR_HEADER);
			u8 jmp = 0;
			u8 *comp = buffer+offset;
			for (int y = (*dim).offset.y; y < (*dim).offset.y+(*dim).size.height; y++) {
				for (int x = (*dim).offset.x; x < (*dim).offset.x+(*dim).size.width; x++) {
					u8 color = (*letter)[x+y*this->size.width];
					if (color == 0 && jmp < 31) {
						jmp++;
					} else {
						*comp = (jmp << 3) + (color & 0x07);
						jmp = 0;
						comp++;
						offset += 1;
					}
				}
			}
			if (jmp) {
				*comp = (jmp << 3);
				offset += 1;
			}
		}
		dim++;
		cur += 4;
	}
	size = offset;
	u8 *sized = new u8[size];
	memcpy(sized, buffer, size);
	return sized;
}

Pixels FNT::get_letter(u8 n) {
	if (n < lowIndex || n >= lowIndex+this->letters.size()) {
		SCMSError err("Internal", "Letter index out of range (got %u, expected number in range %u-%u)", n, lowIndex, lowIndex+this->letters.size());
		throw err;
	}
	Pixels pixels(this->letters[n-lowIndex], {this->size.width,this->size.height});
	return pixels;
}

void FNT::set_letter(u8 n, Pixels pixels) {
	if (n < lowIndex || n >= lowIndex+this->letters.size()) {
		SCMSError err("Internal", "Letter index out of range (got %u, expected number in range %u-%u)", n, lowIndex, this->letters.size());
		throw err;
	}
#warning LETTER SIZE
	this->letters[n-lowIndex] = pixels.pixels;
}

FNT_CHR_HEADER FNT::letter_dims(Pixels letter) {
	FNT_CHR_HEADER dims;
	dims.size = {0,0};
	dims.offset = {(u8)letter.size.width,(u8)letter.size.height};
	for (int y = 0; y < letter.size.height; y++) {
		bool empty = true;
		for (int x = 0; x < letter.size.width; x++) {
			char c = letter.pixels[x+y*letter.size.width];
			if (c != 0) {
				if (x < dims.offset.x)
					dims.offset.x = x;
				if (x + 1 > dims.size.width)
					dims.size.width = x + 1;
				empty = false;
			}
		}
		if (!empty) {
			if (y < dims.offset.y)
				dims.offset.y = y;
			dims.size.height = y;
		}
	}
	if (dims.size.width) {
		dims.size.width -= dims.offset.x;
		dims.size.height -= dims.offset.y - 1;
	}
	return dims;
}

void FNT::close() {
	for (vector<u8 *>::iterator letter = this->letters.begin(); letter != this->letters.end(); letter++)
		delete [] *letter;
	this->letters.clear();
	this->lowIndex = 0;
	this->size = {0,0};
}