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

	arrow->chargeScale = 0;
	arrow->chargeTimer = 0.0f;

	arrow->charging = 0;

	playerArrowState = WITHPLAYER;
}

void CalculateNewPosition(Arrow* arrow)
{
	arrow->chargeScale = (DEFAULT_FORCE + arrow->chargeTimer) / 50;
	arrow->dir.x = CP_Input_GetMouseWorldX() - arrow->oldPosition.x;
	arrow->dir.y = CP_Input_GetMouseWorldY() - arrow->oldPosition.y;
	arrow->dir = CP_Vector_Scale(arrow->dir, arrow->chargeScale);
	arrow->newPosition = CP_Vector_Add(arrow->oldPosition, arrow->dir);
	arrow->chargeTimer = 0.0f;
}

void ArrowInMotion(Arrow* arrow)
{
	arrow->currentPosition = arrow->newPosition;
	playerArrowState = MOTIONLESS;
	//barycentirc maybe, newPosition = oldPosition + t(dir), where t is based off delta time and forcescale.
	//t = distance between oldPos and newPos / 5?
}

void ArrowRecall(Arrow* arrow, CP_Vector playerPos)
{
	arrow->currentPosition = playerPos;
	playerArrowState = WITHPLAYER;
}