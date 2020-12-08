//---------------------------------------------------------
// file:	Score.c
// author:	[Koh Le An Leonard]
// email:	[l.koh@digipen.edu]
//
// brief:	Functions that are used for calculating score
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <cprocessing.h>
#include <stdio.h>
#include "../Bosses/Boss.h"
#include "../Player/player.h"
#include "Score.h"

CP_Color rankColor;
int pDeaths = 0, deathCount = 0;

//calculate stage time
void StageTime(float *timer)
{
	*timer += CP_System_GetDt();
}

//calculate score for stage
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
		timeScore = 4000.f - (10.f * time);
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
			deathScore = 4000.f - (pDeaths * 400.f);
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

//calculate rank based on score
void CalculateRank(float score)
{
	//set rank
	if (score < 10000.f)
		Rank = 'F';
	else if (score >= 10000.f && score < 11500.f)
		Rank = 'E';
	else if (score >= 11500.f && score < 13000.f)
		Rank = 'D';
	else if (score >= 13000.f && score < 15000.f)
		Rank = 'C';
	else if (score >= 15000.f && score < 16500.f)
		Rank = 'B';
	else if (score >= 16500.f && score < 17500.f)
		Rank = 'A';
	else if (score >= 17500.f)
		Rank = 'S';
	//set rank color
	switch (Rank)
	{
	case 'F':
		rankColor = CP_Color_Create(255, 0, 0, 255); //red
		break;
	case 'E':
		rankColor = CP_Color_Create(155, 155, 155, 255); //grey
		break;
	case 'D':
		rankColor = CP_Color_Create(0, 255, 0, 255); //green
		break;
	case 'C':
		rankColor = CP_Color_Create(0, 255, 255, 255); //light blue
		break;
	case 'B':
		rankColor = CP_Color_Create(204, 153, 255, 255); //purple
		break;
	case 'A':
		rankColor = CP_Color_Create(255, 128, 0, 255); //orange
		break;
	case 'S':
		rankColor = CP_Color_Create(255, 215, 0, 255); //gold
		break;
	default:
		break;
	}
}

//displays score on game over or win
void DisplayScore(float scoreCenterX, float scoreCenterY, float time, float score)
{
	char scoreString[] = "Score:";
	char deathString[] = "Deaths:";
	char timeString[] = "Time:";
	char rankString[] = "Rank:";

	char timeScore[BUFFERSIZE];
	char deathScore[BUFFERSIZE];
	char finalScore[BUFFERSIZE];
	char finalRank[3]; //separate because it will be bigger

	float scorePosX = scoreCenterX + (float)CP_System_GetWindowWidth() / 6;
	float scoreStringX = scoreCenterX - (float)CP_System_GetWindowWidth() / 6;

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(50.f);

	//init strings for time, deaths, score, rank
	sprintf_s(timeScore, BUFFERSIZE, "%.2fs", time);
	sprintf_s(deathScore, BUFFERSIZE, "%d", deathCount);
	sprintf_s(finalScore, BUFFERSIZE, "%d", (int)score);
	sprintf_s(finalRank, 3, "%c", Rank);

	//display strings
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText(scoreString, scoreStringX, scoreCenterY);
	CP_Font_DrawText(timeString, scoreStringX, scoreCenterY - (float)CP_System_GetWindowHeight() / 5);
	CP_Font_DrawText(deathString, scoreStringX, scoreCenterY - (float)CP_System_GetWindowHeight() / 10);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BOTTOM);
	CP_Font_DrawText(rankString, scoreStringX, scoreCenterY + (float)CP_System_GetWindowHeight() / 4);
	
	//display scores
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_RIGHT, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText(finalScore, scorePosX, scoreCenterY);
	CP_Font_DrawText(timeScore, scorePosX, scoreCenterY - (float)CP_System_GetWindowHeight() / 5);
	CP_Font_DrawText(deathScore, scorePosX, scoreCenterY - (float)CP_System_GetWindowHeight() / 10);

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_RIGHT, CP_TEXT_ALIGN_V_BOTTOM);
	CP_Settings_Fill(rankColor);
	CP_Settings_TextSize(250.f);
	CP_Font_DrawText(finalRank, scorePosX, scoreCenterY + (float)CP_System_GetWindowHeight() / 4 + 30.f);
}