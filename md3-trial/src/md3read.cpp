#include <cstdio>
#include "md3read.h"
#include "md3_reader.h"


int main(int argc, char *argv[]) {
	MD3Reader reader;
	MD3Mesh mesh;

	if (argc > 1) {
		reader.open(argv[1]);
	} else {
		reader.open(FILE_PATH);
	}
	reader.readMesh(&mesh);
	reader.close();

	printHeader(mesh.header);
	printFrames(mesh.header->num_frames, mesh.frames);
	printTags(mesh.header->num_tags, mesh.tags);
	printSurfaces(mesh.header->num_surfaces, mesh.surfaces);
}


