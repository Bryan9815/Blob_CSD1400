#include "../GameLogic/ScreenManager.h"
#include "scr_level_1.h"



void Level1Init(void) 
{
	LoadMapFile(Level0);
	GridInit(level[0]);
	CreatePlayer(&newPlayer);
	CameraInit(&newPlayer.position);
	BossInit(&ArmorSlime, 1, 125.f);
	shield = CP_Image_Load("././Assets/Shield1.png"); //the shield for boss 1 because the back has to be exposed
}

void LevelDraw(Player* player)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	GridUpdate(level[0], player->hitBox);
	PlayerDraw(&newPlayer);
	AttackNearDraw(&ArmorSlime);
	AttackFarDraw(&ArmorSlime, newPlayer);
	Shield1Draw(ArmorSlime);
	BossDraw(ArmorSlime); //note that boss is drawn after to be on top of shield
	
	
}

void Level1Update(Player* player)
{
	PlayerUpdate(&newPlayer);
	Boss1Battle(newPlayer);
	CameraUpdate(&newPlayer.position, GetFader());
	LevelDraw(player);
}

void Level1Exit(void) 
{
	
}