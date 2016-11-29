//
//  GRP.cpp
//  SCMS
//
//  Created by Zach Zahos on 2015-12-31.
//
//

#include "GRP.h"

Pixels GRP::grp_decompress(const u8 *framedata, int size, int width, int height, GRP_FRAME_HEADER header, u8 transindex) {
	Pixels pixels(width,height,transindex);
	for (int y = 0; y < header.lines; y++) {
		int ty = header.yoffset + y;
		u16 offset;
		unpack(framedata + sizeof(u16)*y, size-sizeof(u16)*y, "<S", &offset);
		const u8 *cur = framedata + offset;
		for (int x = 0; x < header.linewidth;) {
			int tx = header.xoffset + x;
			u8 cmd = *cur;
			cur++;
			if (cmd & 0x80) {
				int count = cmd-0x80;
				memset(pixels.pixels+tx+ty*width, transindex, count);
				x += count;
			} else if (cmd & 0x40) {
				int count = cmd-0x40;
				memset(pixels.pixels+tx+ty*width, *cur, count);
				x += count;
				cur++;
			} else {
				int count = cmd;
				memcpy(pixels.pixels+tx+ty*width, cur, count);
				x += count;
				cur += count;
			}
		}
	}
	return pixels;
}

unsigned char* GRP::grp_compress(Pixels pixels, int &size, GRP_FRAME_HEADER *header, unsigned char transindex) {
	return NULL;
}

void GRP::open_file(const char *filename, bool compressed, unsigned char transindex) {
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
		this->open_data(buffer, size, compressed, transindex);
	} catch (exception) {
		throw;
	}
}

void GRP::open_data(const u8 *buffer, int size, bool compressed, unsigned char transindex) {
	if (size < sizeof(u16)*3) {
		SCMSError err("Open", "Not enough data to be a valid GRP");
		throw err;
	}
	u16 frameCount, width, height;
	unpack(buffer, size, "<3S", &frameCount, &width, &height);
	if (frameCount < 1 || frameCount > 2400) {
		SCMSError err("Open", "Invalid number of frames");
		throw err;
	}
	if (width < 1 || width > 256 || height < 1 || height > 256) {
		SCMSError err("Open", "Invalid number of frames");
		throw err;
	}
	if (size < sizeof(u16)*3+(sizeof(u8)*4+sizeof(u32))*frameCount) {
		SCMSError err("Open", "Not enough data to be a valid GRP");
		throw err;
	}
	const u8 *cur = buffer + sizeof(u16)*3;
	int remaining = size - sizeof(u16)*3;
	GRP_FRAME_HEADER header;
	this->frames.clear();
	for (int f = 0; f < frameCount; f++) {
		unpack(cur, remaining, "<[4CL]", &header);
		if (header.framedata > size) {
			SCMSError err("Open", "Not enough data to be a valid GRP");
			throw err;
		}
		if (header.xoffset + header.linewidth > width) {
			header.linewidth = width - header.xoffset;
		}
		if (header.yoffset + header.lines > height) {
			header.lines = height - header.yoffset;
		}
		const u8 *frame = buffer + header.framedata;
		if (compressed) {
			Pixels pixels = grp_decompress(frame, size-header.framedata, width, height, header, transindex);
			this->frames.push_back(pixels.pixels);
		} else {
			Pixels pixels(width,height,transindex);
			Pixels content((u8 *)frame,width,height);
			pixels.paste(content, header.xoffset, header.yoffset);
//			unsigned char *pixels = new unsigned char[width*height];
//			memset(pixels, transindex, width*height);
//			for (int y = 0; y < header.lines; y++) {
//				memcpy(pixels+(y+header.yoffset)*width+header.xoffset, frame+y*header.linewidth, header.linewidth);
//			}
			this->frames.push_back(pixels.pixels);
		}
		cur += sizeof(GRP_FRAME_HEADER);
		remaining -= sizeof(GRP_FRAME_HEADER);
	}
	this->width = width;
	this->height = height;
	this->compressed = compressed;
	this->transindex = transindex;
}

Pixels GRP::get_frame(int f) {
	if (f < 0 || f >= this->frames.size()) {
		SCMSError err("Internal", "Frame index out of range (got %u, expected number in range 0-%u)", f, this->frames.size());
		throw err;
	}
	Pixels pixels(this->frames[f], this->width, this->height);
	return pixels;
}

void GRP::set_frame(int f, Pixels pixels) {
	if (f < 0 || f >= this->frames.size()) {
		SCMSError err("Internal", "Frame index out of range (got %u, expected number in range 0-%u)", f, this->frames.size());
		throw err;
	}
#warning CHECK FRAME SIZE
	this->frames[f] = pixels.pixels;
}
