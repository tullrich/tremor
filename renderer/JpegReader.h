#ifndef _JPEG_READER_H
#define _JPEG_READER_H

#include <jpeglib.h>
#include "texture_structs.h"

#define BUFFER_HEIGHT 1

class JPEGReader {
	protected:
		jpeg_decompress_struct *cinfo;
		jpeg_error_mgr *jerr;
	public:
		JPEGReader(char *filepath);
		~JPEGReader();

		static int readJPEG(char *filepath,  tImage *img);
};

#endif