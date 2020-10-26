#pragma once
#include <cprocessing.h>
#include "Boss.h"

//functions specifically for boss 1 here
CP_Image shield;
AttackState NearAttack, FarAttack;

void Shield1Draw(Boss armorboss);
void AttackNear(Boss* armorboss, Player* player);
void AttackNearDraw(Boss* armorboss);
void AttackCharge(Player* player, Boss* armorboss/*, GridUnit* grid*/);
void AttackFarDraw(Boss* armorboss, Player player);
void StunTimer(Boss currentboss);
void B1_StateChange(Player player, Boss* currentboss);
void BossAction(Player player);
void Boss1Battle(Player player);