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

bool GridCollisionCheck(Body* entity);
bool ArrowCollision(Body* entity);
bool PlayerEntityCollision(Body* player, Body* entity);