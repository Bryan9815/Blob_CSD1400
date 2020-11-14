#include "../GameLogic/ScreenManager.h"
#include "scr_level_1.h"
#include "../Audio/AudioManager.h"


void Level1Init(void) 
{
	LoadMapFile(Level1);
	GridInit();
	PlayerInit(&newPlayer);
	CameraInit(&newPlayer.pBody.hitbox.position);
	Boss1Init();
	AudioL1Init();
	
	//shield = CP_Image_Load("././Assets/Shield1.png"); //the shield for boss 1 because the back has to be exposed
}

void LevelDraw(Player* player)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	GridUpdate(player->pBody.hitbox);
	PlayerDraw(&newPlayer);
	Boss1Draw(ArmorSlime);
	DrawArrow(&newPlayer.arrow);
	switch (currPlayState)
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
	switch(currPlayState)
	{
	case GAME_PLAY:
		if (GetBlobInputTriggered(BLOB_PAUSE))
		{
			SetPlayState(GAME_PAUSE);
		}
		PlayerUpdate(&newPlayer);
		Boss1Battle();
		AudioL1Play();
		bool dealdamage = ArrowStateChange(&(newPlayer.pBody), &(ArmorSlime.BossBody), &(newPlayer.arrow));
		if (dealdamage == true)
		{
			ArmorSlime.Health = 0;
		}
		
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
	ResetFader(GetFader());
	Boss1Exit();
	AudioL1Exit();
	GridExit();
}