#ifndef _JPEG_READER_H
#define _JPEG_READER_H

#include <jpeglib.h>
#include "texture_structs.h"

#define BUFFER_HEIGHT 2

class JPEGReader {
	private:
		jpeg_decompress_struct cinfo;
		jpeg_error_mgr jerr;
		char *filepath;
		FILE * infile;
		JSAMPROW buffer[BUFFER_HEIGHT];
		int row_stride;

		void allocateBuffer();
		void deallocateBuffer();

	public:
		JPEGReader(char *filepath);
		~JPEGReader();

		static void dumpImage(tImage *img);
		static void dumpImage2(tImage *img);
		static void dumpRow(int width, JSAMPROW row);
		int readJPEG(tImage *img);
};

#endif