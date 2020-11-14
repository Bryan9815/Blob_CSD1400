#include <stdio.h>
#include <stdlib.h>
#include <cprocessing.h>
#include <stdbool.h>
#include <stdio.h>
#include "grid.h"

/*Debug Flag*/
#define debug false

//TEST
CP_Image envSpriteSheet;

#define BUFFERSIZE 2000 * 2000
char levelData[BUFFERSIZE];

int levelWidth = 0, levelHeight = 0;

int GetLevelWidth()//Make error code
{
	return levelWidth;
}

int GetLevelHeight()//Make error code
{
	return levelHeight;
}

void LoadMapFile (MAP _level)	//Call Load before Rendering Map
{
	FILE* fp;

	char fileName[40];
	sprintf_s(fileName, 40, "././Assets/Level/Level%d.txt", (int)_level);

	errno_t err = fopen_s(&fp, fileName, "rt");
	int i = 0, w = 0, h = 0, finalWidth = 0;
	
	if (err == 0 && fp != NULL) /*Checks if file is open*/
	{
		while (!feof(fp)) /*While not at EOF for the file pf*/
		{
			
			levelData[i++] = (char)fgetc(fp);
			if (levelData[i - 1] == '\n' || levelData[i - 1] == EOF)
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



/*Initialize Grid*/
void GridInit()//Add starting point
{

	envSpriteSheet = CP_Image_Load("././Assets/EnvSpriteSheet.png");
	
	level = (GridUnit**)malloc(levelWidth * sizeof(GridUnit));

	for (int i = 0; i < levelWidth; i++)
	{
		*(level + i) = (GridUnit*)malloc(levelHeight * sizeof(GridUnit));
	}

#if 0
	//Boundary 1D
	for (int i = 0; i < GRID_SIZE; i++) {

		if (	i < GRID_WIDTH												/*Top Boundary*/
			|| (i % GRID_WIDTH) == 0										/*Left Boundary*/
			|| (i % GRID_WIDTH) == GRID_WIDTH - 1							/*Right Boundary*/
			|| i >= (GRID_HEIGHT - 1) * GRID_WIDTH && i < GRID_SIZE			/*Bottom Boundary*/
			) {
			grid[i] = GE_WALL;												//Set grid element to wall
		}
		else 
		{
			grid[i] = GE_VOID;												//Empty element		
		}
	}
#endif
#if 0 
	//Boundary 2D
	for (int i = 0; i < w; i++) 
	{
		for (int j = 0; j < h; j++)
		{
			if (i == 0											/*Top Boundary*/
				|| j == 0										/*Left Boundary*/
				|| i == GRID_WIDTH - 1							/*Right Boundary*/
				|| j == GRID_HEIGHT - 1							/*Bottom Boundary*/
				) 
			{
				grid[i * h + j] = GE_WALL;												//Set grid element to wall
			}
			else
			{
				grid[i * h + j] = GE_VOID;												//Empty element		
			}
		}
	}
#endif
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

				(*(level + j) + k)->gridType = GE_FLOOR;
				(*(level + j) + k)->gridAsset = GA_FLOOR;
				(*(level + j) + k)->collider.shapeType = COL_RECT;								//RECT COLLIDER
				(*(level + j) + k)->collider.position.x = (float)(j * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2);
				(*(level + j) + k)->collider.position.y = (float)(k * GRID_UNIT_HEIGHT + GRID_UNIT_HEIGHT / 2);
				(*(level + j) + k)->collider.width = (float)(GRID_UNIT_WIDTH);
				(*(level + j) + k)->collider.height = (float)(GRID_UNIT_HEIGHT);

			}
			else if (levelData[i] == '-' || levelData[i] == '=' || levelData[i] == '|') //WALL
			{

				(*(level + j) + k)->gridType = GE_WALL;
				(*(level + j) + k)->collider.shapeType = COL_RECT;								//RECT COLLIDER

				(*(level + j) + k)->collider.position.x = (float)(j * GRID_UNIT_WIDTH + GRID_UNIT_WIDTH / 2);
				(*(level + j) + k)->collider.position.y = (float)(k * GRID_UNIT_HEIGHT + GRID_UNIT_WIDTH / 2);
				(*(level + j) + k)->collider.width = (float)(GRID_UNIT_WIDTH);
				(*(level + j) + k)->collider.height = (float)(GRID_UNIT_HEIGHT);
				

				if (levelData[i] == '-')
					(*(level + j) + k)->gridAsset = GA_WALL1;
				else if (levelData[i] == '=')
					(*(level + j) + k)->gridAsset = GA_WALL2;
				else if (levelData[i] == '|')
					(*(level + j) + k)->gridAsset = GA_WALL3;

			}

			j++;

		}
	printf("%s\n", levelData);
}



void GridDraw(int i , int j, Collider playerHitBox)
{
	//Checks thru all the elements
	
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
			64.0f, 64.0f, 128.0f, 128.0f,
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
void GridUpdate(Collider playerHitBox)
{	
	for (int i = 0; i < levelWidth; i++)
	{
		for (int j = 0; j < levelHeight; j++)
		{
			GridDraw(i, j, playerHitBox);
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