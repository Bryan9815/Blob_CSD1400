//---------------------------------------------------------
// file:	scr_tutorial.h
// author:	[Phang Jia Rong]
// email:	[jiarong.phang@digipen.edu]
//
// brief:	Header for tutorial.c
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

#include "../Player/player.h"
//#include "../Camera/Camera.h"
#include "../GameLogic/ScreenManager.h"

void TutorialInit(void);
void TutorialUpdate(Player* player);
void TutorialExit(void);