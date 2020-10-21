#pragma once
#include <cprocessing.h>

typedef struct
{
	CP_Vector Position; //Position vector of boss
	int Health;			//Health of boss
	float Size;			//Radius of boss for drawing
} Boss;

Boss ArmorSlime; //currently only 1 boss

void BossPositioning(Boss currentboss);
void BossDraw(Boss currentboss);