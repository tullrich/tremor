#ifndef _ENTITY_H_
#define _ENTITY_H_
 
#include <SDL/SDL.h>

// interface
class Entity {
	protected:
		int id;

	public:
		static int id_next;

		Entity();
		//Entity(Entity &e);
		virtual ~Entity() {};

		// pure virtual methods
		virtual void think(float afTimeStep) = 0;
		virtual void onDraw() = 0;
};

#endif