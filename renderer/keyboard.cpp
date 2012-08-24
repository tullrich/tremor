#include <iostream>
#include "keyboard.h"
 
Keyboard::Keyboard() {
	keystate = SDL_GetKeyState(NULL);
	debug = false;
}

void Keyboard::toggleDebug(bool enabled) {
	debug = enabled;
}

void Keyboard::refresh() {
	//printf("Refresh\n");
    SDL_Event Event;
    while(SDL_PollEvent(&Event)) {
        OnEvent(&Event);
    }
}

void Keyboard::OnEvent(SDL_Event* Event) {
	//printf("Got one! %i\n", *Event.type);
	CEvent::OnEvent(Event);
}

void Keyboard::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	if (debug) {
		printf("Keydown %i %i %i\n", sym, mod, unicode);
	}
}

void Keyboard::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	if (debug) {
		printf("Keyup %i %i %i\n", sym, mod, unicode);
	}
}

bool Keyboard::isKeyUp(const int keycode) {
	return keystate[keycode] == 0;
}


bool Keyboard::isKeyDown(const int keycode) {
	return keystate[keycode] == 1;
}


void Keyboard::OnExit() {
	exit(0);
}