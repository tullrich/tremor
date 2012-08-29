#include <cstdio>
#include "tUtilities.h"

void dumpRawBytes(int size, char *pod) {
	for (int i = 0; i < size; i++) {
		printf("%i,", pod[i]);
	}
	printf("\n");
}