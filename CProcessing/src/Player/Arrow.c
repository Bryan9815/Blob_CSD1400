#include <cprocessing.h>
#include "Arrow.h"

//#include "../GameLogic/grid.h"

int timer = 0;

void DrawArrow(Arrow* arrow)
{
	
	//CP_Graphics_DrawRectAdvanced(player->arrow.currentPosition.x, player->arrow.currentPosition.y, player->arrow.width, player->arrow.width, player->rotation + 45.0f, 1);
	//Draw arrow
	if (arrow->charging == 1)
	{
		//Draw arrow
		CP_Settings_Fill(CP_Color_Create(255, 255, 0, 100));
	}
	else if (arrow->charging == 0)
	{
		//Draw arrow
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		//CP_Graphics_DrawRectAdvanced(player->arrow.currentPosition.x, player->arrow.currentPosition.y, arrow->.width, player->arrow.width, player->rotation + 45.0f, 1);
	}
	CP_Graphics_DrawEllipseAdvanced(arrow->aBody.hitbox.position.x, arrow->aBody.hitbox.position.y, arrow->aBody.hitbox.radius, arrow->aBody.hitbox.radius, arrow->aBody.rotation); //add rotation bij
}

void CreateArrow(Arrow* arrow)
{
	arrowColor = CP_Color_Create(255, 0, 0, 255);

	//Arrow Positiion
	//arrow->currentPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	arrow->aBody.hitbox.position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	arrow->newPosition = arrow->aBody.hitbox.position;
	arrow->oldPosition = arrow->aBody.hitbox.position;
	arrow->aBody.velocity = CP_Vector_Set(0.0f, 0.0f);
	arrow->aBody.rotation = 0.0f;

	//Arrow Charge Variables
	arrow->chargeScale = 0;
	arrow->chargeTimer = 0.0f;
	
	//Check for Arrow Charge
	arrow->charging = 0;

	//Hitbox variables
	arrow->aBody.hitbox.shapeType = COL_CIRCLE; //CIRCLE COLLIDER
	arrow->aBody.hitbox.radius = 25.0f;

	arrow->arrowState = WITHPLAYER;

	travelTimer = 0.5f;
	travelDistance = 0.0f;
	currentDistance = 0.0f;
}

//I barely passed math, I don't know what I'm doing
void CalculateNewPosition(Arrow* arrow, Body* pbody)
{
	if (arrow->arrowState == RELEASE)	//Release Arrow Calculation
	{
		arrow->oldPosition = pbody->hitbox.position;
		arrow->chargeScale = (DEFAULT_FORCE + (arrow->chargeTimer));
		arrow->aBody.velocity = CP_Vector_Subtract(CP_Vector_Set(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY()), arrow->oldPosition);
		arrow->newPosition = CP_Vector_Add(arrow->oldPosition, CP_Vector_Scale(arrow->aBody.velocity, arrow->chargeScale / 30));
	}
	else if (arrow->arrowState == MOTIONLESS)	//Recall Arrow Calculation
	{
		arrow->oldPosition = arrow->aBody.hitbox.position;
		arrow->newPosition = pbody->hitbox.position;
		arrow->aBody.velocity = CP_Vector_Subtract(pbody->hitbox.position, arrow->oldPosition);
	}

	//arrow->travelVector = CP_Vector_Normalize(arrow->travelVector); //Original Vector
	arrow->aBody.velocity = CP_Vector_Normalize(arrow->aBody.velocity);
	travelDistance = CP_Vector_Distance(arrow->oldPosition, arrow->newPosition);
	arrow->chargeTimer = 0.0f;
}

bool ArrowStateChange(Body* pBody, Body* bBody, Arrow* arrow) // arrow release
{
	switch (arrow->arrowState) {
	case RELEASE:
		CalculateNewPosition(arrow, pBody);
		arrow->arrowState = MOTION;
		break;
	case MOTIONLESS:
		ArrowPlayerCollision(arrow, pBody); //pickup player
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
		{
			CalculateNewPosition(arrow, pBody);
			arrow->arrowState = RECALL;
		}
		break;
	case WITHPLAYER:
		arrow->aBody.hitbox.position = pBody->hitbox.position;
		break;
	default:
		break;
	}


	if (arrow->arrowState == MOTION || arrow->arrowState == RECALL)
	{
		bool hit = ArrowInMotion(arrow, bBody);
		return hit;
	}
	return false;
}

bool ArrowInMotion(Arrow* arrow, Body* bBody)
{
	// travel chargeScale in 1 sec
	// every 0.5 seconds, arrow moves 30*normalizeddir
	bool arrowBossCol = ArrowBossCollision(&arrow->aBody, bBody);
	if (currentDistance >= travelDistance)
	{
		arrow->oldPosition = arrow->aBody.hitbox.position;
		currentDistance = 0.0f;
		travelDistance = 0.0f;
		arrow->arrowState = MOTIONLESS;
		travelTimer = 0.0f;
	}
	else
	{
		//travelTimer += CP_System_GetDt();
		//if (travelTimer >= 0.0)
		//{
		if (!ArrowCollision(&(arrow->aBody), level[0])) arrow->aBody.hitbox.position = CP_Vector_Add(arrow->aBody.hitbox.position, CP_Vector_Scale(arrow->aBody.velocity, 10));
		currentDistance += CP_Vector_Distance(arrow->aBody.hitbox.position, arrow->oldPosition);
		arrow->oldPosition = arrow->aBody.hitbox.position;
		//travelTimer -= travelTimer;
		//travelTimer -= CP_System_GetDt();
		//}
	}
	return arrowBossCol;
}

void ArrowPlayerCollision(Arrow* arrow, Body* pBody)
{
	if (COL_IsColliding(arrow->aBody.hitbox, pBody->hitbox) == true)
	{
		arrow->aBody.hitbox.position = pBody->hitbox.position;
		arrow->oldPosition = pBody->hitbox.position;
		arrow->newPosition = pBody->hitbox.position;
		arrow->arrowState = WITHPLAYER;
	}
}


//end me now
bool ArrowBossCollision(Body* arrow, Body* bBody)
{
	bool dealdamage = false;
	CP_Vector differences = CP_Vector_Subtract(arrow->hitbox.position, bBody->hitbox.position); //Vector from boss position to arrow position
	if (COL_IsColliding(arrow->hitbox, bBody->hitbox))
	{
		CP_Matrix rotatedir = CP_Matrix_Rotate(bBody->rotation); //rotation matrix
		CP_Vector dir = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, 1.0f)); //rotate based off (0,1) to get direction vector 
		float theta = CP_Vector_Angle(differences, dir); //angle between dir vector and arrow vector
		if (theta >= 150.0f ) //Assumes gap is 60 degress wide, May need adjusting
		{
			dealdamage = true;
			currentDistance = 0.0f;
			travelDistance = 0.0f;
			return dealdamage;
		}
		else
		{
			//r = d-2(d.n)n
			
			CP_Vector normal = CP_Vector_Normalize(differences);
			float dotproduct = CP_Vector_DotProduct(arrow->velocity, normal);
			CP_Vector resultantVector = CP_Vector_Subtract(arrow->velocity, CP_Vector_Scale(normal,2*dotproduct));
			arrow->velocity = resultantVector;
			arrow->hitbox.position = CP_Vector_Add(CP_Vector_Add(arrow->hitbox.position, CP_Vector_Scale(resultantVector,10)),bBody->velocity);
		}
	}
	return dealdamage;

}

