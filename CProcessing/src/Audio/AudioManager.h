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

int SFX_Vol, BGM_Vol;
char volumeLevel[3];
bool MusicPlaying, SFXPlaying; //to make sure function is only called once
CP_Sound BGM_Menu;
CP_Sound BGM_Boss1;
CP_Sound ReflectSFX, SlamSFX, attackSFX, warningSFX, damageSFX;

const char* GetSoundText(soundSelect input);
char* GetVolumeText(soundSelect input);

void AudioMenuInit(void);
void AudioMenuExit(void);

void VolumeInit(void);
void AudioL1Init(void);
void AudioL1Play(void);
void AudioL1Pause(void);
void AudioL1Exit(void);