#include <cstdio>
#include "renderer.h"

int main(int argv, char **args)
{
	Renderer r;
	r.init();
	
	r.start();

	return true;
}