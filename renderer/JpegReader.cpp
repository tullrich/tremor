#include <cstdio>
#include <cstring>
#include "JpegReader.h"

JPEGReader::JPEGReader(char *filepath) {
		cinfo = new jpeg_decompress_struct;
		jerr = new jpeg_error_mgr;
}

JPEGReader::~JPEGReader() {

}

int JPEGReader::readJPEG(char *filepath, tImage *img) {
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	FILE * infile;
	if ((infile = fopen(filepath, "rb")) == NULL) {
	    fprintf(stderr, "can't open %s\n", filepath);
	    return -1;
	}
	jpeg_stdio_src(&cinfo, infile);

	jpeg_read_header(&cinfo, TRUE);

	jpeg_start_decompress(&cinfo);
	int row_stride = cinfo.output_width * cinfo.output_components;
	printf("Row stride: %i output_components: %i\n", row_stride, cinfo.output_components);

	JSAMPARRAY buffer = new JSAMPROW[BUFFER_HEIGHT];
	//JSAMPARRAY buffer = (JSAMPARRAY)malloc(sizeof(JSAMPROW) * buffer_height);
	for (int i = 0; i < BUFFER_HEIGHT; i++) {
		buffer[i] = new JSAMPLE[row_stride];
	}
	//buffer[0] = (JSAMPROW)malloc(sizeof(JSAMPLE) * row_stride);

	img = new tImage;
	img->width = cinfo.output_width;
	img->height = cinfo.output_height;
	img->pixels = new unsigned char[cinfo.output_height * row_stride];

	//printf("img->pixels %#x\n", &img->pixels[cinfo.output_height * row_stride - row_stride]);
	int count = 0;
	while (cinfo.output_scanline < cinfo.output_height) {
		jpeg_read_scanlines(&cinfo, buffer, BUFFER_HEIGHT);
		//printf("Copying %i row(s) to img->pixels offset %i, %#x\n", BUFFER_HEIGHT, count, img->pixels + count);
		memcpy(img->pixels + count, buffer, sizeof(JSAMPROW[BUFFER_HEIGHT]));
		printf("R:%i, G:%i, B:%i\n", *(img->pixels + count + row_stride), *(img->pixels + count + 1), *(img->pixels + count + 2));
		count += row_stride;
	}

	for (int i = 0; i < cinfo.output_height * row_stride; i+=3) {
		//printf("R:%i, G:%i, B:%i\n", img[i], img[i+1], img[i+2]);
	}

	jpeg_finish_decompress(&cinfo);
	fclose(infile);

	jpeg_destroy_decompress(&cinfo);

	return 1;
}