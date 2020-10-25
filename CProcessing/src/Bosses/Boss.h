#pragma once
#include <cprocessing.h>
#include "../Player/player.h"

//general functions (init, drawing, movement) for all bosses are here
enum BossState
{
	IDLE,			//normal, should be moving toward player
	ATTACK_NEAR,	//attacks player if within a certain distance
	ATTACK_FAR,		//charges at player if beyond that distance
	STUNNED,		//boss cannot move
	DEFEAT			//boss is dead, stop boss functions
};

typedef struct
{
	CP_Vector Position; //Position vector of boss
	float Rotation;		//orientation of boss for drawing
	int Health;			//Health of boss
	float Size;			//Radius of boss for drawing
	float Speed;		//Movement speed of boss (not charge speed of boss 1)
	enum BossState State;
} Boss;

Boss ArmorSlime; //currently only 1 boss

void BossInit(Boss* currentboss, int health, float size);
void BossDraw(Boss currentboss);
void BossMovement(Boss* currentboss, Player player);