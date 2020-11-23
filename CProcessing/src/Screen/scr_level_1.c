#include "../GameLogic/ScreenManager.h"
#include "scr_level_1.h"
#include "../Audio/AudioManager.h"
#include "../GameLogic/Score.h"


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
	//shield = CP_Image_Load("././Assets/Shield1.png"); //the shield for boss 1 because the back has to be exposed
}

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

void Level1Exit(void) 
{
	Boss1Exit();
	AudioL1Exit();
	GridExit();
}