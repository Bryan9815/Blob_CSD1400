#pragma once
#include <cprocessing.h>
#include "../Player/player.h"
#include "../GameLogic/Collider.h"

//general functions (init, drawing, movement) for all bosses are here
typedef enum
{
	IDLE,			//normal, should be moving toward player
	ATTACK_NEAR,	//attacks player if within a certain distance
	ATTACK_FAR,		//charges at player if beyond that distance
	STUNNED,		//boss cannot move
	DEFEAT			//boss is dead, stop boss functions
} BossState;

typedef struct
{
	CP_Vector Position; //Position vector of boss
	float Rotation;		//orientation of boss for drawing
	int Health;			//Health of boss
	float Radius;		//Radius of boss for drawing
	float Speed;		//Movement speed of boss (not charge speed of boss 1)
	BossState State;	//determines boss actions
	Collider Hitbox;	//collision for boss
} Boss;

typedef enum
{
	NOT_ATTACK,
	WARNING,
	ATTACK
} AttackState;

Boss ArmorSlime; //currently only 1 boss

void BossInit(Boss* currentboss, int health, float size);
void BossDraw(Boss currentboss);
void BossMovement(Boss* currentboss, Player player);