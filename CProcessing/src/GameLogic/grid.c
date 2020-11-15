#include <stdio.h>
#include <stdlib.h>
#include <cprocessing.h>
#include <stdbool.h>
#include <stdio.h>
#include "grid.h"

/*Debug Flag*/
#define debug false

//ASSET
CP_Image envSpriteSheet;

//BUFFER SIZE FOR MAP
#define BUFFERSIZE 2000 * 2000

//DATA FOR MAP
char *levelData;

//HEIGHT AND WIDTH OF GRID
int levelWidth = 0, levelHeight = 0;

//ASSETS
#define TEXTURESIZE 64

int GetLevelWidth()//LEVEL WIDTH
{
	return levelWidth;
}

int GetLevelHeight()//LEVEL HEIGHT
{
	return levelHeight;
}

void LoadMapFile (MAP _level)	//Call FUNC to load map from file
{
	FILE* fp;

	char fileName[40];
	sprintf_s(fileName, 40, "././Assets/Level/Level%d.txt", (int)_level);	//Checks by enum

	levelData = (char*)malloc(BUFFERSIZE * sizeof(char));

	errno_t err = fopen_s(&fp, fileName, "rt");
	int i = 0, w = 0, h = 0, finalWidth = 0;
	
	if (err == 0 && fp != NULL) /*Checks if file is open*/
	{
		while (!feof(fp)) /*While not at EOF for the file pf*/
		{
			
			*(levelData + i++) = (char)fgetc(fp);
			if (*(levelData + i - 1) == '\n' || *(levelData + i - 1) == EOF)
			{
				if (finalWidth < w)
					finalWidth = w - 1;
				w = 0;
				h++;
			}
			w++;
		}
		fclose(fp);
	}
	else 
	{
		printf("File Not Found");	//Error checking
	}
	
	levelWidth = finalWidth;
	levelHeight = h;
}

/*	GRID DEFAULT VARIABLES
	unit->gridType = GE_VOID;
	unit->collider.shapeType = COL_RECT;								
	unit->collider.position.x = (float)(x * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2);
	unit->collider.position.y = (float)(y * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2);
	unit->collider.width = (float)(GRID_UNIT_WIDTH);
	unit->collider.height = (float)(GRID_UNIT_HEIGHT);
	unit->gridAsset = GA_VOID;
	unit->isActive = true;
	unit->isCollidable = false;
*/
void GridUnitInit(GridUnit * unit, int x, int y) 

{
	
}

/*Initialize Grid*/
void GridInit()//Add starting point
{

	envSpriteSheet = CP_Image_Load("././Assets/EnvSpriteSheet.png");
	
	//Allocate Memory for Level
	level = (GridUnit**)malloc(levelWidth * sizeof(GridUnit));

	for (int i = 0; i < levelWidth; i++)
	{
		*(level + i) = (GridUnit*)malloc(levelHeight * sizeof(GridUnit));
	}

	//Level Variables
	for (int i = 0, j = 0, k = 0; i < levelWidth * levelHeight + levelHeight; i++)
	{
		if (levelData[i] == '\n')
		{
			j = 0;
			k++;
			continue;
		}

		if (levelData[i] == (char)32) //Floor
		{

			(*(level + j) + k)->collider.shapeType = COL_RECT;				//RECT COLLIDER					
			(*(level + j) + k)->collider.position.x = (float)(j * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2);
			(*(level + j) + k)->collider.position.y = (float)(k * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2);
			(*(level + j) + k)->collider.width = (float)(GRID_UNIT_WIDTH) / 5;
			(*(level + j) + k)->collider.height = (float)(GRID_UNIT_HEIGHT);

			(*(level + j) + k)->isCollidable = false;
			(*(level + j) + k)->isActive = true;

			(*(level + j) + k)->gridType = GE_FLOOR;
			(*(level + j) + k)->gridAsset = GA_FLOOR;

		}
		else if (levelData[i] == '-' || levelData[i] == '=' || levelData[i] == '|') //WALL
		{

			(*(level + j) + k)->gridType = GE_WALL;
				
			(*(level + j) + k)->collider.shapeType = COL_RECT;				//RECT COLLIDER					
			(*(level + j) + k)->collider.position.x = (float)(j * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2);
			(*(level + j) + k)->collider.position.y = (float)(k * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2);
			(*(level + j) + k)->collider.width = (float)(GRID_UNIT_WIDTH) / 5;
			(*(level + j) + k)->collider.height = (float)(GRID_UNIT_HEIGHT);

			(*(level + j) + k)->isCollidable = true;
			(*(level + j) + k)->isActive = true;

			if (levelData[i] == '-')
				(*(level + j) + k)->gridAsset = GA_WALL1;
			else if (levelData[i] == '=')
				(*(level + j) + k)->gridAsset = GA_WALL2;
			else if (levelData[i] == '|')
				(*(level + j) + k)->gridAsset = GA_WALL3;


		}
		else if(levelData[i] == '\\')
		{

			(*(level + j) + k)->gridType = GE_DAMAGE;

			(*(level + j) + k)->collider.shapeType = COL_RECT;				//RECT COLLIDER					
			(*(level + j) + k)->collider.position.x = (float)(j * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2);
			(*(level + j) + k)->collider.position.y = (float)(k * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2);
			(*(level + j) + k)->collider.width = (float)(GRID_UNIT_WIDTH) / 5;
			(*(level + j) + k)->collider.height = (float)(GRID_UNIT_HEIGHT);

			(*(level + j) + k)->isCollidable = false;
			(*(level + j) + k)->isActive = true;
			
			(*(level + j) + k)->gridAsset = GA_DAMAGE1;

		}
		else if (levelData[i] == 'X')
		{

			(*(level + j) + k)->gridType = GE_PIT;

			(*(level + j) + k)->collider.shapeType = COL_RECT;				//RECT COLLIDER					
			(*(level + j) + k)->collider.position.x = (float)(j * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2);
			(*(level + j) + k)->collider.position.y = (float)(k * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2);
			(*(level + j) + k)->collider.width = (float)(GRID_UNIT_WIDTH);
			(*(level + j) + k)->collider.height = (float)(GRID_UNIT_HEIGHT);

			(*(level + j) + k)->isCollidable = true;
			(*(level + j) + k)->isActive = true;

			(*(level + j) + k)->gridAsset = GA_PIT;
			
		}
		else if (levelData[i] == 'S')
		{

			(*(level + j) + k)->gridType = GE_SWITCH;

			(*(level + j) + k)->collider.shapeType = COL_RECT;				//RECT COLLIDER					
			(*(level + j) + k)->collider.position.x = (float)(j * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2);
			(*(level + j) + k)->collider.position.y = (float)(k * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2);
			(*(level + j) + k)->collider.width = (float)(GRID_UNIT_WIDTH);
			(*(level + j) + k)->collider.height = (float)(GRID_UNIT_HEIGHT);

			(*(level + j) + k)->isCollidable = true;
			(*(level + j) + k)->isActive = false;

			(*(level + j) + k)->gridAsset = GA_SWITCH;

			
		}
		else if (levelData[i] == 'D')
		{

			(*(level + j) + k)->gridType = GE_DOOR;

			(*(level + j) + k)->collider.shapeType = COL_RECT;				//RECT COLLIDER					
			(*(level + j) + k)->collider.position.x = (float)(j * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2);
			(*(level + j) + k)->collider.position.y = (float)(k * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2);
			(*(level + j) + k)->collider.width = (float)(GRID_UNIT_WIDTH);
			(*(level + j) + k)->collider.height = (float)(GRID_UNIT_HEIGHT);

			(*(level + j) + k)->isActive = true;
			(*(level + j) + k)->isCollidable = true;

			(*(level + j) + k)->gridAsset = GA_DOOR;

		}
		else if (levelData[i] == 'P')
		{

			(*(level + j) + k)->gridType = GE_PORTAL;
			(*(level + j) + k)->collider.shapeType = COL_RECT;				//RECT COLLIDER					
			(*(level + j) + k)->collider.position.x = (float)(j * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2);
			(*(level + j) + k)->collider.position.y = (float)(k * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2);
			(*(level + j) + k)->collider.width = (float)(GRID_UNIT_WIDTH);
			(*(level + j) + k)->collider.height = (float)(GRID_UNIT_HEIGHT);

			(*(level + j) + k)->isActive = true;
			(*(level + j) + k)->isCollidable = false;

			(*(level + j) + k)->gridAsset = GA_PORTAL;

		}

		j++;

	}
	
#if 0
	printf("%s\n", levelData);
#endif
	free(levelData);
}



void GridDraw(Collider playerHitBox)
{
	//Checks thru all the elements
	for (int i = 0; i < levelWidth; i++)
	{
		for (int j = 0; j < levelHeight; j++)
		{
			#if !debug
			switch (level[i][j].gridAsset)
			{
			case GA_FLOOR:
				CP_Settings_ImageMode(CP_POSITION_CENTER);
				CP_Image_DrawSubImage(
					envSpriteSheet,
					(float)(i * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2),
					(float)(j * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2),
					GRID_UNIT_WIDTH + 2,
					GRID_UNIT_HEIGHT + 2,
					//0, 64.0f, 64.0f, 128.0f,
					1 * TEXTURESIZE, 1 * TEXTURESIZE, 2 * TEXTURESIZE, 2 * TEXTURESIZE,
					255);
				break;
			case GA_PIT:
				CP_Settings_ImageMode(CP_POSITION_CENTER);
				CP_Image_DrawSubImage(
					envSpriteSheet,
					(float)(i * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2),
					(float)(j * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2),
					GRID_UNIT_WIDTH + 2,
					GRID_UNIT_HEIGHT + 2,
					2 * TEXTURESIZE, 1 * TEXTURESIZE, 3 * TEXTURESIZE, 2 * TEXTURESIZE,
					255);
				break;
			case GA_WALL1:
				CP_Settings_ImageMode(CP_POSITION_CENTER);
				CP_Image_DrawSubImage(
					envSpriteSheet,
					(float)(i * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2),
					(float)(j * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2),
					GRID_UNIT_WIDTH + 2,
					GRID_UNIT_HEIGHT + 2,
					64.0f, 0, 128.0f, 64.0f,
					255);
				break;
			case GA_WALL2:
				CP_Settings_ImageMode(CP_POSITION_CENTER);
				CP_Image_DrawSubImage(
					envSpriteSheet,
					(float)(i * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2),
					(float)(j * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2),
					GRID_UNIT_WIDTH + 2,
					GRID_UNIT_HEIGHT + 2,
					0, 0, 64.0f, 64.0f,
					255);
				break;
			case GA_WALL3:
				CP_Settings_ImageMode(CP_POSITION_CENTER);
				CP_Image_DrawSubImage(
					envSpriteSheet,
					(float)(i * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2),
					(float)(j * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2),
					GRID_UNIT_WIDTH + 2,
					GRID_UNIT_HEIGHT + 2,
					128.0f, 0.0f, 192.0f, 64.0f,
					255);
				break;
			case GA_SWITCH:
				//
				CP_Settings_RectMode(CP_POSITION_CENTER);
				if(!level[i][j].isActive)
					CP_Settings_Fill(CP_Color_Create(255, 192, 203, 255));
				else
					CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
				CP_Graphics_DrawRect(
					(float)(i * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2),
					(float)(j * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2),
					GRID_UNIT_WIDTH,
					GRID_UNIT_HEIGHT);
				break;
			case GA_DOOR:
				CP_Settings_RectMode(CP_POSITION_CENTER);
				if (level[i][j].isActive)
					CP_Settings_Fill(CP_Color_Create(210, 105, 30, 255));
				else
					CP_Settings_Fill(CP_Color_Create(0, 0, 0, 0));
				CP_Graphics_DrawRect(
					(float)(i * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2),
					(float)(j * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2),
					GRID_UNIT_WIDTH,
					GRID_UNIT_HEIGHT);
				break;
			case GA_PORTAL:
				CP_Settings_RectMode(CP_POSITION_CENTER);
				CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));
				CP_Graphics_DrawRect(
					(float)(i * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2),
					(float)(j * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2),
					GRID_UNIT_WIDTH,
					GRID_UNIT_HEIGHT);
				break;
			case GA_VOID:
				CP_Settings_RectMode(CP_POSITION_CENTER);
				CP_Settings_Fill(CP_Color_Create(255, 255, 255, 30));
				CP_Graphics_DrawRect(
					(float)(i * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2),
					(float)(j * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2),
					GRID_UNIT_WIDTH,
					GRID_UNIT_HEIGHT);
				break;
			}
		}
	}

		
#endif
	

#if debug
	char _buffer[20];
	snprintf(_buffer, 20, "%d", i - '0');
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText(_buffer,
		(CP_System_GetWindowWidth() / (float)gridW) * (i % gridW),
		(CP_System_GetWindowHeight() / (float)gridH) * (i / gridW));

#endif	
}


/*Draw Call/Update Function for Grid*/
void GridUpdate(Collider playerHitBox, Collider arrowHitBox)
{	
	for (int i = 0; i < levelWidth; i++)
	{
		for (int j = 0; j < levelHeight; j++)
		{
			if (level[i][j].gridType == GE_SWITCH) 
			{
				if (COL_IsColliding(arrowHitBox, level[i][j].collider))
				{
					level[i][j].isActive = !level[i][j].isActive;
				}
			}
				//GridDraw(i, j, playerHitBox);
		}
	}
	
}

void GridExit() 
{

	for (int i = 0; i < levelWidth; i++)
	{
		free(*(level + i));
	}
	free(level);

	CP_Image_Free(&envSpriteSheet);
}

GridUnit* GetGridUnit(int x, int y) 
{
	return &(level[x][y]);
}