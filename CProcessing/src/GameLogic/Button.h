//---------------------------------------------------------
// file:	Button.h
// author:	[Teh Kai Hong Bryan]
// email:	[t.kaihongbryan@digipen.edu]
//
// brief:	Header file for Button.c
//
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include <cprocessing.h>

typedef struct Button {
	float posX;
	float posY;
	float width;
	float height;
	float alpha;
	const char* text;
	int isSelected;
	CP_Color objColor;
}Button;

Button CreateButton(float x, float y, float w, float h, const char* text);
void DrawButton(Button button, float textSize, float scale, CP_Color buttonColor);