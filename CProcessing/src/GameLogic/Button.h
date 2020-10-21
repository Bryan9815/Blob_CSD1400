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