#pragma once
#include "../Player/player.h"
#include "grid.h"
#include <stdbool.h>
#include "Collider.h"

typedef struct
{
	Collider hitbox;
	CP_Vector velocity;
} Body;

void CollisionCheck(Player* player, GridUnit* level);
