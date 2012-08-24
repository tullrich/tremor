#ifndef _RENDERER_H
#define _RENDERER_H

//#define NO_SDL_GLEXT


//#include <GL/glew.h>
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"

#include "keyboard.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define MAX_FPS 60.0
#define ONE_GAME_TICK ((1.0 / MAX_FPS) * 1000)

class Renderer {
	private:
		SDL_Surface *screen;
		bool running;

	protected:
		void render();
		virtual void onRender() {};
		virtual void onInit() {};
		virtual void onLoop(float ts) {};

	public:
		static Keyboard keyboard;

		Renderer();
		virtual ~Renderer();
		void init();
		void start();
		static void clear(SDL_Surface* s);

};

#endif