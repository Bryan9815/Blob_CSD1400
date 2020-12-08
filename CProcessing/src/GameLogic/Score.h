//---------------------------------------------------------
// file:	Score.h
// author:	[Koh Le An Leonard]
// email:	[l.koh@digipen.edu]
//
// brief:	Header for functions in Score.c
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <cprocessing.h>
#include "../Bosses/Boss.h"
#include "../Player/player.h"
#define BUFFERSIZE 10

float Score;
float tutTimer, Boss1Timer, Boss2Timer;
char Rank;

void StageTime(float *timer);
float CalculateScore(float time, bool win);
void CalculateRank(float score);
void DisplayScore(float scoreCenterX, float scoreCenterY, float time, float score);