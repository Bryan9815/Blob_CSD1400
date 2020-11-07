#pragma once
#include <cprocessing.h>
#include "../GameLogic/Collision.h"

#define DEFAULT_FORCE 50.0f

CP_Color		arrowColor;

typedef enum
{
	RELEASE,
	RECALL,
	WITHPLAYER,
	MOTION,
	MOTIONLESS
} ArrowState;


typedef struct
{
	CP_Image	arrowSprite;
	ArrowState  arrowState;

	CP_Vector	oldPosition,
				newPosition;

	float		chargeTimer,
				chargeScale;

	int			charging;
	Body		aBody;

} Arrow;

float 	travelTimer, travelDistance, currentDistance; 

void CreateArrow(Arrow* arrow);
void DrawArrow(Arrow* arrow);
bool ArrowStateChange(Body* pBody, Body* bBody, Arrow* arrow);
void CalculateNewPosition(Arrow* arrow, Body* pBody);
bool ArrowInMotion(Arrow* arrow, Body* bBody);
void MouseTracking(Body* aBody);
void ArrowPlayerCollision(Arrow* arrow, Body* pBody);
bool ArrowBossCollision(Body* arrow, Body* bBody);