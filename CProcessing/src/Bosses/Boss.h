#pragma once
#include <cprocessing.h>
#include "../Player/player.h"

typedef struct
{
	CP_Vector Position; //Position vector of boss
	int Health;			//Health of boss
	float Size;			//Radius of boss for drawing
	float Speed;		//Movement speed of boss (not charge speed of boss 1)
} Boss;

Boss ArmorSlime; //currently only 1 boss

void CreateBoss(Boss* currentboss, int health, float size);
void BossDraw(Boss currentboss);
void BossMovement(Boss* currentboss/*, Player* player*/); //remove all comments once player is added