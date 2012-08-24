#ifndef _MD3_ENTITY_H_
#define _MD3_ENTITY_H_
 
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "entity.h"
#include "md3_mesh.h"

class MD3Entity : public Entity {
	private:


	protected:
		void drawElements(int index);
		void drawSurface(int index);

	public:
		
		MD3Mesh *model;

		MD3Entity(MD3Mesh *model);
		MD3Entity(const MD3Entity &e);
		~MD3Entity();

		virtual void think(float afTimeStep);
		virtual void onDraw();
};

#endif