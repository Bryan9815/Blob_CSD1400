#include "../GameLogic/ScreenManager.h"

GridUnit level[GRID_WIDTH][GRID_HEIGHT];

void Level1Init(void) 
{
	LoadMapFile(Level0);
	GridInit(level[0]);
}

void Level1Update(Player* player)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	GridUpdate(level[0], player->hitBox);
}