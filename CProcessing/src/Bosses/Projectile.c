#include "Projectile.h"
#include "../Player/player.h"

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

void DrawProjectile(Projectile* projectile)
{
	CP_Color WarningColor = CP_Color_Create(255, 0, 0, 255);
	CP_Settings_Fill(WarningColor);
	CP_Graphics_DrawCircle(projectile->body.hitbox.position.x, projectile->body.hitbox.position.y, projectile->body.hitbox.radius*2);
}

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
					projectile->active = false;
					level[i][j].hp--;
					break;
				default:
					break;
				}
			}
		}
	}
}