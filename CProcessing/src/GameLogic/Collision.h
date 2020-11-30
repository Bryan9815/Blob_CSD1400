#pragma once
#include "grid.h"
#include <stdbool.h>
#include "Collider.h"

typedef struct
{
	Collider hitbox;
	CP_Vector velocity;
	float rotation;
} Body;

CP_Vector ArrowReflection(Body* entity, CP_Vector n);
CP_Vector Get_CircleRectCOL_Side(Collider circle, Collider rect, CP_Vector v, CP_Vector startPos);
bool GridCollisionCheck(Body* entity);
bool ArrowCollision(Body* entity, CP_Vector startPos);
bool PlayerEntityCollision(Body* player, Body* entity);