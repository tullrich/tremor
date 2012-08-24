#include "md3_surface.h"

int MD3Surface::getNumTriangles() {
	return surf_header->num_triangles;
}

int MD3Surface::getNumVertices() {
	return surf_header->num_verts;
}