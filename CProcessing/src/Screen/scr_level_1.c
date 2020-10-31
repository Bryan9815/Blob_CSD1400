#include "../GameLogic/ScreenManager.h"
#include "scr_level_1.h"



void Level1Init(void) 
{
	LoadMapFile(Level0);
	GridInit(level[0]);
	PlayerInit(&newPlayer);
	CameraInit(&newPlayer.pBody.hitbox.position);
	BossInit(&ArmorSlime, 1, 80.f);
	shield = CP_Image_Load("././Assets/Shield1.png"); //the shield for boss 1 because the back has to be exposed
}

void LevelDraw(Player* player)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	GridUpdate(level[0], player->pBody.hitbox);
	PlayerDraw(&newPlayer);
	Boss1Draw(ArmorSlime, newPlayer);
	
	
}

void Level1Update(Player* player)
{
	PlayerUpdate(&newPlayer);
	Boss1Battle(newPlayer, level[0]);
	CameraUpdate(&newPlayer.pBody.hitbox.position, GetFader());
	LevelDraw(player);
}

void Level1Exit(void) 
{
	
}