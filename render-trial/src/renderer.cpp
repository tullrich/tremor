#include "renderer.h"

Renderer::Renderer() {
	screen        = 0;
	continue_loop = true;
}

Renderer::~Renderer() {
	SDL_Quit();
}

void Renderer::init() {
	SDL_WM_SetCaption( "Tremor", 0 );

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    }

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_DOUBLEBUF);
	if (screen == NULL) {
		fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
	}

	SDL_WM_SetCaption( "Tremor", 0 );
}

void Renderer::start() {
	while (continue_loop) {
		pumpInput();
		render();
	}
}

void Renderer::pumpInput()
{
	// Poll for events, and handle the ones we care about.
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) 
	{
		switch ( event.type ) 
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				continue_loop = false;
				break;
			}
 
			KeyDown( event.key.keysym.sym );
			break;
 
		case SDL_KEYUP:
			KeyUp( event.key.keysym.sym );
			break;
 
		case SDL_QUIT:
			continue_loop = false;
			break;
 
		case SDL_MOUSEMOTION:
			MouseMoved(
				event.button.button, 
				event.motion.x, 
				event.motion.y, 
				event.motion.xrel, 
				event.motion.yrel);
			break;
 
		case SDL_MOUSEBUTTONUP:
			MouseButtonUp(
				event.button.button, 
				event.motion.x, 
				event.motion.y, 
				event.motion.xrel, 
				event.motion.yrel);
			break;
 
		case SDL_MOUSEBUTTONDOWN:
			MouseButtonDown(
				event.button.button, 
				event.motion.x, 
				event.motion.y, 
				event.motion.xrel, 
				event.motion.yrel);
			break;
		} 
	} 
}

void Renderer::render() {
 
	SDL_FillRect( screen, 0, SDL_MapRGB( screen->format, 0, 0, 0 ) );
 
	// Lock surface if needed
	if ( SDL_MUSTLOCK( screen ) )
		if ( SDL_LockSurface( screen ) < 0 )
			return;
 
	
 
	// Unlock if needed
	if ( SDL_MUSTLOCK( screen ) ) 
		SDL_UnlockSurface( screen );
 
	// Tell SDL to update the whole gScreen
	SDL_Flip( screen );
}