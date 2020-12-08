//---------------------------------------------------------
// file:	scr_level_1.c
// author:	[Phang Jia Rong]
// email:	[jiarong.phang@digipen.edu]
//
// brief:	Handles the functionality and update for level_1
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------


#include "../GameLogic/ScreenManager.h"
#include "scr_level_1.h"
#include "../Audio/AudioManager.h"
#include "../GameLogic/Score.h"

//Level 1 Init
void Level1Init(void) 
{
	LoadMapFile(Level1);
	GridInit();
	PlayerInit(&newPlayer);
	newPlayer.pBody.hitbox.position = CP_Vector_Set(800, 800);
	CameraInit(&newPlayer.pBody.hitbox.position, PAN_PLAYER);
	Boss1Init();
	ArmorSlime.BossBody.hitbox.position = CP_Vector_Set(2000, 800);
	AudioL1Init();
	Boss1Timer = 0.f;
}

//Draw for Level_1
void LevelDraw(Player* player)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));

	GridDraw(player->pBody.hitbox);
	Boss1Draw(ArmorSlime);
	PlayerDraw(&newPlayer);
	DrawArrow(&newPlayer.arrow);
	switch (GetPlayState())
	{
	case GAME_PLAY:
		break;
	default:
		DrawOverlay();
		break;
	}
}

//Update for Level1
void Level1Update(Player* player)
{
	switch(GetPlayState())
	{
	case GAME_PLAY:
		if (GetBlobInputTriggered(BLOB_PAUSE))
		{
			SetPlayState(GAME_PAUSE);
		}
		PlayerUpdate(&newPlayer);
		Boss1Battle();
		AudioL1Play();
		bool dealdamage = ArrowStateCheck(&(newPlayer.pBody), &(ArmorSlime.BossBody), &(newPlayer.arrow));
		BossDamage(&dealdamage, &ArmorSlime);
		StageTime(&Boss1Timer);
		break;
	case GAME_PAUSE:
		AudioL1Pause();
		if (GetBlobInputTriggered(BLOB_PAUSE))
		{
			SetPlayState(GAME_PLAY);
		}
		break;
	}
	CameraUpdate(&newPlayer.pBody.hitbox.position, GetFader());
	LevelDraw(player);
}

//Exit Call for Level1
void Level1Exit(void) 
{
	Boss1Exit();
	AudioL1Exit();
	GridExit();
}