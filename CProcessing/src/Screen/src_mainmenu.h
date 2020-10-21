#pragma once
void MainMenuInit(void);
void MainMenuUpdate(void);
void MainMenuExit(void);

typedef struct
{
	float posX;
	float posY;
	float width;
	float height;
	float alpha;
	const char *text;
	int isSelected;
	CP_Color objColor;
}Button;