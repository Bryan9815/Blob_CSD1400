#pragma once
#include "grid.h"
#include <stdbool.h>
#include "Collider.h"

typedef struct
{
	Collider hitbox;
	CP_Vector velocity;
} Body;

bool CollisionCheck(Body* entity, GridUnit* level);
