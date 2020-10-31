#include <cprocessing.h>
#include "Arrow.h"
#include "../GameLogic/grid.h"

void CreateArrow(Arrow* arrow)
{
	arrowColor = CP_Color_Create(255, 0, 0, 255);

	arrow->currentPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	arrow->newPosition = arrow->currentPosition;
	arrow->oldPosition = arrow->currentPosition;
	arrow->dir = CP_Vector_Set(0.0f, 0.0f);

	//arrow->radius = ;

	arrow->chargeScale = 0;
	arrow->chargeTimer = 0.0f;

	arrow->charging = 0;

	arrow->hitBox.shapeType = COL_CIRCLE; //CIRCLE COLLIDER
	arrow->hitBox.position = arrow->currentPosition;
	arrow->hitBox.radius = CP_System_GetWindowWidth() / 25.0f;

	playerArrowState = WITHPLAYER;

	travelTimer = 0.0f;
	travelDistance = 0.0f;
}

void CalculateNewPosition(Arrow* arrow, Body pbody)
{
	arrow->oldPosition = arrow->currentPosition;
	if (playerArrowState == RELEASE)
	{
		arrow->chargeScale = (DEFAULT_FORCE + (arrow->chargeTimer));
		arrow->dir = CP_Vector_Subtract(CP_Vector_Set(
			CP_Input_GetMouseWorldX(),
			CP_Input_GetMouseWorldY()),
			arrow->oldPosition);
		arrow->newPosition = CP_Vector_Add(arrow->oldPosition, CP_Vector_Scale(arrow->dir, arrow->chargeScale / 30));
	}
	else if (playerArrowState == MOTIONLESS)
	{
		arrow->dir = CP_Vector_Subtract(pbody.hitbox.position,
			arrow->oldPosition);
		arrow->newPosition = pbody.hitbox.position;
	}

	arrow->normalizedDir = CP_Vector_Normalize(arrow->dir);
	travelDistance = CP_Vector_Distance(arrow->oldPosition, arrow->newPosition);
	arrow->chargeTimer = 0.0f;
}

void ArrowInMotion(Arrow* arrow)
{
	//travel chargeScale in 1 sec
	// every 0.5 seconds, arrow moves 30*normalizeddir
	if (CP_Vector_Distance(arrow->oldPosition, arrow->currentPosition) >= travelDistance)
	{
		arrow->oldPosition = arrow->currentPosition;
		playerArrowState = MOTIONLESS;
		travelTimer = 0.0f;
	}
	else
	{
		travelTimer += CP_System_GetDt();
		if (travelTimer >= 0.5)
		{
			arrow->currentPosition = CP_Vector_Add(arrow->currentPosition, CP_Vector_Scale(arrow->normalizedDir,30));
			arrow->hitBox.position = arrow->currentPosition;
			travelTimer -= CP_System_GetDt();
		}

	}

}
void ArrowPlayerCollision(Arrow* arrow, Body pbody)
{
	if (COL_IsColliding(arrow->hitBox, pbody.hitbox) == true)
	{
		arrow->currentPosition = pbody.hitbox.position;
		arrow->oldPosition = pbody.hitbox.position;
		arrow->newPosition = pbody.hitbox.position;
		playerArrowState = WITHPLAYER;
	}
}