#include <cprocessing.h>
#include "AudioManager.h"
#include "../GameLogic/ScreenManager.h"
#include <math.h>

bool MenuPlaying = false;
float SFX_Vol, BGM_Vol;

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
		sprintf_s(volumeLevel, 3, "%d", (int)BGM_Vol);
		break;
	case SFX:
		sprintf_s(volumeLevel, 3, "%d", (int)SFX_Vol);
		break;
	default:
		return "";
		break;
	}
	return volumeLevel;
}

void VolumeInit(void)
{
	SFX_Vol = 0;
	BGM_Vol = 0;
}

void AudioMenuInit(void)
{
	if (MenuPlaying == false)
	{
		BGM_Menu = CP_Sound_LoadMusic("././Assets/Audio/BlobMenu.wav");
		CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, (0.1f * BGM_Vol));
		CP_Sound_PlayMusic(BGM_Menu);
		CP_Sound_ResumeAll(); //Resume from pause menu
		MenuPlaying = true;
	}
}

void AudioMenuExit(void)
{
	CP_Sound_StopAll();
	CP_Sound_Free(BGM_Menu);
	MenuPlaying = false;
}

void AudioL0Init(void)
{
	BGM_Tutorial = CP_Sound_LoadMusic("././Assets/Audio/BlobTutorial.wav");
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_SFX, (0.1f * SFX_Vol));
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, (0.1f * BGM_Vol));
	CP_Sound_PlayMusic(BGM_Tutorial);
}

void AudioL0Exit(void)
{
	CP_Sound_StopAll();
	CP_Sound_Free(BGM_Tutorial);
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
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_SFX, (0.1f * SFX_Vol));
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, (0.1f * BGM_Vol));
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

float GetSFXVolume()
{
	return SFX_Vol;
}

void SetSFXVolume(float newVol)
{
	SFX_Vol = roundf(newVol);
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_SFX, (0.1f * newVol));
}

float GetBGMVolume()
{
	return BGM_Vol;
}

void SetBGMVolume(float newVol)
{
	BGM_Vol = roundf(newVol);
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, (0.1f * newVol));
}