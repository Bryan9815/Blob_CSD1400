#include <cprocessing.h>
#include "AudioManager.h"
#include "../GameLogic/ScreenManager.h"


bool MenuPlaying = false;

//for sound options
const char* GetSoundText(soundSelect input)
{
	switch (input)
	{
	case MUSIC:
		return "Music";
		break;
	case SFX:
		return "SFX";
		break;
	default:
		return "";
		break;
	}
}

//for sound options
char* GetVolumeText(soundSelect input)
{
	switch (input)
	{
	case MUSIC:
		sprintf_s(volumeLevel, 3, "%d", BGM_Vol);
		break;
	case SFX:
		sprintf_s(volumeLevel, 3, "%d", SFX_Vol);
		break;
	default:
		return "";
		break;
	}
	return volumeLevel;
}

void VolumeInit(void)
{
	SFX_Vol = 10;
	BGM_Vol = 10;
}

void AudioMenuInit(void)
{
	if (MenuPlaying == false)
	{
		BGM_Menu = CP_Sound_LoadMusic("././Assets/Audio/BlobMenu.wav");
		CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, (0.1f * (float)BGM_Vol));
		CP_Sound_PlayMusic(BGM_Menu);
		CP_Sound_ResumeAll(); //Resume from pause menu
		//test if track is loaded
		MenuPlaying = true;
	}
}

void AudioMenuExit(void)
{
	CP_Sound_StopAll();
	CP_Sound_Free(BGM_Menu);
	MenuPlaying = false;
}


void AudioL1Init(void)
{
	//load and play
	BGM_Boss1 = CP_Sound_LoadMusic("././Assets/Audio/boss1.wav");
	SlamSFX = CP_Sound_Load("././Assets/Audio/bossSlamSFX1.wav");
	ReflectSFX = CP_Sound_Load("././Assets/Audio/reflectSFX1.wav");
	attackSFX = CP_Sound_Load("././Assets/Audio/attackSFX.wav");
	damageSFX = CP_Sound_Load("././Assets/Audio/bossDamaged.wav");
	warningSFX = CP_Sound_Load("././Assets/Audio/warningAttackSFX.wav");
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_SFX, (0.1f * (float)SFX_Vol));
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, (0.1f * (float)BGM_Vol));
	CP_Sound_PlayMusic(BGM_Boss1);
	CP_Sound_ResumeAll(); //resume if player paused and retry
	MusicPlaying = true;
	SFXPlaying = false;
	//test if track is loaded
	/*if (attackSFX && damageSFX && warningSFX)
		printf("work");
	else
		printf("no work");*/
}

void AudioL1Play(void)
{
	//if not playing from pause, resume music
	if (MusicPlaying == false)
	{
		CP_Sound_ResumeAll();
		MusicPlaying = true;
	}
}

void AudioL1Pause(void)
{
	//if playing, pause music
	if (MusicPlaying == true)
	{
		CP_Sound_PauseAll();
		MusicPlaying = false;
	}
}

void AudioL1Exit(void)
{
	//stop any music/SFX still playing
	CP_Sound_StopAll();
	CP_Sound_Free(BGM_Boss1);
	CP_Sound_Free(ReflectSFX);
	CP_Sound_Free(SlamSFX);
	CP_Sound_Free(attackSFX);
	CP_Sound_Free(damageSFX);
	CP_Sound_Free(warningSFX);
}