#pragma once
#include <cprocessing.h>
#include <stdbool.h>
#define SOUND_MIN 0
#define SOUND_MAX 15

typedef enum
{
	MUSIC,
	SFX
} soundSelect;

char volumeLevel[3];
bool MusicPlaying, SFXPlaying; //to make sure function is only called once
CP_Sound BGM_Menu, BGM_Tutorial, BGM_Boss1;
CP_Sound ReflectSFX, SlamSFX, attackSFX, warningSFX, damageSFX;

const char* GetSoundText(soundSelect input);
char* GetVolumeText(soundSelect input);

void VolumeInit(void);
void AudioMenuInit(void);
void AudioMenuExit(void);

void AudioL0Init(void);
void AudioL0Exit(void);

void AudioL1Init(void);
void AudioL1Play(void);
void AudioL1Pause(void);
void AudioL1Exit(void);

float GetSFXVolume();
void SetSFXVolume(float newVol);
float GetBGMVolume();
void SetBGMVolume(float newVol);