#include "../GameLogic/ScreenManager.h"
#include "scr_level_2.h"
#include "../Audio/AudioManager.h"
#include "../GameLogic/Score.h"

void Level2Init(void) 
{
	LoadMapFile(Level2);
	GridInit();
	PlayerInit(&newPlayer);
	newPlayer.pBody.hitbox.position = CP_Vector_Set(800, 800);
	CameraInit(&newPlayer.pBody.hitbox.position, PAN_PLAYER);
	Boss2Init();
	Boss2.BossBody.hitbox.position = CP_Vector_Set(1425, 800);
	AudioL1Init();
	Boss2Timer = 0.f;
}

void Level2Draw(Player* player)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));

	GridDraw(player->pBody.hitbox);
	Boss2Draw();
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

void Level2Update(Player* player)
{
	switch(GetPlayState())
	{
	case GAME_PLAY:
		if (GetBlobInputTriggered(BLOB_PAUSE))
		{
			SetPlayState(GAME_PAUSE);
		}
		PlayerUpdate(&newPlayer);
		Boss2Battle();
		AudioL1Play();
		StageTime(&Boss2Timer);
		bool dealdamage = ArrowStateCheck(&(newPlayer.pBody), &(Boss2.BossBody), &(newPlayer.arrow));
		BossDamage(&dealdamage, &Boss2);
		break;
	case GAME_PAUSE:
		AudioL1Pause();
		if (GetBlobInputTriggered(BLOB_PAUSE))
		{
			SetPlayState(GAME_PLAY);
		}
		break;
	}
	GridUpdate(player->pBody.hitbox, player->arrow.aBody.hitbox);
	CameraUpdate(&newPlayer.pBody.hitbox.position, GetFader());
	Level2Draw(player);
}

void Level2Exit(void) 
{
	Boss2Exit();
	AudioL1Exit();
	GridExit();
}