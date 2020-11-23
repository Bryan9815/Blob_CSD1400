#pragma once
#include <cprocessing.h>
#include "../GameLogic/Collision.h"

typedef struct Projectile
{
	CP_Vector position, direction;
	float velocity;
	Body collision;
}Projectile;

Projectile CreateProjectile(CP_Vector pos, CP_Vector dir, float vel);
void DrawProjectile(Projectile* projectile);
void UpdateProjectile(Projectile *projectile);