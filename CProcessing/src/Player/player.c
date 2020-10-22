#include <stdio.h>
#include <cprocessing.h>
#include "player.h"


CP_Color backgroundColour;
//Player newPlayer;

void SetPlayer(Player* player) //Default settings
{
	//Player Stats and Position
	//player.sprite = CP_Image_Load("./dioface.png");
	player->speed = 7.0f;
	player->width = CP_System_GetWindowWidth() / 15.0f;
	player->rotation = 0.0f;
	player->position.x = CP_System_GetWindowWidth() / 2.0f;
	player->position.y = CP_System_GetWindowWidth() / 2.0f;
	player->velX = 0;
	player->velY = -1;

	//Player dodge
	player->numDodge = 2;
	player->dodgeBlur = 3;
	player->dodgeCooldown = 4;
	player->dodgeFactor = 10.0f;
	player->dodgeTimer = CP_System_GetWindowWidth() / 100.0f;
	player->isDodging = 0;
}

/*Physics*/
void PlayerUpdate(Player player)
{
	
}

void PlayerMovement(Player* player)
{
	CP_Settings_Background(backgroundColour);

	if (CP_Input_KeyTriggered(KEY_SPACE) && (player->numDodge > 0))
	{
		player->isDodging = 1;
		player->numDodge -= 1;

	}
	else if (CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_A))
	{
		player->velY = -1;
		player->position.y += (player->velY * player->speed);
		player->velX = -1;
		player->position.x += (player->velX * player->speed);
		player->rotation = -45.0f;
	}
	else if ((CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_D)))
	{
		player->velY = -1;
		player->position.y += (player->velY * player->speed);
		player->velX = 1;
		player->position.x += (player->velX * player->speed);
		player->rotation = 45.0f;
	}
	else if (CP_Input_KeyDown(KEY_W))
	{
		player->velY = -1;
		player->position.y += (player->velY * player->speed);
		player->velX = 0;
		player->position.x += (player->velX * player->speed);
		player->rotation = 0.0f;
	}
	else if (CP_Input_KeyDown(KEY_S) && CP_Input_KeyDown(KEY_D))
	{
		player->velY = 1;
		player->position.y += (player->velY * player->speed);
		player->velX = 1;
		player->position.x += (player->velX * player->speed);
		player->rotation = 135.0f;
	}
	else if (CP_Input_KeyDown(KEY_S) && CP_Input_KeyDown(KEY_A))
	{
		player->velY = 1;
		player->position.y += (player->velY * player->speed);
		player->velX = -1;
		player->position.x += (player->velX * player->speed);
		player->rotation = 225.0f;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		player->velY = 1;
		player->position.y += (player->velY * player->speed);
		player->velX = 0;
		player->position.x += (player->velX * player->speed);
		player->rotation = 180.0f;
	}

	else if (CP_Input_KeyDown(KEY_A))
	{
		player->velY = 0;
		player->position.y += (player->velY * player->speed);
		player->velX = -1;
		player->position.x += (player->velX * player->speed);
		player->rotation = -90.0f;
	}

	else if (CP_Input_KeyDown(KEY_D))
	{
		player->velY = 0;
		player->position.y += (player->velY * player->speed);
		player->velX = 1;
		player->position.x += (player->velX * player->speed);
		player->rotation = 90.0f;
	}
	CP_Graphics_DrawRectAdvanced(player->position.x, player->position.y, player->width, player->width, player->rotation, 1);
	//CP_Image_DrawAdvanced(player.sprite, player.position.x, player.position.y, player->width, player->width, 255, rotateimage);
}

//Cooldown for Dodge
void PlayerDodgeTimer(Player* player)
{
	if (player->numDodge < 2)
	{
		player->dodgeTimer += CP_System_GetDt();
		if (player->dodgeTimer > player->dodgeCooldown)
		{
			player->numDodge += 1;
			player->dodgeTimer = 0.0f;
		}
	}
}

//Player Dodging
void PlayerDodge(Player* player)
{
	if (player->isDodging == 1)
	{

		if (player->dodgeBlur != 0)
		{
			player->dodgeBlur -= 1;
		}
		else
		{
			player->dodgeBlur = 3;
			player->isDodging = 0;
		}
		player->position.x += (player->velX * (player->speed * (player->dodgeFactor / 4)));
		player->position.y += (player->velY * (player->speed * (player->dodgeFactor / 4)));
		CP_Graphics_DrawRectAdvanced(player->position.x, player->position.y, player->width, player->width, player->rotation, 1);
		//CP_Image_DrawAdvanced(player->sprite, player->position.x, player->position.y, dioWidth, dioHeight, 255, rotateimage);
	}
}