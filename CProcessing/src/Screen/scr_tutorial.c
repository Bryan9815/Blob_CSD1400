#include "scr_tutorial.h"
#include "../Audio/AudioManager.h"

#define SkipDrawDelay 5.0f

float timer;

GridUnit* switches[2];
GridUnit* door1[8];
GridUnit* damage[8];
GridUnit* portal[4];

bool switchesDown,
     gateIsOpen;

float skipDrawTimer = SkipDrawDelay;

void TutorialInit(void) 
{
	LoadMapFile(Level0);
	GridInit();

	skipDrawTimer = SkipDrawDelay;

	int k = 0, l = 0, m = 0, n = 0;
	for (int i = 0; i < GetLevelWidth(); i++) 
	{
		for (int j = 0; j < GetLevelHeight(); j++)
		{
			if (GetGridUnit(i, j)->gridType == GE_SWITCH) 
			{
				switches[k++] = GetGridUnit(i, j);
			}
			else if (GetGridUnit(i, j)->gridType == GE_DOOR)
			{
				door1[l++] = GetGridUnit(i, j);
			}
			else if (GetGridUnit(i, j)->gridType == GE_PORTAL)
			{
				portal[m++] = GetGridUnit(i, j);
			}
			else if (GetGridUnit(i, j)->gridType == GE_DAMAGE)
			{
				damage[n++] = GetGridUnit(i, j);
			}
		}
	}

	switchesDown = false;
	gateIsOpen = false;

	//Player
	PlayerInit(&newPlayer);
	newPlayer.pBody.hitbox.position = CP_Vector_Set(400, 500);
	newPlayer.arrow.aBody.hitbox.position = newPlayer.pBody.hitbox.position;
	CameraInit(&newPlayer.pBody.hitbox.position, PAN_PLAYER);
	timer = 0;
	AudioL0Init();
}

void TutorialDraw(Player* player)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));

	GridDraw(player->pBody.hitbox);

	//Tutorial Instructions
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	//SKIP
	if (skipDrawTimer <= 0) 
	{
		CP_Settings_TextSize(30);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText("X to skip tutorial", CP_System_GetWindowWidth() - 100 + GetCameraPos().x, 20 + GetCameraPos().y);
	}
	else 
	{
		skipDrawTimer -= CP_System_GetDt();
	}

	//WASD
	CP_Settings_TextSize(25);
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Font_DrawText("W A S D", 400.0f, 350.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("TO MOVE", 400.0f, 380.0f);

	//SPACE
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Font_DrawText("SPACE", 1200.0f, 350.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("TO DASH/DODGE", 1200.0f, 380.0f);

	//MOUSE1
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Font_DrawText("HOLD MOUSE 1", 2250.0f, 350.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("TO FIRE", 2250.0f, 380.0f);

	//MOUSE2
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Font_DrawText("MOUSE 2", 2750.0f, 350.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("TO RECALL", 2750.0f, 380.0f);


	PlayerDraw(&newPlayer);
	DrawArrow(&newPlayer.arrow);

	switch (GetPlayState())
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
	switch (GetPlayState())
	{
	case GAME_PLAY:
		if (GetBlobInputTriggered(BLOB_PAUSE))
		{
			SetPlayState(GAME_PAUSE);
		}
		if (CP_Input_KeyTriggered(KEY_X)) //Skips tutorial on X
		{
			SetGameState(SCR_LEVEL1);
		}
		PlayerUpdate(&newPlayer);
		ArrowStateCheck(&(newPlayer.pBody), &(ArmorSlime.BossBody), &(newPlayer.arrow));
		GridUpdate(player->pBody.hitbox, player->arrow.aBody.hitbox);

		for (size_t i = 0; i < sizeof(damage) / sizeof(damage[0]); i++)
		{
			if (COL_IsColliding(player->pBody.hitbox, damage[i]->collider) && playerState != DODGING)//Damage
			{
				player->health = 0;
			}
		}

		//Check Switches
		for (size_t i = 0; i < sizeof(switches) / sizeof(switches[0]); i++)
		{
			if (!(switches[i]->isActive))
			{
				switchesDown = false;
				break;
			}
			else 
			{
				switchesDown = true;
			}
		}

		//Door right door open
		if (switchesDown && !gateIsOpen)
		{
			for (size_t i = 0; i < sizeof(door1) / sizeof(door1[0]); i++)
			{
				door1[i]->isActive = false;
				door1[i]->isCollidable = false;
			}
			gateIsOpen = true;
		}

		//Right Clear Room Clear
		for (size_t i = 0; i < sizeof(portal) / sizeof(portal[0]); i++)
		{
			if (COL_IsColliding(player->pBody.hitbox, portal[i]->collider))//Reach the Portal
			{
				ScreenStartFade(FADE_IN);
				SetPlayState(GAME_SWAP);
				break;
			}
		}


		break;
	case GAME_PAUSE:
		if (GetBlobInputTriggered(BLOB_PAUSE))
		{
			SetPlayState(GAME_PLAY);
		}
		break;
	case GAME_SWAP://Once the fader ended
		if (!(GetFader()->isFading)) 
		{
			SetGameState(SCR_LEVEL1);
		}
		break;
	}
	CameraUpdate(&newPlayer.pBody.hitbox.position, GetFader());
	TutorialDraw(player);
}

void TutorialExit(void)
{
	AudioL0Exit();
	GridExit();
}