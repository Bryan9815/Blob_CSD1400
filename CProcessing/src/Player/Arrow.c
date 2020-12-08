// file:	Arrow.c
// author:	[Lim Zi Qing]
// email:	[ziqing.l@digipen.edu]
//
// brief:	Arrow object with Arrow collision
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <cprocessing.h>
#include "Arrow.h"
#include "../Audio/AudioManager.h"
#include <stdio.h>

//#include "../GameLogic/grid.h"

float timer = 0;
bool arrowhit = false;

//Draw the arrow
void DrawArrow(Arrow* arrow)
{
	//Draw arrow
	int alpha = 255;
	CP_Image_DrawAdvanced(arrow->arrowSprite, arrow->aBody.hitbox.position.x, arrow->aBody.hitbox.position.y, arrow->aBody.hitbox.radius, arrow->aBody.hitbox.radius, alpha, arrow->aBody.rotation);
}

//Initialize the arrow
void CreateArrow(Arrow* arrow)
{
	arrowColor = CP_Color_Create(255, 0, 0, 255);

	//Arrow Positiion
	//arrow->currentPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	arrow->newPosition = arrow->aBody.hitbox.position;
	arrow->oldPosition = arrow->aBody.hitbox.position;
	arrow->aBody.velocity = CP_Vector_Set(0.0f, 0.0f);
	arrow->aBody.rotation = 0.0f;
	
	//Check for Arrow Charge
	arrow->charging = 0;
	arrow->charge = 0.0f;

	//Hitbox variables
	arrow->aBody.hitbox.shapeType = COL_CIRCLE; //CIRCLE COLLIDER

	arrow->arrowState = WITHENTITY;

	arrow->travelDistance = 0.0f;
	arrow->currentDistance = 0.0f;
}

// Calculate the distance travelled by the arrow during release.
void CalculateRelease(Arrow* arrow, Body* entity, CP_Vector pos) 
{
	arrow->oldPosition = entity->hitbox.position;
	arrow->charge = (DEFAULT_FORCE + (arrow->charge));
	arrow->aBody.velocity = CP_Vector_Subtract(pos, arrow->oldPosition);
	arrow->newPosition = CP_Vector_Add(arrow->oldPosition, CP_Vector_Scale(arrow->aBody.velocity, arrow->charge / 30));

	arrow->aBody.velocity = CP_Vector_Normalize(arrow->aBody.velocity);
	arrow->travelDistance = CP_Vector_Distance(arrow->oldPosition, arrow->newPosition);
}

//Calculates the new position and distance of the arrow recall
void CalculateRecall(Arrow* arrow, Body* entity)
{
	arrow->oldPosition = arrow->aBody.hitbox.position;
	arrow->newPosition = entity->hitbox.position;
	arrow->aBody.velocity = CP_Vector_Subtract(entity->hitbox.position, arrow->oldPosition);

	arrow->aBody.velocity = CP_Vector_Normalize(arrow->aBody.velocity);
	arrow->travelDistance = CP_Vector_Distance(arrow->oldPosition, arrow->newPosition);
}

//Calculates rotation of an object based on the axis and a direction
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

//tracks position of mouse for arrow release
void MouseTracking(Body* aBody)
{
	CP_Vector mousePositionVector = CP_Vector_Subtract(CP_Vector_Set(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY()), aBody->hitbox.position);
	CalculateRotation(aBody, mousePositionVector);
}

//Arrow collision with circulr object
void IdleArrowCollision_Circle(Body* aBody, Body* entity) //Push Arrow Away when in contact with circular entity
{
	if (COL_IsColliding(aBody->hitbox, entity->hitbox))
	{
		CP_Vector differences = CP_Vector_Subtract(aBody->hitbox.position, entity->hitbox.position);
		float mag = CP_Vector_Length(differences); //magnitude of diffvector
		float resMag = aBody->hitbox.radius + entity->hitbox.radius; //magnitude of resultant vector
		CP_Vector resultantVector = CP_Vector_Scale(differences, (resMag - mag) / mag);
		//CP_Vector newPos = CP_Vector_Add(aBody->hitbox.position, resultantVector);
		aBody->velocity = resultantVector;
		GridCollisionCheck(aBody);
		aBody->hitbox.position = CP_Vector_Add(aBody->hitbox.position, aBody->velocity);
	}
}

//Arrow pickup
void ArrowPickup(Arrow* arrow, Body* entity)
{
	if (COL_IsColliding(arrow->aBody.hitbox, entity->hitbox) == true)
	{
		arrow->aBody.hitbox.position = entity->hitbox.position;
		arrow->oldPosition = entity->hitbox.position;
		arrow->newPosition = entity->hitbox.position;
		arrow->arrowState = WITHENTITY;
	}
}

//Arrow mnovement
void ArrowInMotion(Arrow* arrow)
{
	if (arrow->currentDistance >= arrow->travelDistance || arrow->arrowState == WITHENTITY)
	{
		arrow->oldPosition = arrow->aBody.hitbox.position;
		arrow->charge = 0.0f;
		arrow->currentDistance = 0.0f;
		arrow->travelDistance = 0.0f;
		arrow->arrowState = MOTIONLESS;
		arrow->aBody.velocity = CP_Vector_Set(0.0f, 0.0f);
	}
	else
	{
		if (arrow->arrowState == MOTION)
		{
			if (!ArrowCollision(&(arrow->aBody),arrow->oldPosition))
			{

				CP_Vector newVel = CP_Vector_Set(arrow->aBody.velocity.x * ARROW_SPEED * CP_System_GetDt() * ((arrow->charge / ARROW_SSCALE) + 1),
					arrow->aBody.velocity.y * ARROW_SPEED * CP_System_GetDt() * ((arrow->charge / ARROW_SSCALE) + 1));

				//arrow->aBody.hitbox.position = CP_Vector_Add(arrow->aBody.hitbox.position, CP_Vector_Scale(arrow->aBody.velocity, 10));
				arrow->aBody.hitbox.position = CP_Vector_Add(arrow->aBody.hitbox.position, newVel);
				CalculateRotation(&arrow->aBody, arrow->aBody.velocity);
			}
		}
		else if (arrow->arrowState == RECALL)
		{
			CP_Vector newVel = CP_Vector_Set(arrow->aBody.velocity.x * ARROW_SPEED * CP_System_GetDt() * ((arrow->charge / ARROW_SSCALE) + 1),
				arrow->aBody.velocity.y * (ARROW_SPEED + 200.0f) * CP_System_GetDt() * ((arrow->charge / ARROW_SSCALE) + 1));

			//arrow->aBody.hitbox.position = CP_Vector_Add(arrow->aBody.hitbox.position, CP_Vector_Scale(arrow->aBody.velocity, 10));
			arrow->aBody.hitbox.position = CP_Vector_Add(arrow->aBody.hitbox.position, newVel);
			CalculateRotation(&arrow->aBody, arrow->aBody.velocity);
			ArrowCollision(&arrow->aBody,arrow->oldPosition);
		}
		arrow->currentDistance += CP_Vector_Distance(arrow->aBody.hitbox.position, arrow->oldPosition);
		arrow->oldPosition = arrow->aBody.hitbox.position;
	}
}