#include "Projectile.h"

Projectile CreateProjectile(CP_Vector pos, CP_Vector dir, float vel)
{
	Projectile newProjectile;
	newProjectile.position = pos;
	newProjectile.direction = dir;
	newProjectile.velocity = vel;
	return newProjectile;
}

void DrawProjectile(Projectile* projectile)
{
	CP_Color WarningColor = CP_Color_Create(255, 0, 0, 255);
	CP_Settings_Fill(WarningColor);
	CP_Graphics_DrawCircle(projectile->position.x, projectile->position.y, 20.f);
}

void UpdateProjectile(Projectile *projectile)
{
	projectile->position = CP_Vector_Add(CP_Vector_Scale(projectile->direction, projectile->velocity), projectile->position);
}