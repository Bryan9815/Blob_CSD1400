#include <cprocessing.h>
#include <stdio.h>
#include "../Bosses/Boss.h"
#include "../Player/player.h"
#include "Score.h"

int pDeaths = 0, deathCount = 0;

void StageTime(float *timer)
{
	*timer += CP_System_GetDt();
}

float CalculateScore(float time, bool lose)
{
	float totalScore = 0;
	float timeScore = 0;
	float deathScore = 0;

	//Time calculation
	if (time >= 300.f)
	{
		timeScore = 0;
	}
	else
	{
		timeScore = 3000.f - (10.f * time);
	}

	if (!lose) //if player wins
	{
		//Death calculation
		if (pDeaths >= 10)
		{
			deathScore = 0;
		}
		else
		{
			deathScore = 3000.f - (pDeaths * 300.f);
		}

		totalScore += 10000.f + timeScore + deathScore;
		deathCount = pDeaths; //save player deaths for score display
		pDeaths = 0; //reset player deaths for future playing
	}
	else //if player loses
	{
		totalScore += timeScore;
		pDeaths++;
		deathCount = pDeaths; //save player deaths for score display
	}
	return totalScore;
}

void DisplayScore(float scorePosX, float scorePosY, float time, float score)
{
	char scoreString[BUFFERSIZE];
	char deathString[BUFFERSIZE];
	char timeString[BUFFERSIZE];
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(50.f);

	//make strings for time, deaths and scores
	sprintf_s(timeString, BUFFERSIZE, "Time: %.2fs", time);
	sprintf_s(deathString, BUFFERSIZE, "Deaths: %d", deathCount);
	sprintf_s(scoreString, BUFFERSIZE, "Score: %d", (int)score);

	//display strings
	CP_Font_DrawText(scoreString, scorePosX, scorePosY);
	CP_Font_DrawText(timeString, scorePosX - (float)(CP_System_GetWindowWidth() / 4), scorePosY);
	CP_Font_DrawText(deathString, scorePosX + (float)(CP_System_GetWindowWidth() / 4), scorePosY);
}