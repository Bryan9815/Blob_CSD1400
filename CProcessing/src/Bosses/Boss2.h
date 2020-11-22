#pragma once
#include <cprocessing.h>
#include "Boss.h"
#include "../GameLogic/grid.h"

//functions specifically for boss 1 here
Collider Attack;
CP_Vector ChargeTarget, ChargeDir;

//void Shield1Draw(Boss armorboss);
void Boss2Init(void);
void B2_StateChange(Player player, Boss* currentboss);
void Boss2Draw(Boss armorboss);
void Boss2Battle(void);
void Boss2Exit(void);