#include "../GameLogic/ScreenManager.h"
#include "scr_level_1.h"
bool pause;


void Level1Init(void) 
{
	pause = false;
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
	if (!pause)
	{
		GridUpdate(level[0], player->pBody.hitbox);
		PlayerDraw(&newPlayer);
		Boss1Draw(ArmorSlime, newPlayer);
	}
	else
	{
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Settings_TextSize(96);
		CP_Font_DrawText("PAUSE", (float)CP_System_GetWindowWidth() / 2 + GetCameraPos().x, (float)CP_System_GetWindowHeight() / 2 + GetCameraPos().y);
	}
}

void Level1Update(Player* player)
{
	if (!pause)
	{
		if (GetBlobInputTriggered(BLOB_PAUSE))
		{
			pause = true;
		}
		PlayerUpdate(&newPlayer);
		Boss1Battle(newPlayer, level[0]);
	}
	else
	{
		if (GetBlobInputTriggered(BLOB_PAUSE))
		{
			pause = false;
		}
	}
	CameraUpdate(&newPlayer.pBody.hitbox.position, GetFader());
	LevelDraw(player);
}

void Level1Exit(void) 
{
	
}