#include "scr_tutorial.h"


void TutorialInit(void) 
{
	LoadMapFile(Level0);
	GridInit();
}

void TutorialDraw(Player* player)
{

}

void TutorialUpdate(Player* player)
{
	GridUpdate(player->pBody.hitbox);
}

void TutorialExit(void)
{
	GridExit();
}