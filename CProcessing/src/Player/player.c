#include <stdio.h>
#include <cprocessing.h>
#include "player.h"
#include "../GameLogic/BlobInput.h"


CP_Color backgroundColour;

void PlayerInit(Player* player) //Default Variables
{
	//Set Player and Arrow state
	playerState = STILL;
	playerArrowState = WITHPLAYER;

	playerColor = CP_Color_Create(255, 255, 255, 255);
	//sprite = CP_Image_Load(".dioface.png");

	//Player Stats and Position
	player->health = 1;
	player->rotation = 0.0f;

#if 0
	player->hitBox.shapeType = COL_RECT; //RECT COLLIDER
	player->hitBox.position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f - player->width / 2, CP_System_GetWindowHeight() / 2.0f - player->width / 2); //Align Hitbox to Corner
	player->hitBox.width = CP_System_GetWindowWidth() / 15.0f;
	player->hitBox.height = CP_System_GetWindowWidth() / 15.0f;
#endif
#if 1
	player->pBody.hitbox.shapeType = COL_CIRCLE; //CIRCLE COLLIDER
	player->pBody.hitbox.position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	player->pBody.hitbox.radius = CP_System_GetWindowWidth() / 40.0f;
#endif

	//Player dodge
	dodgeDistance = CP_System_GetWindowWidth() / 30.0f;
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
	MouseTracking(player);
	if (playerState == DODGING)
	{
		//Draw player
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50));
		CP_Graphics_DrawEllipseAdvanced(player->pBody.hitbox.position.x, player->pBody.hitbox.position.y, player->pBody.hitbox.radius * 2, player->pBody.hitbox.radius * 2, player->rotation);

		//Draw arrow
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 50));
		CP_Graphics_DrawEllipseAdvanced(player->arrow.aBody.hitbox.position.x, player->arrow.aBody.hitbox.position.y, player->arrow.aBody.hitbox.radius, player->arrow.aBody.hitbox.radius, player->rotation + 45.0f);
		//CP_Graphics_DrawRectAdvanced(player->arrow.currentPosition.x, player->arrow.currentPosition.y, player->arrow.width, player->arrow.width, player->rotation + 45.0f, 1);
	}
	else
	{
		//Draw player
		CP_Settings_Fill(playerColor);
		CP_Graphics_DrawEllipseAdvanced(player->pBody.hitbox.position.x, player->pBody.hitbox.position.y, player->pBody.hitbox.radius * 2, player->pBody.hitbox.radius * 2, player->rotation);

		//Draw arrow
		if (player->arrow.charging == 1)
		{
			//Draw arrow
			CP_Settings_Fill(CP_Color_Create(255, 255, 0, 100));
		}
		else if (player->arrow.charging == 0)
		{
			//Draw arrow
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			//CP_Graphics_DrawRectAdvanced(player->arrow.currentPosition.x, player->arrow.currentPosition.y, player->arrow.width, player->arrow.width, player->rotation + 45.0f, 1);
		}
		CP_Graphics_DrawEllipseAdvanced(player->arrow.aBody.hitbox.position.x, player->arrow.aBody.hitbox.position.y, player->arrow.aBody.hitbox.radius, player->arrow.aBody.hitbox.radius, player->rotation + 45.0f);
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
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 200));	
#if 1
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

	if (playerState != DODGING)
	{
		playerState = STILL;
		player->pBody.velocity = CP_Vector_Set(0, 0);
		if (GetBlobInputDown(BLOB_UP) && GetBlobInputDown(BLOB_LEFT))
		{
			playerState = MOVING;
			player->pBody.velocity = CP_Vector_Set(-1, -1);

			//player->rotation = -45.0f;
		}
		else if (GetBlobInputDown(BLOB_UP) && GetBlobInputDown(BLOB_RIGHT))
		{
			playerState = MOVING;
			player->pBody.velocity = CP_Vector_Set(1, -1);

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
			player->pBody.velocity = CP_Vector_Set(1, 1);

			//player->rotation = 135.0f;
		}
		else if (GetBlobInputDown(BLOB_DOWN) && GetBlobInputDown(BLOB_LEFT))
		{
			playerState = MOVING;
			player->pBody.velocity = CP_Vector_Set(-1, 1);

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

		if (CP_Input_KeyTriggered(KEY_SPACE) && playerState != STILL && (player->numDodge > 0))
		{
			playerState = DODGING;

			player->numDodge -= 1;
			player->pBody.velocity.x = player->pBody.velocity.x * (PLAYER_SPEED * (dodgeDistance / 20));
			player->pBody.velocity.y = player->pBody.velocity.y * (PLAYER_SPEED * (dodgeDistance / 20));
		}
		else if (playerState != DODGING)
		{
			player->pBody.velocity.x = (player->pBody.velocity.x * PLAYER_SPEED);
			player->pBody.velocity.y = (player->pBody.velocity.y * PLAYER_SPEED);
		}

	}
	Dodge(player);

	CollisionCheck(&newPlayer.pBody, level[0]);
	
	player->pBody.hitbox.position.x += player->pBody.velocity.x;		//Circle
	player->pBody.hitbox.position.y += player->pBody.velocity.y;
#if 1
	
#endif

	//Arrow
	if (playerArrowState == WITHPLAYER)
	{
		player->arrow.aBody.hitbox.position = player->pBody.hitbox.position;
	}

}


void MouseTracking(Player* player)
{
	mousePositionVector = CP_Vector_Subtract(CP_Vector_Set(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY()), player->pBody.hitbox.position);
	if (mousePositionVector.x < 0)
	{
		player->rotation = CP_Vector_Angle(mousePositionVector, CP_Vector_Set(0.0f, 1.0f)) + 180.0f;
	}
	else
	{
		player->rotation = CP_Vector_Angle(mousePositionVector, CP_Vector_Set(0.0f, -1.0f));
	}
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
		
		if (playerArrowState == WITHPLAYER)
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

void ArrowStateChange(Player* player, Arrow* arrow) // arrow release
{
	switch (playerArrowState) {
	case RELEASE:
		CalculateNewPosition(arrow, player->pBody);
		playerArrowState = MOTION;
		break;
	case MOTIONLESS:
		ArrowPlayerCollision(arrow, player->pBody); //pickup player
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
		{
			CalculateNewPosition(arrow, player->pBody);
			playerArrowState = RECALL;
		}
		break;
	case WITHPLAYER:
		arrow->aBody.hitbox.position = player->pBody.hitbox.position;
		break;
	default:
		break;
	}

	if (playerArrowState == MOTION || playerArrowState == RECALL)
	{
		ArrowInMotion(arrow);
	}
	
}

void ArrowTrigger(Player* player)
{
	if (playerState == STILL && playerArrowState == WITHPLAYER)
	{
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
		{
			player->arrow.charging = 1;
			if (player->arrow.chargeTimer <= 60)
			{
				player->arrow.chargeTimer += CP_System_GetDt() * 20;
			}

		}
		else if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
		{
			if (player->arrow.charging == 1)
			{
				playerArrowState = RELEASE;
				player->arrow.charging = 0;
			}
		}
	}

	else if (playerState == MOVING || playerState == DODGING)
	{
		player->arrow.chargeTimer = 0.0f;
		player->arrow.charging = 0;
	}

}

void DisplayScore(float score) //function to display the score on screen
{
	char scoreBuffer[15]; //buffer for value of score
	sprintf_s(scoreBuffer, 15, "Score: %d", (int)score); // print score into buffer

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
	CP_Color textColor = CP_Color_Create(255, 255, 255, 255); //set text to white, size to 20
	CP_Settings_Fill(textColor);
	CP_Settings_TextSize(20);
	CP_Font_DrawText(scoreBuffer, 30.f, 40.f); //display score at top left corner
}

/*Update Player*/
void PlayerUpdate(Player* player)
{
	if (player->health == 1)
	{
		PlayerMovement(player);
		ArrowStateChange(player, &(player->arrow));
		ArrowTrigger(player);
		DisplayScore(currentDistance);
	}
	else //when player is dead
	{
		//for now
		//move to game over screen later
		//set values to default if needed
		PlayerMovement(player);
		ArrowStateChange(player, &(player->arrow));
		ArrowTrigger(player);
	}

}