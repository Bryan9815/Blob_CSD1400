#pragma once
#include <cprocessing.h>
#include "Boss.h"
#include "../GameLogic/grid.h"

//functions specifically for boss 1 here
CP_Image shield;
AttackState NearAttack, FarAttack;
Collider Attack;
CP_Vector ChargeTarget, ChargeDir;

//void Shield1Draw(Boss armorboss);
void Boss1Init(void);
void AttackNear(Boss* armorboss, Player* player);
void AttackNearDraw(Boss armorboss);
void AttackCharge(Player* player, Boss* armorboss, GridUnit *grid);
void AttackFarDraw(Boss armorboss);
void StunTimer(Boss* currentboss);
void B1_StateChange(Player player, Boss* currentboss);
void Boss1Action(void);
void Boss1Battle(void);
void Boss1Draw(Boss armorboss);
void Boss1Exit(void);