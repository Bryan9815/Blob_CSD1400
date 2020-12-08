//---------------------------------------------------------
// file:	Boss2.h
// author:	[Teh Kai Hong Bryan]
// email:	[t.kaihongbryan@digipen.edu]
//
// brief:	Header file for Boss2.c
//
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include <cprocessing.h>
#include "Boss.h"
#include "../GameLogic/grid.h"

typedef enum BossState2
{
	IDLE_B2,			//normal
	DASH,
	SHOOT_1,
	SHOOT_2,
	SHOOT_3,
	STUNNED_B2,
	DEFEAT_B2
} BossState2;

//functions specifically for boss 1 here
Collider Attack;
CP_Vector ChargeTarget, ChargeDir;

//void Shield1Draw(Boss armorboss);
void Boss2Init(void);
void B2_StateChange(Player player);
void Boss2Draw();
void Boss2Battle(void);
void Boss2Exit(void);