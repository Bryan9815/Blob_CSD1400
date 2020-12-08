// file:	Arrow.h
// author:	[Lim Zi Qing]
// email:	[ziqing.l@digipen.edu]
//
// brief:	Header file for Arrow.c
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <cprocessing.h>
#include "../GameLogic/Collision.h"

#define DEFAULT_FORCE 30.0f
#define MAX_FORCE 60.0f
#define ARROW_SSCALE 45
#define ARROW_SPEED 600.0f

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

	CP_Vector	oldPosition,	//Original position
				newPosition;	//Position to move to

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

void ArrowPickup(Arrow* arrow, Body* entity);