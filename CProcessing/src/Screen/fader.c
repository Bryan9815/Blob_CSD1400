#include <cprocessing.h>
#include <stdio.h>
#include <stdbool.h>
#include "fader.h"

void CreateFader(Fader* fader) //Default Variables
{
	fader->isFading = false;
	fader->fadeSpeed = 200.0f;
	fader->fadeAlpha = 255.0f;

}

void StartFade(Fader* fader, FadeType fadeType)	//Sets the Fader to fade
{

	if (fadeType == FADE_OUT)
		fader->fadeAlpha = 255.0f;
	else
		fader->fadeAlpha = 0.0f;

	fader->isFading = true;
	fader->fadeType = fadeType;
}

void StopFade(Fader* fader, FadeType fadeType)	//Sets the Fader to stop fading @todo
{
	fader->isFading = false;
	fader->fadeType = fadeType;
}

void UpdateFade(Fader* fader)	//Drawcall for Fader
{
	if (fader->isFading) //fading
	{
		if (fader->fadeType == FADE_IN)
		{
			fader->fadeAlpha += CP_System_GetDt() * fader->fadeSpeed;	//Fade Speed is 200 zzz
		}
		else 
		{
			fader->fadeAlpha -= CP_System_GetDt() * fader->fadeSpeed;
		}

		if (fader->fadeType == FADE_IN && fader->fadeAlpha >= 255)
		{
			fader->fadeAlpha = 255;
			fader->isFading = false;
		}
		else if (fader->fadeType == FADE_OUT && fader->fadeAlpha <= 0)
		{
			fader->fadeAlpha = 0;
			fader->isFading = false;
		}
	}


	CP_Settings_Fill(CP_Color_Create(0, 0, 0, (int)fader->fadeAlpha));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(fader->fadePosX, fader->fadePosY, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());

}

void ResetFader(Fader* fader)
{
	fader->fadePosX = 0;
	fader->fadePosY = 0;
}