#include "mD3Entity.h"
#include "SDL/SDL_opengl.h"

MD3Entity::MD3Entity(MD3Mesh *model) : Entity() {
	this->model = model;
	printf("CREATED ENTITY %i\n", id);
}

MD3Entity::MD3Entity(const MD3Entity &e) {
	this->model = e.model;
	printf("MD3 Copy Constructor %i\n", id);
}

MD3Entity::~MD3Entity() {

	printf("Destroying ENTITY %i\n", id);
}

void MD3Entity::think(float afTimeStep) {
}

int CheckGLErrors()
{
  int errCount = 0;
  for(GLenum currError = glGetError(); currError != GL_NO_ERROR; currError = glGetError())
  {
    printf("currError: %#x\n", currError);
    ++errCount;
  }
 
  return errCount;
}

static GLint vertices[] = {125, 125, 1, 
					100, 325, 1,
					175, 25, 1,
					175, 325, 1,
					250, 25, 1,
					325, 325, 1};
static GLfloat colors[] = {1.0, 1.0, 1.0, 1.0,
                          1.0, 1.0, 1.0, 1.0,
                          1.0, 1.0, 1.0, 1.0,
                          1.0, 1.0, 1.0, 1.0,
                          1.0, 1.0, 1.0, 1.0,
                          1.0, 1.0, 1.0, 1.0,};


void drawDebug() {
	//glColorPointer(4, GL_FLOAT, 0, colors);
	//printf("vertice location %#x\n", vertices);
	glVertexPointer(3, GL_INT, 0, vertices);

	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void MD3Entity::drawElements(int index) {
	MD3Surface *s = &model->surfaces[index];
	int num_vertices = s->getNumVertices();
	//printf("num_vertices %i\n", num_vertices);

	glVertexPointer(3, GL_SHORT, sizeof(md3_vertex), s->xyznormals);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, num_vertices, GL_UNSIGNED_INT, s->triangles);
	glDisableClientState(GL_VERTEX_ARRAY);


	//printf("drawSurface end\n");
	CheckGLErrors();
}

void MD3Entity::drawSurface(int index) {
	MD3Surface *s = &model->surfaces[index];

	//glEnable( GL_TEXTURE_2D );
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glTexCoordPointer( 2, GL_FLOAT, 0, s->sts );
	drawElements(index);

	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnable( GL_TEXTURE_2D );

}


void MD3Entity::onDraw() {

	for (int i = 0; i < model->getNumSurfaces(); i++) {
		drawSurface(i);
	}
	
}

