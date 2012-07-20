#ifndef _MD_STRUCTS_H
#define _MD_STRUCTS_H


/* POD structure matching the first input from an md3 file */
typedef struct {
	int ident;
	int version;
	unsigned char name[64];
	int flags;
	int num_frames;
	int num_tags;
	int num_surfaces;
	int num_skins;
	int ofs_frames;
	int ofs_tags;
	int ofs_surfaces;
	int ofs_eof;

} md3_header;

typedef struct {
	float x;
	float y;
	float z;
} vec3;

typedef struct {
	vec3 min_bounds;
	vec3 max_bounds;
	vec3 local_origin;
	float radius;
	char name[16];
} md3_frame;

static void printHeader(md3_header* h) {
	printf("md3_header {\n");
	printf("	ident: %i\n", h->ident);
	printf("	version: %i\n", h->version);
	printf("	name: %s\n", h->name);
	printf("	flags: %i\n", h->flags);
	printf("	num_frames: %i\n", h->num_frames);
	printf("	num_tags: %i\n", h->num_tags);
	printf("	num_skins: %i\n", h->num_skins);
	printf("	ofs_frames: %i\n", h->ofs_frames);
	printf("	ofs_tags: %i\n", h->ofs_tags);
	printf("	ofs_surfaces: %i\n", h->ofs_surfaces);
	printf("	ofs_eof: %i\n", h->ofs_eof);
	printf("}\n");
}

static void printFrame(md3_frame* f) {
	printf("md3_frame {\n");
	printf("	min_bounds: <%f,%f,%f>\n", f->min_bounds.x, f->min_bounds.y, f->min_bounds.z);
	printf("	max_bounds: <%f,%f,%f>\n", f->max_bounds.x, f->max_bounds.y, f->max_bounds.z);
	printf("	local_origin: <%f,%f,%f>\n", f->local_origin.x, f->local_origin.y, f->local_origin.z);
	printf("	radius: %f\n", f->radius);
	printf("	name: %s\n", f->name);
	printf("}\n");

	printf("sizeof(md3_frame): %lu\n", sizeof(md3_frame));
	printf("sizeof(float): %lu\n", sizeof(float));
}

#endif