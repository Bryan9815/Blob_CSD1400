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