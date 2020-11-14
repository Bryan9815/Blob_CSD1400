#include <stdio.h>
#include <cprocessing.h>
#include "player.h"
#include "../GameLogic/BlobInput.h"
#include "../Bosses/Boss.h"
#include "../Screen/scr_level_1.h"
#include "../GameLogic//ScreenManager.h"


CP_Color backgroundColour;

void PlayerInit(Player* player) //Default Variables
{
	//Set Player and Arrow state
	playerState = STILL;
	player->arrow.arrowState = WITHPLAYER;

	playerColor = CP_Color_Create(255, 255, 255, 255);
	sprite = CP_Image_Load("././Assets/slime.png"); // NO MORE KONO DIO DA!


	//Player Stats and Position
	player->health = 1;
	player->pBody.rotation = 0.0f;

#if 0
	player->hitBox.shapeType = COL_RECT; //RECT COLLIDER
	player->hitBox.position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f - player->width / 2, CP_System_GetWindowHeight() / 2.0f - player->width / 2); //Align Hitbox to Corner
	player->hitBox.width = CP_System_GetWindowWidth() / 15.0f;
	player->hitBox.height = CP_System_GetWindowWidth() / 15.0f;
#endif
#if 1
	player->pBody.hitbox.shapeType = COL_CIRCLE; //CIRCLE COLLIDER
	player->pBody.hitbox.position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	player->pBody.hitbox.radius = 40.0f;
#endif

	//Player dodge
	dodgeDistance = 55.0f;
	dodgeTimer = 0.0f;
	dodgeBlur = 20;
	player->numDodge = 2;

	//Player Arrow
	CreateArrow(&(player->arrow));

}

void PlayerDraw(Player* player)
{
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	if (playerState == DODGING)
	{
		//Draw player
		int transparency = 50;
		
		//Draw player sprite
		CP_Image_DrawAdvanced(sprite, player->pBody.hitbox.position.x, player->pBody.hitbox.position.y, player->pBody.hitbox.radius * 2, player->pBody.hitbox.radius * 2, transparency, player->pBody.rotation);

		//Draw arrow
		CP_Image_DrawAdvanced(player->arrow.arrowSprite, player->arrow.aBody.hitbox.position.x, player->arrow.aBody.hitbox.position.y, player->arrow.aBody.hitbox.radius, player->arrow.aBody.hitbox.radius, transparency, player->arrow.aBody.rotation);

	}
	else
	{
		//Draw player
		//CP_Settings_Fill(playerColor);
		//CP_Graphics_DrawEllipseAdvanced(player->pBody.hitbox.position.x, player->pBody.hitbox.position.y, player->pBody.hitbox.radius * 2, player->pBody.hitbox.radius * 2, player->pBody.rotation);

		CP_Image_DrawAdvanced(sprite, player->pBody.hitbox.position.x, player->pBody.hitbox.position.y, player->pBody.hitbox.radius * 2, player->pBody.hitbox.radius * 2, 255, player->pBody.rotation);

	}

	//Draw Dodge Bar
	if (dodgeTimer > 0)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 100, 100));
		CP_Graphics_DrawRect(player->pBody.hitbox.position.x, player->pBody.hitbox.position.y - player->pBody.hitbox.radius - 10.0f, player->pBody.hitbox.radius, player->pBody.hitbox.radius / 5);
		CP_Settings_Fill(CP_Color_Create(255, 255, 100, 255));
		CP_Graphics_DrawRect(player->pBody.hitbox.position.x, player->pBody.hitbox.position.y - player->pBody.hitbox.radius - 10.0f, player->pBody.hitbox.radius * (dodgeTimer / DODGE_COOLDOWN), player->pBody.hitbox.radius / 5);
	}



	//HitBox
	//CP_Settings_Fill(CP_Color_Create(255, 0, 0, 200));	
#if 0
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	CP_Graphics_DrawCircle(					//CIRCLE COLLIDER
		player->pBody.hitbox.position.x,
		player->pBody.hitbox.position.y,
		player->pBody.hitbox.radius * 2);
#endif
#if 0
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(					//RECT COLLIDER
		player->hitBox.position.x,
		player->hitBox.position.y,
		player->hitBox.width,
		player->hitBox.height
	);
#endif
	//Draw Dio
	//CP_Image_DrawAdvanced(sprite, player->position.x, player->position.y, dioWidth, dioHeight, 255, player->rotation);
}

void PlayerMovement(Player* player)
{
	CP_Settings_Background(backgroundColour);
	bool shooting = ArrowTrigger(player);
	if (shooting == false)
	{
		if (playerState != DODGING)
		{
			playerState = STILL;
			player->pBody.velocity = CP_Vector_Set(0, 0);
			if (GetBlobInputDown(BLOB_UP) && GetBlobInputDown(BLOB_LEFT))
			{
				playerState = MOVING;
				//player->pBody.velocity = CP_Vector_Set(-1, -1);
				CP_Matrix rotatedir = CP_Matrix_Rotate(-45.0f);
				player->pBody.velocity = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, -1.0f));

				//player->rotation = -45.0f;
			}
			else if (GetBlobInputDown(BLOB_UP) && GetBlobInputDown(BLOB_RIGHT))
			{
				playerState = MOVING;
				//player->pBody.velocity = CP_Vector_Set(1, -1);
				CP_Matrix rotatedir = CP_Matrix_Rotate(45.0f);
				player->pBody.velocity = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, -1.0f));

				//player->rotation = 45.0f;
			}
			else if (GetBlobInputDown(BLOB_UP))
			{
				playerState = MOVING;
				player->pBody.velocity = CP_Vector_Set(0, -1);

				//player->rotation = 0.0f;
			}
			else if (GetBlobInputDown(BLOB_DOWN) && GetBlobInputDown(BLOB_RIGHT))
			{
				playerState = MOVING;
				//player->pBody.velocity = CP_Vector_Set(1, 1);
				CP_Matrix rotatedir = CP_Matrix_Rotate(-45.0f);
				player->pBody.velocity = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, 1.0f));

				//player->rotation = 135.0f;
			}
			else if (GetBlobInputDown(BLOB_DOWN) && GetBlobInputDown(BLOB_LEFT))
			{
				playerState = MOVING;
				//player->pBody.velocity = CP_Vector_Set(-1, 1);
				CP_Matrix rotatedir = CP_Matrix_Rotate(45.0f);
				player->pBody.velocity = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, 1.0f));

				//player->rotation = 225.0f;
			}
			else if (GetBlobInputDown(BLOB_DOWN))
			{
				playerState = MOVING;
				player->pBody.velocity = CP_Vector_Set(0, 1);

				//player->rotation = 180.0f;
			}
			else if (GetBlobInputDown(BLOB_LEFT))
			{
				playerState = MOVING;
				player->pBody.velocity = CP_Vector_Set(-1, 0);

				//player->rotation = -90.0f;
			}
			else if (GetBlobInputDown(BLOB_RIGHT))
			{
				playerState = MOVING;
				player->pBody.velocity = CP_Vector_Set(1, 0);

				//player->rotation = 90.0f;
			}

			if (CP_Input_KeyTriggered(KEY_SPACE) && (player->numDodge > 0))
			{
				player->numDodge -= 1;
				if (playerState == STILL)
				{
					CP_Matrix rotatedir = CP_Matrix_Rotate(player->pBody.rotation); //rotation matrix
					CP_Vector dir = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, -1.0f)); //rotate based off (0,1) to get direction vector
					player->pBody.velocity = dir;
				}

				player->pBody.velocity.x = player->pBody.velocity.x * (PLAYER_SPEED * CP_System_GetDt() * (dodgeDistance / 20));
				player->pBody.velocity.y = player->pBody.velocity.y * (PLAYER_SPEED * CP_System_GetDt() * (dodgeDistance / 20));
				playerState = DODGING;
			}

			if (playerState != DODGING)
			{
				player->pBody.velocity.x = (player->pBody.velocity.x * PLAYER_SPEED * CP_System_GetDt());
				player->pBody.velocity.y = (player->pBody.velocity.y * PLAYER_SPEED * CP_System_GetDt());
			}
		}
	}

	bool playerBossCol = PlayerEntityCollision(&player->pBody, &ArmorSlime.BossBody);
	CollisionCheck(&(player->pBody));
	if (playerBossCol == true && playerState == DODGING)
	{
		player->pBody.velocity = CP_Vector_Set(0.0f, 0.0f);
	}
	Dodge(player);

	player->pBody.hitbox.position.x += player->pBody.velocity.x;		//Circle
	player->pBody.hitbox.position.y += player->pBody.velocity.y;
}

void Dodge(Player* player)
{
	DodgeRecharge(player);
	if (playerState == DODGING)
	{

		if (dodgeBlur != 0)
		{
			dodgeBlur -= 1;
		}
		else
		{
			dodgeBlur = 20;
			playerState = STILL;
		}
		
		if (player->arrow.arrowState == WITHPLAYER)
		{
			player->arrow.aBody.hitbox.position = player->pBody.hitbox.position;
		}
	}
		
}

void DodgeRecharge(Player* player) //Recharge Dodge
{
	if (player->numDodge < 2)
	{
		dodgeTimer += CP_System_GetDt();
		if (dodgeTimer > DODGE_COOLDOWN)
		{
			player->numDodge += 1;
			dodgeTimer = 0.0f;
		}
	}
}

bool ArrowTrigger(Player* player)
{
	if (player->arrow.arrowState == WITHPLAYER)
	{
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
		{
			player->pBody.velocity.x = 0.0f;
			player->pBody.velocity.y = 0.0f;
			player->arrow.charging = 1;
			if (player->arrow.chargeTimer <= (MAX_FORCE - DEFAULT_FORCE))
			{
				player->arrow.chargeTimer += CP_System_GetDt() * 10;
				return true;
			}

		}
		else if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
		{
			if (player->arrow.charging == 1)
			{
				player->arrow.arrowState = RELEASE;
				player->arrow.charging = 0;
				return false;
			}
		}
	}

	else if (playerState == MOVING || playerState == DODGING)
	{
		player->arrow.chargeTimer = 0.0f;
		player->arrow.charging = 0;
	}
	return false;
}

/*Update Player*/
void PlayerUpdate(Player* player)
{
	MouseTracking(&player->pBody);
	if (player->health == 1)
	{
		PlayerMovement(player);
		ArrowTrigger(player);
	}
	else //when player is dead
	{
		//for now
		//move to game over screen later
		//set values to default if needed
		SetGameOver(false);
		PlayerMovement(player);
		ArrowTrigger(player);
	}

}

void PlayerExit()
{
	CP_Image_Free(&sprite);
}