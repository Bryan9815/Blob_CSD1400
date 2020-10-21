#include <cprocessing.h>
#include <stdio.h>
#include <stdbool.h>
#include "fader.h"

Fader CreateFader() 
{
	Fader fader;

	fader.fadeAlpha = 255;
	fader.fadeType = FADE_OUT;
	fader.isFading = false;

	return fader;
}

Fader StartFade(Fader fader, FadeType fadeType)	//wtf
{
	fader.isFading = true;
	fader.fadeType = fadeType;

	return fader;
}

Fader StopFade(Fader fader, FadeType fadeType)	//wtf
{
	fader.isFading = false;
	fadeType = fadeType;

	return fader;
}

Fader UpdateFade(Fader fader)	//wtf
{
	if (fader.isFading) //fading
	{
		if (fader.fadeType == FADE_IN) 
		{
			fader.fadeAlpha += CP_System_GetDt() * 200;	//Fade Speed is 200 zzz
		}
		else 
		{
			fader.fadeAlpha -= CP_System_GetDt() * 200;
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
	//printf("%d\n", (int)fader.fadeAlpha);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, (int)fader.fadeAlpha));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(0, 0, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());

	return fader;
}



