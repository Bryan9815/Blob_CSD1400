#include <stdio.h>
#include <stdlib.h>
#include <cprocessing.h>
#include <stdbool.h>
#include <stdio.h>

#include "grid.h"

/*Debug Flag*/
#define debug false

//TEST
CP_Image tile1;
CP_Image tile2;

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

void LoadMapFile (MAP level)	//Call Load before Rendering Map
{
	FILE* fp;

	char fileName[40];
	sprintf_s(fileName, 40, "././Assets/Level/Level%d.txt", (int)level);

	errno_t err = fopen_s(&fp, fileName, "rt");
	int i = 0, w = 0, h = 1, finalWidth = 0;
	
	if (err == 0 && fp != NULL) /*Checks if file is open*/
	{
		while (!feof(fp)) /*While not at EOF for the file pf*/
		{
			
			levelData[i++] = (char)fgetc(fp);
			if (levelData[i - 1] == '\n')
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
void GridInit(GRID_ELEMENTS* grid)//Add starting point
{
	
	tile1 = CP_Image_Load("././Assets/Tile1.png");
	tile2 = CP_Image_Load("././Assets/Tile2.png");
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
	
	for (int i = 0, j = 0 ,k = 0; i < levelWidth * levelHeight + levelHeight; i++)
	{
		if (levelData[i] == '\n')
		{
			j = 0;
			k++;
			continue;
		}

		if (levelData[i] == (char)32) //Floor
		{
			grid[j * levelHeight + k] = GE_FlOOR;
		}
		else if (levelData[i] == '-') //WALL
		{
			grid[j * levelHeight + k] = GE_WALL;
		}
		
		j++;
		
	}
	printf("%s\n", levelData);
}

/*Draw Call/Update Function for Grid*/
void GridUpdate(GRID_ELEMENTS* grid)
{
	//Checks thru all the elements
	for (int i = 0; i < levelWidth; i++)
	{
		for (int j = 0; j < levelHeight; j++)
		{
#if !debug
			switch (grid[i * levelHeight + j])
			{
			case GE_FlOOR:
				CP_Settings_ImageMode(CP_POSITION_CORNER);
				CP_Image_Draw(
					tile1,
					(float)GRID_UNIT_WIDTH * i,
					(float)GRID_UNIT_HEIGHT * j,
					GRID_UNIT_WIDTH,
					GRID_UNIT_HEIGHT,
					255);
				break;
			case GE_WALL:
				CP_Settings_ImageMode(CP_POSITION_CORNER);
				CP_Image_Draw(
					tile2,
					(float)GRID_UNIT_WIDTH * i,
					(float)GRID_UNIT_HEIGHT * j,
					GRID_UNIT_WIDTH,
					GRID_UNIT_HEIGHT,
					255);
#if 0
				CP_Graphics_DrawRect(
					(float)GRID_UNIT_WIDTH * i,
					(float)GRID_UNIT_HEIGHT * j,
					GRID_UNIT_WIDTH,
					GRID_UNIT_HEIGHT);
#endif
				break;
			case GE_VOID:
				CP_Settings_Fill(CP_Color_Create(255, 255, 255, 30));
				CP_Graphics_DrawRect(
					(float)GRID_UNIT_WIDTH * i,
					(float)GRID_UNIT_HEIGHT * j,
					GRID_UNIT_WIDTH,
					GRID_UNIT_HEIGHT);
				break;
			}

		}
#endif
	}

#if debug
	char _buffer[20];
	snprintf(_buffer, 20, "%d", i - '0');
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText(_buffer,
		(CP_System_GetWindowWidth() / (float)gridW) * (i % gridW),
		(CP_System_GetWindowHeight() / (float)gridH) * (i / gridW));
	
#endif	

}