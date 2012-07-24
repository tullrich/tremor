#ifndef _RENDERER_H
#define _RENDERER_H

#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Renderer {
	private:
		SDL_Surface *screen;
		bool continue_loop;

	protected:
		void render();
		void pumpInput();

		virtual void KeyUp		(const int& iKeyEnum) {}
		virtual void KeyDown		(const int& iKeyEnum) {}
		virtual void MouseMoved		(const int& iButton,
						 const int& iX, 
						 const int& iY, 
						 const int& iRelX, 
						 const int& iRelY) {}
		virtual void MouseButtonUp	(const int& iButton, 
						 const int& iX, 
						 const int& iY, 
						 const int& iRelX, 
						 const int& iRelY) {}
		virtual void MouseButtonDown	(const int& iButton, 
						 const int& iX, 
						 const int& iY, 
						 const int& iRelX, 
						 const int& iRelY) {}

	public:
		Renderer();
		~Renderer();
		void init();
		void start();

};

#endif