#pragma once
#include <cprocessing.h>
#include "../GameLogic/Collision.h"

#define DEFAULT_FORCE 30.0f
#define MAX_FORCE 60.0f
#define ARROW_SSCALE 45

float arrowSpeed;
CP_Color		arrowColor;

typedef enum
{
	RELEASE,
	RECALL,
	WITHENTITY,
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

	float		charge;
	int			charging;

	float		travelDistance,
				currentDistance;

	Body		aBody;

} Arrow;

void CreateArrow(Arrow* arrow);
void DrawArrow(Arrow* arrow);

void CalculateRelease(Arrow* arrow, Body* entity, CP_Vector pos);
void CalculateRecall(Arrow* arrow, Body* entity);
void CalculateRotation(Body* aBody, CP_Vector vector);

void MouseTracking(Body* aBody);

void IdleArrowCollision_Circle(Body* aBody, Body* entity);
void ArrowInMotion(Arrow* arrow);

void ArrowPlayerCollision(Arrow* arrow, Body* pBody);
bool ArrowBoss1Collision(Arrow* arrow, Body* bBody);