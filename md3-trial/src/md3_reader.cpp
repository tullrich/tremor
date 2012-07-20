#include <cstdio>
#include "md3_reader.h"

bool MD3Reader::checkError() {
	return file_in.fail();
}

void MD3Reader::open(const char* filepath) {

	printf("Opening file %s...", filepath);
	file_in.open(filepath, std::fstream::in);	

	if (checkError()) {
		printf("\nERROR: could not open file\n");
		return;
	}

	printf("done\n");
}

void MD3Reader::readMesh(MD3Mesh* mesh) {
	
	md3_header *header;
	md3_frame *frames;
	md3_tag *tags;

	header = new md3_header;
	if (!readHeader(header)) {
		return;
	};
	mesh->header = header;
	
	printf("header->num_frames: %i\n", header->num_frames);
	frames = new md3_frame[header->num_frames];
	if(!readFrames(header->num_frames, header->ofs_frames, frames)) {
		return;
	}
	mesh->frames = frames;

	tags = new md3_tag[header->num_tags];
	if(!readTags(header->num_tags, header->ofs_tags, tags)) {
		return;
	}
	mesh->tags = tags;
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

	if (checkError()) {
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

	if (checkError()) {
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

	if (checkError()) {
		printf("\nERROR: could not read header\n");
		return false;
	}

	printf("done\n");
	return true;
}

void MD3Reader::close() {
	printf("Closing file...");
	file_in.close();

	if (checkError()) {
		printf("\nERROR: could not close file\n");
		return;
	}

	printf("done\n");
}
