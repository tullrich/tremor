#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
 
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "CEvent.h"

class Keyboard : public CEvent {
	public:
		// constructor
		Keyboard();

		void toggleDebug(bool enabled);

		// rechecks current keyboard input status
		void refresh();

		void OnEvent(SDL_Event* Event);

		void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

		bool isKeyUp(int keycode);
		bool isKeyDown(int keycode);

		void OnExit();

	private:

		bool debug;
		Uint8 *keystate;
};

#endif