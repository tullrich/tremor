#ifndef _MD3_MESH_H
#define _MD3_MESH_H
#include "md3_structs.h"
#include "md3_mesh.h"

class MD3Mesh {
	public:
		md3_header* header;
		md3_frame* frames;
};

#endif