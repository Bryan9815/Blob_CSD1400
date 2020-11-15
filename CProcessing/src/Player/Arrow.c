#include <cprocessing.h>
#include "Arrow.h"
#include "../Audio/AudioManager.h"

//#include "../GameLogic/grid.h"

int timer = 0;

void DrawArrow(Arrow* arrow)
{
	
	//Draw arrow
	int alpha = 255;
	if (arrow->charging == 1)
	{
		CP_Vector lineend = CP_Vector_Add(arrow->aBody.hitbox.position,CP_Vector_Scale(CP_Vector_Subtract(CP_Vector_Set(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY()), arrow->aBody.hitbox.position),arrow->chargeTimer/ARROW_SSCALE));
		CP_Graphics_DrawLine(arrow->aBody.hitbox.position.x, arrow->aBody.hitbox.position.y, lineend.x, lineend.y);
	}
	CP_Image_DrawAdvanced(arrow->arrowSprite, arrow->aBody.hitbox.position.x, arrow->aBody.hitbox.position.y, arrow->aBody.hitbox.radius, arrow->aBody.hitbox.radius, alpha, arrow->aBody.rotation);
}

void CreateArrow(Arrow* arrow)
{
	arrowColor = CP_Color_Create(255, 0, 0, 255);
	arrow->arrowSprite = CP_Image_Load("././Assets/arrow.png");

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
	arrowSpeed = 500.0f;
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
}

void CalculateRotation(Body* aBody, CP_Vector vector)
{
	if (vector.x < 0)
	{
		aBody->rotation = CP_Vector_Angle(vector, CP_Vector_Set(0.0f, 1.0f)) + 180.0f;
	}
	else
	{
		aBody->rotation = CP_Vector_Angle(vector, CP_Vector_Set(0.0f, -1.0f));
	}
}

void MouseTracking(Body* aBody)
{
	CP_Vector mousePositionVector = CP_Vector_Subtract(CP_Vector_Set(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY()), aBody->hitbox.position);
	CalculateRotation(aBody, mousePositionVector);
}

bool ArrowStateChange(Body* pBody, Body* bBody, Arrow* arrow) // arrow release
{
	switch (arrow->arrowState)
	{
	case RELEASE:
		CalculateNewPosition(arrow, pBody);
		arrow->arrowState = MOTION;
		break;
	case MOTIONLESS:
		ArrowPlayerCollision(arrow, pBody); //pickup player
		IdleArrowBossCollision(&arrow->aBody, bBody);
		//PlayerEntityCollision(&arrow->aBody, bBody);
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT)) // && !COL_IsColliding(arrow->aBody.hitbox, bBody->hitbox)
		{
			CalculateNewPosition(arrow, pBody);
			arrow->arrowState = RECALL;
		}
		break;
	case WITHPLAYER:
		arrow->aBody.hitbox.position = pBody->hitbox.position;
		MouseTracking(&arrow->aBody);
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
	bool arrowBossCol = ArrowBossCollision(arrow, bBody);
	if (currentDistance >= travelDistance)
	{
		arrow->oldPosition = arrow->aBody.hitbox.position;
		arrow->chargeTimer = 0.0f;
		currentDistance = 0.0f;
		travelDistance = 0.0f;
		arrow->arrowState = MOTIONLESS;
		travelTimer = 0.0f;
		arrow->aBody.velocity = CP_Vector_Set(0.0f, 0.0f);
	}
	else
	{
		if (!ArrowCollision(&(arrow->aBody)))
		{
			if (arrow->arrowState == RECALL)
			{
				arrowSpeed = 600.0f;
			}
			else if (arrow->arrowState == MOTION)
			{
				arrowSpeed = 500.0f;
			}

			CP_Vector newVel = CP_Vector_Set(arrow->aBody.velocity.x * arrowSpeed * CP_System_GetDt() * ((arrow->chargeTimer / ARROW_SSCALE) + 1),
					arrow->aBody.velocity.y * arrowSpeed * CP_System_GetDt() * ((arrow->chargeTimer / ARROW_SSCALE) + 1));
			
			//arrow->aBody.hitbox.position = CP_Vector_Add(arrow->aBody.hitbox.position, CP_Vector_Scale(arrow->aBody.velocity, 10));
			arrow->aBody.hitbox.position = CP_Vector_Add(arrow->aBody.hitbox.position, newVel);
			CalculateRotation(&arrow->aBody, arrow->aBody.velocity);
		}
		currentDistance += CP_Vector_Distance(arrow->aBody.hitbox.position, arrow->oldPosition);
		arrow->oldPosition = arrow->aBody.hitbox.position;

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
bool ArrowBossCollision(Arrow* arrow, Body* bBody)
{
	bool dealdamage = false;
	CP_Vector differences = CP_Vector_Subtract(arrow->aBody.hitbox.position, bBody->hitbox.position); //Vector from boss position to arrow position
	if (COL_IsColliding(arrow->aBody.hitbox, bBody->hitbox))
	{

		CP_Matrix rotatedir = CP_Matrix_Rotate(bBody->rotation); //rotation matrix
		CP_Vector dir = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, 1.0f)); //rotate based off (0,1) to get direction vector 
		float theta = CP_Vector_Angle(differences, dir); //angle between dir vector and arrow vector
		if (theta >= 150.0f) //Assumes gap is 60 degress wide, May need adjusting
		{
			dealdamage = true;
			currentDistance = 0.0f;
			travelDistance = 0.0f;
			return dealdamage;
		}
		else
		{
			//r = d-2(d.n)n
			CP_Sound_Play(ReflectSFX);
			CP_Vector normal = CP_Vector_Normalize(differences);
			float dotproduct = CP_Vector_DotProduct(arrow->aBody.velocity, normal);
			CP_Vector resultantVector = CP_Vector_Subtract(arrow->aBody.velocity, CP_Vector_Scale(normal, 2 * dotproduct));
			//Adjust arrow rotation Here
			arrow->aBody.velocity = resultantVector;
			CalculateRotation(&arrow->aBody, arrow->aBody.velocity);
			arrow->aBody.hitbox.position = CP_Vector_Add(CP_Vector_Add(arrow->aBody.hitbox.position, CP_Vector_Scale(resultantVector, 10)), bBody->velocity);
		}

	}
	return dealdamage;
}

void IdleArrowBossCollision(Body* aBody, Body* bBody)
{
	//float dist = aBody->hitbox.radius + bBody->hitbox.radius;
	//float currdist = CP_Vector_Distance(arrow->aBody.hitbox.position, bBody->hitbox.position);
	if (COL_IsColliding(aBody->hitbox,bBody->hitbox))
	{
		CP_Vector differences = CP_Vector_Subtract(aBody->hitbox.position, bBody->hitbox.position);
		float mag = CP_Vector_Length(differences); //magnitude of diffvector
		float resMag = aBody->hitbox.radius + bBody->hitbox.radius; //magnitude of resultant vector
		CP_Vector resultantVector = CP_Vector_Scale(differences, (resMag - mag) / mag);
		//CP_Vector newPos = CP_Vector_Add(aBody->hitbox.position, resultantVector);
		aBody->velocity = resultantVector;
		GridCollisionCheck(aBody);
		aBody->hitbox.position = CP_Vector_Add(aBody->hitbox.position, aBody->velocity);
	}

	
}
