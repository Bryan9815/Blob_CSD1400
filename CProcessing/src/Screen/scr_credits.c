#include <cprocessing.h>
#include "../GameLogic/ScreenManager.h"

static CP_Vector currentPosition, startingOffset;

static CP_Matrix translationMatrix;

float centreX, centreY;

float scrollSpeed = 1.0f;

void CreditsInit() 
{
	centreX = (float)CP_System_GetWindowWidth() / 2;
	centreY = (float)CP_System_GetWindowHeight() / 2;
	//startingOffset = CP_Vector_Set(centreX, (float)CP_System_GetWindowHeight());
	currentPosition = CP_Vector_Set(0, 0);
	translationMatrix = CP_Matrix_Translate(currentPosition);
}

void CreditsDraw() 
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("BLOB", centreX, centreY);

}

void CreditsUpdate()
{
	currentPosition = CP_Vector_Add(currentPosition, CP_Vector_Set(0, -scrollSpeed));
	translationMatrix = CP_Matrix_Translate(currentPosition);

	CP_Settings_ApplyMatrix(translationMatrix);

	CreditsDraw();

}


void CreditsExit()
{

}