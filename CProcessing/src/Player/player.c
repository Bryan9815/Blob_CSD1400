#include <stdio.h>
#include <cprocessing.h>
#include "player.h"


CP_Color backgroundColour;
float rotateplayer;
//Player newPlayer;

void CreatePlayer(Player* player) //Default Variables
{
	//player.sprite = CP_Image_Load("./Assets/dioface.png");
	player->speed = 7.0f;
	player->width = CP_System_GetWindowWidth() / 15.0f;
	player->rotation = 0.0f;
	player->position.x = CP_System_GetWindowWidth() / 2.0f;
	player->position.y = CP_System_GetWindowWidth() / 2.0f;
	player->velX = 0;
	player->velY = 0;
}


/*Physics*/
void PlayerUpdate(Player player)
{

}

void PlayerMovement(Player* player)
{
	CP_Settings_Background(backgroundColour);

	if (CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_A))
	{
		player->velY = -1;
		player->velX = -1;
		player->position.y += (player->velY * player->speed);
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
		player->rotation = 180.0f;
	}

	else if (CP_Input_KeyDown(KEY_A))
	{
		player->velX = -1;
		player->position.x += (player->velX * player->speed);
		player->rotation = -90.0f;
	}

	else if (CP_Input_KeyDown(KEY_D))
	{
		player->velX = 1;
		player->position.x += (player->velX * player->speed);
		player->rotation = 90.0f;
	}
	CP_Graphics_DrawRectAdvanced(player->position.x, player->position.y, player->width, player->width, player->rotation, 1);
	//CP_Image_DrawAdvanced(player.sprite, player.position.x, player.position.y, player->width, player->width, 255, rotateimage);
	player->rotation = 0.0f;
}