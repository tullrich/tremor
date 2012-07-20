#ifndef _MD3READER_H
#define _MD3READER_H
#include <fstream>
#include "md3_structs.h"
#include "md3_mesh.h"

class MD3Reader {
	public:

		void open(const char* filepath);
		void readMesh(MD3Mesh* mesh);
		bool readHeader(md3_header* header);
		bool readFrames(int num_frames, int ofs_frames, md3_frame* frames);
		void close();

	private:
		std::fstream file_in;

		bool checkError();
};

#endif
