#include "renderer.h"
#include <GL/gl.h>

Keyboard Renderer::keyboard = Keyboard();

Renderer::Renderer() {
	printf("Renderer Constructor\n");
	screen  = 0;
	running = true;
}

Renderer::~Renderer() {
	SDL_Quit();
}

void Renderer::init() {

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return;
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );

	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_OPENGL | SDL_DOUBLEBUF );

	if (screen == NULL) {
		fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
		return;
	}

	/*GLenum err = glewInit();
	if (GLEW_OK != err)
	{
	  /* Problem: glewInit failed, something is seriously wrong. 
	  fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}*/

	onInit();
}

void Renderer::start() {    

	Uint32 next_game_tick = SDL_GetTicks();
    float delta;
    Uint32 curTick;

	while (running) {

		curTick = SDL_GetTicks();

		if( curTick > next_game_tick && (delta = (float)(curTick - next_game_tick)) > ONE_GAME_TICK) {
            keyboard.refresh();
            //printf("delta %f %f\n", delta, ONE_GAME_TICK);
            onLoop(delta);

            next_game_tick = curTick + ONE_GAME_TICK;
        }

		render();

        SDL_Delay(5);
	}
}

void Renderer::render() {
 
	clear(screen);

	// Lock surface if needed
	//if ( SDL_MUSTLOCK( screen ) )
	//	if ( SDL_LockSurface( screen ) < 0 )
	//		return;
 
	onRender();
 
	// Unlock if needed
	//if ( SDL_MUSTLOCK( screen ) ) 
	//	SDL_UnlockSurface( screen );

	// Tell SDL to update the whole gScreen
	SDL_GL_SwapBuffers();
}

void Renderer::clear(SDL_Surface* s) {
    SDL_FillRect( s, NULL, 0 );
}