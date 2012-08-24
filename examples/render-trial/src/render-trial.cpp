#include <cstdio>
#include <vector>
#include "render-trial.h"
#include "trialRenderer.h"
#include "mD3Entity.h"
#include "md3_reader.h"
#include "JpegReader.h"

using namespace std;

MD3Reader reader;
MD3Mesh meshes[2];

bool readInMesh(MD3Mesh *mesh, char* filepath) {
	reader.open(filepath);

	bool good_read = reader.readMesh(mesh);
	reader.close();

	return good_read;
}

int main(int argc, char **argv)
{
	char* filepath;
	if (argc > 1) {
		filepath = argv[1];
	} else {
		filepath = (char*)FILE_PATH;
	} 

	if (!readInMesh(&meshes[0], filepath)) {
		printf("[0] Bad mesh read aborting renderer\n");
		return -1;
	}
	printMesh(&meshes[0]);

	if (!readInMesh(&meshes[1], (char*)FILE_PATH2)) {
		printf("[1] Bad mesh read aborting renderer\n");
		return -1;
	}

	printf("Creating entities\n");
	//vector<MD3Entity*> entities;
	MD3Entity entity1 = MD3Entity(&meshes[0]);
	//entities.push_back( &entity1 );
	MD3Entity entity2 = MD3Entity(&meshes[1]);
	//entities.push_back( &entity2 );

	MD3Entity entities[2] = {
		MD3Entity(entity1), MD3Entity(entity2)
	};

	tImage *img;
	JPEGReader::readJPEG((char*)SHOTGUN_FILEPATH, img);

	//MD3Entity entities[2] = {
	//	MD3Entity(&entity1), MD3Entity(&entity2)
	//};
	
	//short i = 0; 
	//printHeader(entities[0].model->header);
	//printHeader(entities[1].model->header);

	//MD3Entity entitiez[2] = {
	//	MD3Entity(&meshes[0]), MD3Entity(&meshes[1])
	//};
	
	//MD3Entity entityz = MD3Entity(&meshes[0]);
	//MD3Entity entityy = MD3Entity(&meshes[1]);
	//entities[0] = entity1;
	//entities[1] = entity2;

	printf("Creating renderer\n");
	TrialRenderer r = TrialRenderer(2, entities, img);
	r.init();
	r.start();

	return true;
}
