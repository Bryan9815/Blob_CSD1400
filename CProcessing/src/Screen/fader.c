#include <cprocessing.h>
#include <stdio.h>
#include <stdbool.h>
#include "fader.h"

Fader CreateFader() //Default Variables
{
	Fader fader;
	fader.isFading = false;
	fader.fadeSpeed = 200.0f;
	fader.fadeAlpha = 255.0f;

	return fader;
}

Fader StartFade(Fader fader, FadeType fadeType)	//Sets the Fader to fade
{

	if (fadeType == FADE_OUT)
		fader.fadeAlpha = 255.0f;
	else
		fader.fadeAlpha = 0.0f;

	fader.isFading = true;
	fader.fadeType = fadeType;

	return fader;
}

Fader StopFade(Fader fader, FadeType fadeType)	//Sets the Fader to stop fading
{
	fader.isFading = false;
	fader.fadeType = fadeType;
	return fader;
}

Fader UpdateFade(Fader fader)	//Drawcall for Fader
{
	if (fader.isFading) //fading
	{
		if (fader.fadeType == FADE_IN)
		{
			fader.fadeAlpha += CP_System_GetDt() * fader.fadeSpeed;	//Fade Speed is 200 zzz
		}
		else 
		{
			fader.fadeAlpha -= CP_System_GetDt() * fader.fadeSpeed;
		}

		if (fader.fadeType == FADE_IN && fader.fadeAlpha >= 255)
		{
			fader.fadeAlpha = 255;
			fader.isFading = false;
		}
		else if (fader.fadeType == FADE_OUT && fader.fadeAlpha <= 0)
		{
			fader.fadeAlpha = 0;
			fader.isFading = false;
		}
	}


	CP_Settings_Fill(CP_Color_Create(0, 0, 0, (int)fader.fadeAlpha));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(0, 0, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());

	return fader;
}



