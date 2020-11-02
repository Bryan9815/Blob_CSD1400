#include <cprocessing.h>
#include "Arrow.h"
#include "../Bosses/Boss.h"
//#include "../GameLogic/grid.h"


void CreateArrow(Arrow* arrow)
{
	arrowColor = CP_Color_Create(255, 0, 0, 255);

	//Arrow Positiion
	//arrow->currentPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	arrow->aBody.hitbox.position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	arrow->newPosition = arrow->aBody.hitbox.position;
	arrow->oldPosition = arrow->aBody.hitbox.position;
	arrow->aBody.velocity = CP_Vector_Set(0.0f, 0.0f);

	//Arrow Charge Variables
	arrow->chargeScale = 0;
	arrow->chargeTimer = 0.0f;
	
	//Check for Arrow Charge
	arrow->charging = 0;

	//Hitbox variables
	arrow->aBody.hitbox.shapeType = COL_CIRCLE; //CIRCLE COLLIDER
	arrow->aBody.hitbox.radius = 25;

	playerArrowState = WITHPLAYER;

	travelTimer = 0.0f;
	travelDistance = 0.0f;
	currentDistance = 0.0f;
}

//I barely passed math, I don't know what I'm doing
void CalculateNewPosition(Arrow* arrow, Body pbody)
{
	if (playerArrowState == RELEASE)	//Release Arrow Calculation
	{
		arrow->oldPosition = pbody.hitbox.position;
		arrow->chargeScale = (DEFAULT_FORCE + (arrow->chargeTimer));
		arrow->aBody.velocity = CP_Vector_Subtract(CP_Vector_Set(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY()), arrow->oldPosition);
		arrow->newPosition = CP_Vector_Add(arrow->oldPosition, CP_Vector_Scale(arrow->aBody.velocity, arrow->chargeScale / 30));
	}
	else if (playerArrowState == MOTIONLESS)	//Recall Arrow Calculation
	{
		arrow->oldPosition = arrow->aBody.hitbox.position;
		arrow->newPosition = pbody.hitbox.position;
		arrow->aBody.velocity = CP_Vector_Subtract(pbody.hitbox.position, arrow->oldPosition);
	}

	//arrow->travelVector = CP_Vector_Normalize(arrow->travelVector); //Original Vector
	arrow->aBody.velocity = CP_Vector_Normalize(arrow->aBody.velocity);
	travelDistance = CP_Vector_Distance(arrow->oldPosition, arrow->newPosition);
	arrow->chargeTimer = 0.0f;
}

void ArrowInMotion(Arrow* arrow)
{
	// travel chargeScale in 1 sec
	// every 0.5 seconds, arrow moves 30*normalizeddir
	if (currentDistance >= travelDistance) //temp, only woirks for release
	{
		arrow->oldPosition = arrow->aBody.hitbox.position;
		currentDistance = 0.0f;
		travelDistance = 0.0f;
		playerArrowState = MOTIONLESS;
		travelTimer = 0.0f;
	}
	else
	{
		travelTimer += CP_System_GetDt();
		if (travelTimer >= 0.5)
		{
			if (!ArrowCollision(&(arrow->aBody), level[0])) arrow->aBody.hitbox.position = CP_Vector_Add(arrow->aBody.hitbox.position, CP_Vector_Scale(arrow->aBody.velocity, 10));
			ArrowBossCollision(&arrow->aBody, &ArmorSlime.BossBody);
			currentDistance += CP_Vector_Distance(arrow->aBody.hitbox.position, arrow->oldPosition);
			arrow->oldPosition = arrow->aBody.hitbox.position;
			travelTimer -= CP_System_GetDt();
		}
	}
}

void ArrowPlayerCollision(Arrow* arrow, Body pbody)
{
	if (COL_IsColliding(arrow->aBody.hitbox, pbody.hitbox) == true)
	{
		arrow->aBody.hitbox.position = pbody.hitbox.position;
		arrow->oldPosition = pbody.hitbox.position;
		arrow->newPosition = pbody.hitbox.position;
		playerArrowState = WITHPLAYER;
	}
}
