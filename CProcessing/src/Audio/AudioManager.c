#include <cprocessing.h>
#include "AudioManager.h"
#include "../GameLogic/ScreenManager.h"

void AudioInit()
{
	BGM_Boss1 = CP_Sound_LoadMusic("../../Assets/Audio/boss1.wav");
	
}

void AudioLvl1()
{
	CP_Sound_PlayMusic(BGM_Boss1);
}

void AudioExit()
{
	CP_Sound_Free(BGM_Boss1);
}