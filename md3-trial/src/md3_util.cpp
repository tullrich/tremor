#include <cstdio>
#include "md3_structs.h"

void printHeader(md3_header* h) {
	printf("md3_header {\n");
	printf("	ident: %i\n", h->ident);
	printf("	version: %i\n", h->version);
	printf("	name: %s\n", h->name);
	printf("	flags: %i\n", h->flags);
	printf("	num_frames: %i\n", h->num_frames);
	printf("	num_tags: %i\n", h->num_tags);
	printf("	num_surfaces: %i\n", h->num_surfaces);
	printf("	num_skins: %i\n", h->num_skins);
	printf("	ofs_frames: %i\n", h->ofs_frames);
	printf("	ofs_tags: %i\n", h->ofs_tags);
	printf("	ofs_surfaces: %i\n", h->ofs_surfaces);
	printf("	ofs_eof: %i\n", h->ofs_eof);
	printf("}\n");
}

void printFrame(md3_frame* f) {
	printf("md3_frame {\n");
	printf("	min_bounds: <%f,%f,%f>\n", f->min_bounds.x, f->min_bounds.y, f->min_bounds.z);
	printf("	max_bounds: <%f,%f,%f>\n", f->max_bounds.x, f->max_bounds.y, f->max_bounds.z);
	printf("	local_origin: <%f,%f,%f>\n", f->local_origin.x, f->local_origin.y, f->local_origin.z);
	printf("	radius: %f\n", f->radius);
	printf("	name: %s\n", f->name);
	printf("}\n");
}

void printTag(md3_tag* t) {
	printf("md3_tag {\n");
	printf("	name:%s\n", t->name);
	printf("	origin: <%f,%f,%f>\n", t->origin.x, t->origin.y, t->origin.z);
	printf("	axis:	[%9f, %9f, %9f\n", t->axis[0].x, t->axis[0].y, t->axis[0].z);
	printf("	 	 %9f, %9f, %9f\n", t->axis[1].x, t->axis[1].y, t->axis[1].z);
	printf("	 	 %9f, %9f, %9f]\n", t->axis[2].x, t->axis[2].y, t->axis[2].z);
	printf("}\n");
}

void printSurface(md3_surface* t) {
	printf("md3_surface {\n");
	printf("	ident: %i\n", t->ident);
	printf("	name: %s\n", t->name);
	printf("	flags: %i\n", t->flags);
	printf("	num_frames: %i\n", t->num_frames);
	printf("	num_shaders: %i\n", t->num_shaders);
	printf("	num_verts: %i\n", t->num_verts);
	printf("	num_triangles: %i\n", t->num_triangles);
	printf("	ofs_triangles: %i\n", t->ofs_triangles);
	printf("	ofs_shaders: %i\n", t->ofs_shaders);
	printf("	ofs_st: %i\n", t->ofs_st);
	printf("	ofs_xyznormal: %i\n", t->ofs_xyznormal);
	printf("	ofs_end: %i\n", t->ofs_end);
	printf("}\n");
}

void printFrames(int num_frames, md3_frame* frames) {
	for (int i = 0; i < num_frames; i++) {		
		printFrame(&frames[i]);
	}
}

void printTags(int num_tags, md3_tag* tags) {
	for (int i = 0; i < num_tags; i++) {		
		printTag(&tags[i]);
	}
}

void printSurfaces(int num_surfaces, md3_surface* surfaces) {
	for (int i = 0; i < num_surfaces; i++) {		
		printSurface(&surfaces[i]);
	}
}