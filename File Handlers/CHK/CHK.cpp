//
//  CHK.cpp
//  SCMS
//
//  Created by Zach Zahos on 2016-01-01.
//
//

#include "CHK.h"
#include "Exception.h"
#include "Pack.h"
#include "CHKSections.h"

#include <fstream>

bool CHK::section_required(u32 sectionID, CHK *chk) {
	switch (sectionID) {
		case CHKSectionVER::ID:
			return true;
		case CHKSectionTYPE::ID:
			return CHKSectionTYPE::Requirements.is_required(chk);
		case CHKSectionIVER::ID:
			return CHKSectionIVER::Requirements.is_required(chk);
		case CHKSectionIVE2::ID:
			return CHKSectionIVE2::Requirements.is_required(chk);
		case CHKSectionVCOD::ID:
			return CHKSectionVCOD::Requirements.is_required(chk);
		case CHKSectionIOWN::ID:
			return CHKSectionIOWN::Requirements.is_required(chk);
		case CHKSectionOWNR::ID:
			return CHKSectionOWNR::Requirements.is_required(chk);
		case CHKSectionERA::ID:
			return CHKSectionERA::Requirements.is_required(chk);
		case CHKSectionDIM::ID:
			return CHKSectionDIM::Requirements.is_required(chk);
		case CHKSectionSIDE::ID:
			return CHKSectionSIDE::Requirements.is_required(chk);
		case CHKSectionMTXM::ID:
			return CHKSectionMTXM::Requirements.is_required(chk);
		case CHKSectionPUNI::ID:
			return CHKSectionPUNI::Requirements.is_required(chk);
		case CHKSectionUPGR::ID:
			return CHKSectionUPGR::Requirements.is_required(chk);
		case CHKSectionPTEC::ID:
			return CHKSectionPTEC::Requirements.is_required(chk);
		case CHKSectionUNIT::ID:
			return CHKSectionUNIT::Requirements.is_required(chk);
		case CHKSectionISOM::ID:
			return CHKSectionISOM::Requirements.is_required(chk);
		case CHKSectionTILE::ID:
			return CHKSectionTILE::Requirements.is_required(chk);
		case CHKSectionDD2::ID:
			return CHKSectionDD2::Requirements.is_required(chk);
		case CHKSectionTHG2::ID:
			return CHKSectionTHG2::Requirements.is_required(chk);
		case CHKSectionMASK::ID:
			return CHKSectionMASK::Requirements.is_required(chk);
		case CHKSectionSTR::ID:
			return CHKSectionSTR::Requirements.is_required(chk);
		case CHKSectionUPRP::ID:
			return CHKSectionUPRP::Requirements.is_required(chk);
		case CHKSectionUPUS::ID:
			return CHKSectionUPUS::Requirements.is_required(chk);
		case CHKSectionMRGN::ID:
			return CHKSectionMRGN::Requirements.is_required(chk);
		case CHKSectionTRIG::ID:
			return CHKSectionTRIG::Requirements.is_required(chk);
		case CHKSectionMBRF::ID:
			return CHKSectionMBRF::Requirements.is_required(chk);
		case CHKSectionSPRP::ID:
			return CHKSectionSPRP::Requirements.is_required(chk);
		case CHKSectionFORC::ID:
			return CHKSectionFORC::Requirements.is_required(chk);
		case CHKSectionWAV::ID:
			return CHKSectionWAV::Requirements.is_required(chk);
		case CHKSectionUNIS::ID:
			return CHKSectionUNIS::Requirements.is_required(chk);
		case CHKSectionUPGS::ID:
			return CHKSectionUPGS::Requirements.is_required(chk);
		case CHKSectionTECS::ID:
			return CHKSectionTECS::Requirements.is_required(chk);
		case CHKSectionSWNM::ID:
			return CHKSectionSWNM::Requirements.is_required(chk);
		case CHKSectionCOLR::ID:
			return CHKSectionCOLR::Requirements.is_required(chk);
		case CHKSectionPUPx::ID:
			return CHKSectionPUPx::Requirements.is_required(chk);
		case CHKSectionPTEx::ID:
			return CHKSectionPTEx::Requirements.is_required(chk);
		case CHKSectionUNIx::ID:
			return CHKSectionUNIx::Requirements.is_required(chk);
		case CHKSectionUPGx::ID:
			return CHKSectionUPGx::Requirements.is_required(chk);
		case CHKSectionTECx::ID:
			return CHKSectionTECx::Requirements.is_required(chk);
		default:
			return false;
	}
}

CHKSection* CHK::section_create(u32 sectionID, CHK *chk, bool onlyKnown) {
	switch (sectionID) {
		case CHKSectionVER::ID:
			return new CHKSectionVER(chk);
		case CHKSectionTYPE::ID:
			return new CHKSectionTYPE(chk);
		case CHKSectionIVER::ID:
			return new CHKSectionIVER(chk);
		case CHKSectionIVE2::ID:
			return new CHKSectionIVE2(chk);
		case CHKSectionVCOD::ID:
			return new CHKSectionVCOD(chk);
		case CHKSectionIOWN::ID:
			return new CHKSectionIOWN(chk);
		case CHKSectionOWNR::ID:
			return new CHKSectionOWNR(chk);
		case CHKSectionERA::ID:
			return new CHKSectionERA(chk);
		case CHKSectionDIM::ID:
			return new CHKSectionDIM(chk);
		case CHKSectionSIDE::ID:
			return new CHKSectionSIDE(chk);
		case CHKSectionMTXM::ID:
			return new CHKSectionMTXM(chk);
		case CHKSectionPUNI::ID:
			return new CHKSectionPUNI(chk);
		case CHKSectionUPGR::ID:
			return new CHKSectionUPGR(chk);
		case CHKSectionPTEC::ID:
			return new CHKSectionPTEC(chk);
		case CHKSectionUNIT::ID:
			return new CHKSectionUNIT(chk);
		case CHKSectionISOM::ID:
			return new CHKSectionISOM(chk);
		case CHKSectionTILE::ID:
			return new CHKSectionTILE(chk);
		case CHKSectionDD2::ID:
			return new CHKSectionDD2(chk);
		case CHKSectionTHG2::ID:
			return new CHKSectionTHG2(chk);
		case CHKSectionMASK::ID:
			return new CHKSectionMASK(chk);
		case CHKSectionSTR::ID:
			return new CHKSectionSTR(chk);
		case CHKSectionUPRP::ID:
			return new CHKSectionUPRP(chk);
		case CHKSectionUPUS::ID:
			return new CHKSectionUPUS(chk);
		case CHKSectionMRGN::ID:
			return new CHKSectionMRGN(chk);
		case CHKSectionTRIG::ID:
			return new CHKSectionTRIG(chk);
		case CHKSectionMBRF::ID:
			return new CHKSectionMBRF(chk);
		case CHKSectionSPRP::ID:
			return new CHKSectionSPRP(chk);
		case CHKSectionFORC::ID:
			return new CHKSectionFORC(chk);
		case CHKSectionWAV::ID:
			return new CHKSectionWAV(chk);
		case CHKSectionUNIS::ID:
			return new CHKSectionUNIS(chk);
		case CHKSectionUPGS::ID:
			return new CHKSectionUPGS(chk);
		case CHKSectionTECS::ID:
			return new CHKSectionTECS(chk);
		case CHKSectionSWNM::ID:
			return new CHKSectionSWNM(chk);
		case CHKSectionCOLR::ID:
			return new CHKSectionCOLR(chk);
		case CHKSectionPUPx::ID:
			return new CHKSectionPUPx(chk);
		case CHKSectionPTEx::ID:
			return new CHKSectionPTEx(chk);
		case CHKSectionUNIx::ID:
			return new CHKSectionUNIx(chk);
		case CHKSectionUPGx::ID:
			return new CHKSectionUPGx(chk);
		case CHKSectionTECx::ID:
			return new CHKSectionTECx(chk);
		default:
			if (onlyKnown) {
				throw;
			}
			return new CHKSectionUnknown(chk, sectionID);
	}
}

void CHK::open_file(const char *filename) {
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
void CHK::open_data(const u8 *buffer, int size) {
	const u8 *cur = buffer, *end = buffer+size;
	while (cur-end > sizeof(u32)*2) {
		u32 sectionID = *(u32 *)cur;
		cur += sizeof(u32);
		u32 sectionSize = *(u32 *)cur;
		cur += sizeof(u32);
		CHKSection *section = CHK::section_create(sectionID, this, false);
		sectionSize = min(sectionSize, (u32)(end-cur));
		section->load_data((u8 *)cur, sectionSize);
		this->sections[sectionID] = section;
		cur += sectionSize;
	}
}

CHKSection* CHK::get_section(u32 sectionID, bool createIfNeeded, bool checkRequirements) {
	CHKSection *section = nullptr;
	auto iter = this->sections.find(sectionID);
	if (iter != this->sections.end()) {
		section = iter->second;
	} else {
		if (checkRequirements && CHK::section_required(sectionID, this)) {
			throw;
		}
		if (createIfNeeded) {
			section = CHK::section_create(sectionID, this);
			this->sections[sectionID] = section;
		}
	}
	return section;
}

void CHK::set_section(CHKSection *section) {
	this->sections[section->sectionID()] = section;
}
