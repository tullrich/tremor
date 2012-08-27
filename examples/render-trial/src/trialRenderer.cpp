#include "trialRenderer.h"

TrialRenderer::TrialRenderer(int num_entities, MD3Entity *entities, tImage *img) {
	printf("TrialRenderer Constructor\n");
	this->num_entities = num_entities;
	this->e            = entities;
	
	eyeX               = 1;
	eyeY               = 1;
	eyeZ               = 1;
	centerY            = 0;
	centerZ            = 0;
	centerX            = 100;
	upX                = 0;
	upZ                = 0;
	upY                = 1;

	this->img = img;
	texname = 0;
}

void TrialRenderer::onLoop(float ts) {

	// forward and back
	if (keyboard.isKeyDown(SDLK_s)) {
		printf("S pressed\n");
		eyeZ -= 10;
	} else if(keyboard.isKeyDown(SDLK_w)) {
		printf("W pressed\n");
		eyeZ += 10;
	}

	// left and right
	if (keyboard.isKeyDown(SDLK_a)) {
		printf("A pressed\n");
		eyeX -= 10;
	} else if(keyboard.isKeyDown(SDLK_d)) {
		printf("D pressed\n");
		eyeX += 10;
	}

	// up and down
	if (keyboard.isKeyDown(SDLK_UP)) {
		printf("Up pressed\n");
		eyeY -= 10;
	} else if(keyboard.isKeyDown(SDLK_DOWN)) {
		printf("Down pressed\n");
		eyeY += 10;
	}

}

void TrialRenderer::onRender() {
	
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt(eyeX , eyeY , eyeZ , centerX , centerY , centerZ , upX , upY , upZ);

	//printf("eyeX %f, eyeY %f, eyeZ %f, centerX %f, centerY %f, centerZ %f, upX %f, upY %f, upZ %f\n", eyeX , eyeY , eyeZ , centerX , centerY , centerZ , upX , upY , upZ);

	for (int i = 0; i < num_entities; i++) {
		//printf("onRender calling object %i\n", i);
		e[i].onDraw();
	}

   //glEnable(GL_TEXTURE_2D);
   //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   //glBindTexture(GL_TEXTURE_2D, texname);
   //glBegin(GL_QUADS);
   //glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
   //glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
   //glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
   //glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);

   //glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
   //glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
   //glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
   //glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
   //glEnd();
   //glDisable(GL_TEXTURE_2D);
	//((*e)[0]).onDraw();
}

void TrialRenderer::onInit() {
	SDL_WM_SetCaption( "Trial Renderer", 0 );

	//glEnable( GL_TEXTURE_2D );
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
 
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	 
	glViewport( 0, 0, 640, 480 );
	 
	glClear( GL_COLOR_BUFFER_BIT );
	 
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	 
	//glOrtho(0.0f, 640, 480, 0.0f, -1000.0f, 1000.0f);
	gluPerspective(90, 640/480, .1, 10000);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	/*glGenTextures(1, &texname);
	glBindTexture(GL_TEXTURE_2D, texname);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, 
                img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                img->pixels);
	*/
}