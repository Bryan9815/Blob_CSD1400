#include <stdio.h>
#include <stdlib.h>
#include <cprocessing.h>
#include <stdbool.h>
#include "grid.h"

/*Debug Flag*/
#define debug false

//TEST
CP_Image tile1;
CP_Image tile2;

/*Initialize Grid*/
void GridInit(GRID_ELEMENTS* grid, int w, int h)//Add starting point
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
}

/*Draw Call/Update Function for Grid*/
void GridUpdate(GRID_ELEMENTS* grid, int w, int h)
{
	//Checks thru all the elements
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++) 
		{
#if !debug
			switch (grid[i * h + j])
			{
			case GE_WALL:
				CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
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
				CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
				CP_Settings_ImageMode(CP_POSITION_CORNER);
				CP_Image_Draw(
					tile1,
					(float)GRID_UNIT_WIDTH * i,
					(float)GRID_UNIT_HEIGHT * j,
					GRID_UNIT_WIDTH,
					GRID_UNIT_HEIGHT,
					255);
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