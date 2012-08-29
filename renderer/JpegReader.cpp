#include <cstdio>
#include <cstring>
#include "JpegReader.h"

JPEGReader::JPEGReader(char *filepath) : cinfo(), jerr() {
	this->filepath = filepath;

	/* init structs, allocates temp memory here */
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	/* open the .jpg stream */
	if ((infile = fopen(filepath, "rb")) == NULL) {
	    fprintf(stderr, "can't open %s\n", filepath);
	}
	jpeg_stdio_src(&cinfo, infile);

	/* populate certain header fields */
	jpeg_read_header(&cinfo, TRUE);

}

JPEGReader::~JPEGReader() {
	fclose(infile);
	jpeg_destroy_decompress(&cinfo);
}

void JPEGReader::dumpImage(tImage *img) { 
	for (int i = 0; i < img->height; i++) {
		int row_ofs = i * img->width * 3;
		printf("\n\nROW_OFS %i\n", row_ofs);
		for (int j = 0; j < img->width * 3; j+=3) {
			printf("(%.3i,%.3i,%.3i)	", img->pixels[row_ofs + j], img->pixels[row_ofs + j + 1], img->pixels[row_ofs + j + 2]);
			//printf("%#x ", &img->pixels[row_ofs + j]);

			if ((j % 10) == 0) {
				printf("\n");
			}
		}
		printf("\n");
		//if (i == 3)
			//break;
	}
}

void JPEGReader::dumpImage2(tImage *img) { 
	for (int i = 0; i < img->height * img->width * 3; i++) {
		printf("%i,", img->pixels[i]);
	}
}

void JPEGReader::dumpRow(int width, JSAMPROW row) {
	for (int j = 0; j < width; j+=3) {
		printf("%i,%i,%i ", row[j], row[j+1], row[j+2]);
	}
	printf("\n\n");
}

void JPEGReader::allocateBuffer() {
	for (int i = 0; i < BUFFER_HEIGHT; i++) {
		buffer[i] = new JSAMPLE[row_stride];
	}
}

void JPEGReader::deallocateBuffer() {
	for (int i = 0; i < BUFFER_HEIGHT; i++) {
		delete buffer[i];
	}
}


int JPEGReader::readJPEG(tImage *img) {

	/* start */
	jpeg_start_decompress(&cinfo);

	/* allocate buffer char** */
	row_stride = cinfo.output_width * cinfo.output_components;
	allocateBuffer();

	/* allocate returned image */
	img = new tImage;
	img->width = cinfo.output_width;
	img->height = cinfo.output_height;
	img->pixels = new unsigned char[cinfo.output_height * row_stride];

	/* read in the entire image */
	int count = 0;
	while (cinfo.output_scanline < cinfo.output_height) {
		jpeg_read_scanlines(&cinfo, buffer, BUFFER_HEIGHT);
		for (int h = 0; h < BUFFER_HEIGHT; h++) {
			memcpy(img->pixels + count, buffer[0], sizeof(JSAMPLE[row_stride]));
		}	
		count += row_stride * BUFFER_HEIGHT;
	}

	/* cleanup */
	jpeg_finish_decompress(&cinfo);
	deallocateBuffer();

	return 1;
}
