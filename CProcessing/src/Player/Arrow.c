#include <cprocessing.h>
#include "arrow.h"

void CreateArrow(Arrow* arrow)
{
	arrowColor = CP_Color_Create(255, 0, 0, 200);

	arrow->position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	arrow->newPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	arrow->dir = CP_Vector_Set(0.0f, 0.0f);

	arrow->width = CP_System_GetWindowWidth() / 23.0f;

	arrow->force = 0;
	arrow->forceTimer = 0.0f;

	arrow->canShoot = 1;
}

void ArrowRelease(Arrow* arrow)
{
	//arrow->newPosition = CP_Vector_Add(arrow->position, )
}