#include <cstdio>
#include "md3_reader.h"

bool MD3Reader::_checkError() {
	return file_in.fail();
}

void MD3Reader::open(const char* filepath) {

	printf("Opening file %s...", filepath);
	file_in.open(filepath, std::fstream::in);	

	if (_checkError()) {
		printf("\nERROR: could not open file\n");
		return;
	}

	printf("done\n");
}

bool MD3Reader::readMesh(MD3Mesh* mesh) {
	
	md3_header *header;
	md3_frame *frames;
	md3_tag *tags;
	md3_surface *surfaces;

	// Read in each component, stop and return if there is an error at any step
	// in the case of an error, the model will be uncomplete

	// Read in the header
	header = new md3_header;
	if (!readHeader(header)) {
		return false;
	};
	mesh->header = header;
	
	// Read in the frames
	frames = new md3_frame[header->num_frames];
	if(!readFrames(header->num_frames, header->ofs_frames, frames)) {
		return false;
	}
	mesh->frames = frames;

	// Read in the tags
	tags = new md3_tag[header->num_tags];
	if(!readTags(header->num_tags, header->ofs_tags, tags)) {
		return false;
	}
	mesh->tags = tags;

	// Read in the surfaces
	surfaces = new md3_surface[header->num_surfaces];
	if(!readSurfaces(header->num_surfaces, header->ofs_surfaces, surfaces)) {
		return false;
	}
	mesh->surfaces = surfaces;

	return true;
}



bool MD3Reader::_readSurface(int ofs_surface, md3_surface* surface) {
	file_in.seekg(ofs_surface);
	file_in.read((char*)surface, sizeof(md3_surface));

	return !_checkError();
}

bool MD3Reader::readSurface(int ofs_surface, md3_surface* surface) {
	if (!file_in.is_open()) {
		printf("\nERROR: File is not open\n");
		return false;
	}

	if(!_readSurface(ofs_surface, surface)) {
		printf("\nERROR: could not read surfaces\n");
		return false;
	}

	return true;
}

bool MD3Reader::readSurfaces(int num_surfaces, int ofs_surfaces, md3_surface* surfaces) {
	int ofs_current;

	printf("Reading %i surface%s...", num_surfaces, (num_surfaces != 1) ? "s": "");

	if (!file_in.is_open()) {
		printf("\nERROR: File is not open\n");
		return false;
	}

	ofs_current = ofs_surfaces;
	for(int i = 0; i < num_surfaces; i++) {
		if(!_readSurface(ofs_current, &surfaces[i])) {
			printf("\nERROR: could not read surfaces\n");
			return false;
		}

		ofs_current += surfaces[i].ofs_end;
	}

	printf("done\n");
	return true;
}

bool MD3Reader::readTags(int num_tags, int ofs_tags, md3_tag* tags) {
	printf("Reading %i tag%s...", num_tags, (num_tags != 1) ? "s": "");

	if (!file_in.is_open()) {
		printf("\nERROR: File is not open\n");
		return false;
	}

	file_in.seekg(ofs_tags);

	if (file_in.tellg() != ofs_tags) {
		printf("\nERROR: could not reach tag offset\n");
		return false;
	}

	file_in.read((char*)tags, sizeof(md3_tag) * num_tags);

	if (_checkError()) {
		printf("\nERROR: could not read tags\n");
		return false;
	}

	printf("done\n");
	return true;
}

bool MD3Reader::readFrames(int num_frames, int ofs_frames, md3_frame* frames) {
	printf("Reading %i frame%s...", num_frames, (num_frames != 1) ? "s": "");

	if (!file_in.is_open()) {
		printf("\nERROR: File is not open\n");
		return false;
	}

	file_in.seekg(ofs_frames);

	if (file_in.tellg() != ofs_frames) {
		printf("\nERROR: could not reach frame offset\n");
		return false;
	}

	file_in.read((char*)frames, sizeof(md3_frame) * num_frames);

	if (_checkError()) {
		printf("\nERROR: could not read frames\n");
		return false;
	}

	printf("done\n");
	return true;
}

bool MD3Reader::readHeader(md3_header* header) {
	printf("Reading header...");

	if (!file_in.is_open()) {
		printf("\nERROR: File is not open\n");
		return false;
	}

	file_in.read((char*)header, sizeof(md3_header));

	if (_checkError()) {
		printf("\nERROR: could not read header\n");
		return false;
	}

	printf("done\n");
	return true;
}

void MD3Reader::close() {
	printf("Closing file...");
	file_in.close();

	if (_checkError()) {
		printf("\nERROR: could not close file\n");
		return;
	}

	printf("done\n");
}
