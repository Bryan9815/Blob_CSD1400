#include "scr_tutorial.h"


void TutorialInit(void) 
{
	LoadMapFile(Level0);
	GridInit();

	//Player
	PlayerInit(&newPlayer);
	newPlayer.pBody.hitbox.position = CP_Vector_Set(200, 200);
	CameraInit(&newPlayer.pBody.hitbox.position);
}

void TutorialDraw(Player* player)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	GridUpdate(player->pBody.hitbox);
	PlayerDraw(&newPlayer);
	DrawArrow(&newPlayer.arrow);
}

void TutorialUpdate(Player* player)
{
	PlayerUpdate(&newPlayer);
	ArrowStateChange(&(newPlayer.pBody), &(ArmorSlime.BossBody), &(newPlayer.arrow));
	CameraUpdate(&newPlayer.pBody.hitbox.position, GetFader());
	TutorialDraw(player);
}

void TutorialExit(void)
{
	GridExit();
}