//---------------------------------------------------------
// file:	Projectile.h
// author:	[Teh Kai Hong Bryan]
// email:	[t.kaihongbryan@digipen.edu]
//
// brief:	Header file for Projectile.c
//
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include <cprocessing.h>
#include "../GameLogic/Collision.h"

typedef struct Projectile
{
	CP_Vector direction;
	Body body;
	float speed;
	bool active;
}Projectile;

Projectile CreateProjectile(CP_Vector pos, CP_Vector dir, float vel);
void DrawProjectile(Projectile* projectile);
void UpdateProjectile(Projectile *projectile);