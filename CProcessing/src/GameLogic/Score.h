#pragma once
#include <cprocessing.h>
#include "../Bosses/Boss.h"
#include "../Player/player.h"
#define BUFFERSIZE 10

float Score;
float tutTimer, Boss1Timer;
char Rank;

void StageTime(float *timer);
float CalculateScore(float time, bool win);
void CalculateRank(float score);
void DisplayScore(float scoreCenterX, float scoreCenterY, float time, float score);