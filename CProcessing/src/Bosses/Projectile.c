//---------------------------------------------------------
// file:	Projectile.c
// author:	[Teh Kai Hong Bryan]
// email:	[t.kaihongbryan@digipen.edu]
//
// brief:	Projectile object
//
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "Projectile.h"
#include "../Player/player.h"

// Creates a projectile with the stated position, direction and velocity
Projectile CreateProjectile(CP_Vector pos, CP_Vector dir, float vel)
{
	Projectile newProjectile;
	newProjectile.body.hitbox.position = pos;
	newProjectile.direction = dir;
	newProjectile.speed = vel;
	newProjectile.body.velocity = CP_Vector_Scale(newProjectile.direction, newProjectile.speed);
	newProjectile.body.hitbox.shapeType = COL_CIRCLE;
	newProjectile.body.hitbox.radius = 10.f;
	newProjectile.active = true;
	return newProjectile;
}

// Draws projectile
void DrawProjectile(Projectile* projectile)
{
	CP_Color WarningColor = CP_Color_Create(255, 0, 0, 255);
	CP_Settings_Fill(WarningColor);
	CP_Graphics_DrawCircle(projectile->body.hitbox.position.x, projectile->body.hitbox.position.y, projectile->body.hitbox.radius*2);
}

// Updates projectile
void UpdateProjectile(Projectile *projectile)
{
	projectile->body.hitbox.position = CP_Vector_Add(projectile->body.velocity, projectile->body.hitbox.position);

	if (COL_IsColliding(projectile->body.hitbox, newPlayer.pBody.hitbox) && playerState != DODGING) //check if player is hit by attack
	{
		newPlayer.health = 0;
	}

	for (int i = 0; i < GetLevelWidth(); i++)
	{
		for (int j = 0; j < GetLevelHeight(); j++)
		{
			if (COL_IsColliding(level[i][j].collider, projectile->body.hitbox))
			{
				switch (level[i][j].gridType)
				{
				case GE_WALL:
					projectile->active = false;
					break;
				case GE_PILLAR:
					if (level[i][j].isActive == true)
					{
						projectile->active = false;
						level[i][j].hp--;
					}
					break;
				default:
					break;
				}
			}
		}
	}
}