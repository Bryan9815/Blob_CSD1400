//---------------------------------------------------------
// file:	Boss.h
// author:	[Koh Le An Leonard]
// email:	[l.koh@digipen.edu]
//
// brief:	Header for functions in Boss.c
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <cprocessing.h>
#include "../Player/player.h"
#include "../GameLogic/grid.h"
#include "../Screen/scr_level_1.h"
#include "../GameLogic/Collision.h"

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
	CP_Image bosssprite;//image for boss
	float Rotation;		//orientation of boss for drawing
	int Health;			//Health of boss
	int maxHealth;		//Max health of boss
	BossState State;	//determines boss actions
	Body BossBody;		//position and velocity of boss movement for collision
	int bossAlpha;		//for invincibility
} Boss;

typedef enum
{
	NOT_ATTACK,
	WARNING,
	ATTACK
} AttackState;


Boss ArmorSlime, Boss2; //currently only 1 boss

void BossInit(Boss* currentboss, int health, float size, CP_Vector startPos);
void BossDraw(Boss currentboss);
void BossHealthDraw(Boss boss);
void BossMovement(Boss* currentboss, Player player, GridUnit* grid);
void BossRotation(Boss* currentboss, CP_Vector position);
void BossDamage(bool* hit, Boss* boss);