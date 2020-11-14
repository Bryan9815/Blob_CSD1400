#include "scr_tutorial.h"

float timer;

void TutorialInit(void) 
{
	LoadMapFile(Level0);
	GridInit();

	//Player
	PlayerInit(&newPlayer);
	newPlayer.pBody.hitbox.position = CP_Vector_Set(200, 200);
	CameraInit(&newPlayer.pBody.hitbox.position, LOCK_PLAYER);
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
	float dt = CP_System_GetDt();
	switch (currPlayState)
	{
	case GAME_PLAY:
		if (GetBlobInputTriggered(BLOB_PAUSE))
		{
			SetPlayState(GAME_PAUSE);
		}
		PlayerUpdate(&newPlayer);
		ArrowStateChange(&(newPlayer.pBody), &(ArmorSlime.BossBody), &(newPlayer.arrow));
		if (GetCameraMode() == LOCK_PLAYER)
		{
			timer += dt;
			if (timer > 0.1f)
			{
				SetCameraMode(PAN_PLAYER);
				timer = 0.0f;
			}
		}
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