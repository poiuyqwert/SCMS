//
//  CHK.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-01.
//
//

#pragma once

#include "Types.h"
#include "CHKSection.h"

#include <map>

class CHK {
	CHKGameMode::Enum gameMode;
	
	std::map<u32, CHKSection*> sections;
public:
	CHK() {}
	
	static bool section_required(u32 sectionID, CHK *chk);
	static CHKSection* section_create(u32 sectionID, CHK *chk = nullptr, bool onlyKnown = true);
	
	void open_file(const char *filename);
	void open_data(const u8 *buffer, int size);
	void save_file(const char *filename);
	u8* save_data(int &size);
	
	CHKSection* get_section(u32 sectionID, bool createIfNeeded = false, bool checkRequirements = true);
	template<class T> T* get_section(bool createIfNeeded = false, bool checkRequirements = true) {
		CHKSection *section = this->get_section(T::ID, createIfNeeded, checkRequirements);
		return dynamic_cast<T *>(section);
	}
	
	void set_section(CHKSection *section);
//	template<class T> void set_section(T *section) {
//		this->sections[T::ID] = section;
//	}
};
