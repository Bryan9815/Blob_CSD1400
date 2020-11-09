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
	Boss1Init();
	//shield = CP_Image_Load("././Assets/Shield1.png"); //the shield for boss 1 because the back has to be exposed
}

void LevelDraw(Player* player)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	GridUpdate(level[0], player->pBody.hitbox);
	PlayerDraw(&newPlayer);
	Boss1Draw(ArmorSlime);
	DrawArrow(&newPlayer.arrow);

	if(pause)
	{
		CP_Vector overlayCenter = CP_Vector_Set((float)CP_System_GetWindowWidth() / 2 + GetCameraPos().x, (float)CP_System_GetWindowHeight() / 2 + GetCameraPos().y);
		CP_Settings_Fill(CP_Color_Create(50, 50, 50, 150));
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRect(overlayCenter.x, overlayCenter.y, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Settings_TextSize(96);
		CP_Font_DrawText("PAUSE", overlayCenter.x, overlayCenter.y);
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
		Boss1Battle();
		bool dealdamage = ArrowStateChange(&(newPlayer.pBody), &(ArmorSlime.BossBody), &(newPlayer.arrow));
		if (dealdamage == true)
		{
			ArmorSlime.Health = 0;
		}
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
	ResetFader(GetFader());
	Boss1Exit();
}