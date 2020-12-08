//---------------------------------------------------------
// file:	scr_credits.c
// author:	[Phang Jia Rong]
// email:	[jiarong.phang@digipen.edu]
//
// brief:	Handles the functionality and update for credits
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <cprocessing.h>
#include "../GameLogic/ScreenManager.h"

static CP_Vector currentPosition, startingOffset;

static CP_Matrix translationMatrix;

float scrollSpeed = 2.0f;
float endTimer = 0.0f;

//Hardcoded DrawCalls for Credits
void CreditsDraw() 
{
	//Start
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	//SKIP
	CP_Settings_TextSize(30);
	CP_Font_DrawText("Space to Skip", (float)CP_System_GetWindowWidth() - 100, ((float)CP_System_GetWindowHeight() / 2 - 40) + currentPosition.y);

	CP_Settings_TextSize(75);
	CP_Font_DrawText("DIGIPEN INSTITUTE OF TECHNOLOGY", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 100);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("Presents", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 175);

	CP_Settings_TextSize(55);
	CP_Font_DrawText("A COLDSOBA PRODUCTION", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 300);
	CP_Settings_TextSize(75);
	CP_Font_DrawText("\"BLOB\"", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 375);

	CP_Settings_TextSize(50);
	CP_Font_DrawText("WWW.DIGIPEN.EDU", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 500);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("ALL CONTENT © 2020 DigiPen Institute of Technology Singapore, ALL RIGHTS RESERVED.", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 600);

	CP_Settings_TextSize(50);
	CP_Font_DrawText("DEVELOPED BY", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 1200);
	
	CP_Settings_TextSize(75);
	CP_Font_DrawText("TEH KAI HONG BRYAN", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 1275);
	CP_Font_DrawText("KOH LE AN LEONARD", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 1350);
	CP_Font_DrawText("LIM ZI QING", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 1425);
	CP_Font_DrawText("PHANG JIA RONG", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 1500);
	
	CP_Settings_TextSize(50);
	CP_Font_DrawText("INSTRUCTORS", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 2100);

	CP_Settings_TextSize(75);
	CP_Font_DrawText("Cheng Ding Xiang", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 2175);
	CP_Font_DrawText("Raymond Teo", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 2250);

	CP_Settings_TextSize(50);
	CP_Font_DrawText("PRESIDENT", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 2400);

	CP_Settings_TextSize(75);
	CP_Font_DrawText("Claude Comair", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() + 2475);

}

void CreditsInit()
{

	currentPosition = CP_Vector_Set((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2);
	CameraInit(&currentPosition, LOCK_PLAYER);

}

void CreditsUpdate()
{
	//Camera Panning
	currentPosition = CP_Vector_Add(currentPosition, CP_Vector_Set(0, +scrollSpeed));
	CameraUpdate(&currentPosition, GetFader());
	
	CreditsDraw();
	
	endTimer += scrollSpeed;

	if (GetBlobInputTriggered(BLOB_INTERACT) || endTimer > 2250 + (float)CP_System_GetWindowHeight() * 4/3) //Ends Credits after last text appears +  4/3 of the screen
	{
		SetGameState(SCR_MAIN_MENU); //Change Back to Main Menu
	}

}


void CreditsExit()
{

}