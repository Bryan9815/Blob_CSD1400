#include "scr_tutorial.h"

float timer;

void TutorialInit(void) 
{
	LoadMapFile(Level0);
	GridInit();

	//Player
	PlayerInit(&newPlayer);
	newPlayer.pBody.hitbox.position = CP_Vector_Set(200, 200);
	newPlayer.arrow.aBody.hitbox.position = newPlayer.pBody.hitbox.position;
	CameraInit(&newPlayer.pBody.hitbox.position, PAN_PLAYER);
	timer = 0;
}

void TutorialDraw(Player* player)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	GridUpdate(player->pBody.hitbox);
	PlayerDraw(&newPlayer);
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

void TutorialUpdate(Player* player)
{
	switch (currPlayState)
	{
	case GAME_PLAY:
		if (GetBlobInputTriggered(BLOB_PAUSE))
		{
			SetPlayState(GAME_PAUSE);
		}
		PlayerUpdate(&newPlayer);
		ArrowStateCheck(&(newPlayer.pBody), &(ArmorSlime.BossBody), &(newPlayer.arrow));
		break;
	case GAME_PAUSE:
		if (GetBlobInputTriggered(BLOB_PAUSE))
		{
			SetPlayState(GAME_PLAY);
		}
		break;
	}
	CameraUpdate(&newPlayer.pBody.hitbox.position, GetFader());
	TutorialDraw(player);
}

void TutorialExit(void)
{
	GridExit();
}