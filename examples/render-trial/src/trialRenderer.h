#ifndef _TRIAL_RENDERER_H
#define _TRIAL_RENDERER_H

#include <vector>

#include "renderer.h"
#include "mD3Entity.h"
#include "texture_structs.h"

using namespace std;

class TrialRenderer : public Renderer {
	private:
		int num_entities;
		MD3Entity *e;
		double eyeX, eyeY, eyeZ;
		double centerX, centerY, centerZ;
		double upX, upY, upZ;

		tImage *img;
		GLuint texname;

	public:
		TrialRenderer(int num_entities, MD3Entity *entities, tImage *img);
		void onRender();
		void onLoop(float ts);
		void onInit();

};

#endif