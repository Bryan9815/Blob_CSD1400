#include <cprocessing.h>
#include "Arrow.h"

void CreateArrow(Arrow* arrow)
{
	arrowColor = CP_Color_Create(255, 0, 0, 200);

	arrow->currentPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	arrow->newPosition = arrow->currentPosition;
	arrow->oldPosition = arrow->currentPosition;
	arrow->dir = CP_Vector_Set(0.0f, 0.0f);

	arrow->width = CP_System_GetWindowWidth() / 25.0f;

	arrow->forceScale = 0;
	arrow->forceTimer = 0.0f;

	playerArrowState = WITHPLAYER;
}

void ArrowRelease(Arrow* arrow) // arrow release
{
	arrow->forceScale = (DEFAULT_FORCE + arrow->forceTimer) / 20;
	arrow->dir.x = CP_Input_GetMouseX() - arrow->oldPosition.x;
	arrow->dir.y = CP_Input_GetMouseY() - arrow->oldPosition.y;
	arrow->dir = CP_Vector_Scale(arrow->dir, arrow->forceScale);
	arrow->newPosition = CP_Vector_Add(arrow->oldPosition, arrow->dir);
	//arrow->newPosition = CP_Vector_Add(arrow->position, )
	arrow->forceTimer = 0.0f;
	playerArrowState = MOTION;
}

void ArrowPhysics(Arrow* arrow)
{
	if (playerArrowState == MOTION)
	{
		arrow->currentPosition = arrow->newPosition;
		//barycentirc maybe, newPosition = oldPosition + t(dir), where t is based off delta time and forcescale.
		//t = distance between oldPos and newPos / 5?
	}
}