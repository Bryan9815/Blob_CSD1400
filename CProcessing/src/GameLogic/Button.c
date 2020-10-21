#include "Button.h"

Button CreateButton(float x, float y, float w, float h, const char* text)
{
	Button newButton;
	newButton.posX = x;
	newButton.posY = y;
	newButton.width = w;
	newButton.height = h;
	newButton.text = text;

	return newButton;
}

void DrawButton(Button button, float textSize, float scale, CP_Color buttonColor)
{
	CP_Settings_Fill(buttonColor);
	CP_Graphics_DrawRect(button.posX, button.posY, button.width * scale, button.height * scale);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(textSize * scale);
	CP_Font_DrawText(button.text, button.posX, button.posY);
}