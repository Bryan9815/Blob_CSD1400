#include <cprocessing.h>
#include "AudioManager.h"
#include "../GameLogic/ScreenManager.h"

bool Playing; //to make sure function is only called once

void AudioL1Init(void)
{
	//load and play
	BGM_Boss1 = CP_Sound_LoadMusic("././Assets/Audio/boss1.wav");
	SlamSFX = CP_Sound_Load("././Assets/Audio/bossSlamSFX1.wav");
	ReflectSFX = CP_Sound_Load("././Assets/Audio/reflectSFX1.wav");
	CP_Sound_PlayMusic(BGM_Boss1);
	CP_Sound_ResumeAll(); //resume if player paused and retry
	Playing = true;
	//test if track is loaded
	/*if (ReflectSFX && SlamSFX)
		printf("work");
	else
		printf("no work");*/
}

void AudioL1Play(void)
{
	//if not playing from pause, resume music
	if (Playing == false)
	{
		CP_Sound_ResumeAll();
		Playing = true;
	}
}

void AudioL1Pause(void)
{
	//if playing, pause music
	if (Playing == true)
	{
		CP_Sound_PauseAll();
		Playing = false;
	}
}

void AudioL1Exit(void)
{
	//stop any music/SFX still playing
	CP_Sound_StopAll();
	CP_Sound_Free(BGM_Boss1);
	CP_Sound_Free(ReflectSFX);
	CP_Sound_Free(SlamSFX);
}