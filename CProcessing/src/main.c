//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include <stdio.h>
#include "GameLogic/ScreenManager.h"
#include <crtdbg.h>
#include <stdlib.h>

static const float WINDOW_SCALE = 0.8f;
static const int WINDOW_WIDTH = 1600, WINDOW_HEIGHT = 900;


// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	CP_System_SetWindowTitle("Blob");

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CP_System_SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	/*The following stuff is for console output.
	The current console output function from CProcessing
	is being fixed*/

	CP_System_ShowConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	/*
	void* asd = malloc(1000);
	asd;
	free(asd);
	*/
	//free(asd);
#else
	CP_System_Fullscreen();
	//CP_System_FullscreenAdvanced(WINDOW_WIDTH, WINDOW_HEIGHT);
#endif

	CP_System_SetFrameRate(60.0f);


	// Run Game
	CP_Engine_SetNextGameState(GameInit, GameUpdate, GameExit);
	CP_Engine_Run();
	return 0;
}
