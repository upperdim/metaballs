#include <stdio.h>
#include <stdbool.h>

#include "debug.h"

bool debugMode = false;

void print_debug_info(double deltaTime)
{
	if (debugMode) {
		printf("dt: %lf - FPS: %d\n", deltaTime, (int) (1000 / deltaTime));
	}
}
