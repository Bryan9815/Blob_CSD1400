#pragma once
#include "BlobInput.h"
#include <stdio.h>

BlobKeys keys[6];	//Use Enum Any as the greatest num instead of hardcoding it at 6
char turnInputToChar[40];

BlobKeys CreateBlobButton(CP_KEY k1, CP_KEY k2, CP_KEY k3, const char* ck1, const char* ck2, const char* ck3)
{
	BlobKeys newKey;
	newKey.key[0] = k1;
	newKey.key[1] = k2;
	newKey.key[2] = k3;

	newKey.c_key[0] = ck1;
	newKey.c_key[1] = ck2;
	newKey.c_key[2] = ck3;

	return newKey;
}

void BlobInputInit()
{
	keys[BLOB_UP] = CreateBlobButton(KEY_UP, KEY_W, KEY_I, "UP", "W", "I");
	keys[BLOB_DOWN] = CreateBlobButton(KEY_DOWN, KEY_S, KEY_K, "DOWN", "S", "K");
	keys[BLOB_LEFT] = CreateBlobButton(KEY_LEFT, KEY_A, KEY_J, "LEFT", "A", "J");
	keys[BLOB_RIGHT] = CreateBlobButton(KEY_RIGHT, KEY_D, KEY_L, "RIGHT", "D", "L");
	keys[BLOB_INTERACT] = CreateBlobButton(KEY_SPACE, KEY_ENTER, KEY_ENTER, "SPACE", "ENTER", "ENTER");
	keys[BLOB_PAUSE] = CreateBlobButton(KEY_ESCAPE, KEY_ESCAPE, KEY_ESCAPE, "ESC", "ESC", "ESC");
	//keys[BLOB_SKIP] = CreateBlobButton(KEY_X, KEY_X, KEY_X, "X", "X", "X");
}

int GetBlobInputTriggered(BlobInput input)
{
	for (int i = 0; i < 3; i++)
	{
		if (CP_Input_KeyTriggered(keys[input].key[i]))
			return 1;
	}
	return 0;
}

int GetBlobInputDown(BlobInput input)
{
	for (int i = 0; i < 3; i++)
	{		
		if (CP_Input_KeyDown(keys[input].key[i]))
			return 1;
	}
	if (input == ANY)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < BLOB_PAUSE; j++)
			{
				if (CP_Input_KeyDown(keys[j].key[i]))
					return 1;
			}
		}
	}
	return 0;
}

int GetBlobInputReleased(BlobInput input)
{
	for (int i = 0; i < 3; i++)
	{
		if (CP_Input_KeyReleased(keys[input].key[i]))
			return 1;
	}
	return 0;
}

const char* GetBlobInputName(BlobInput input)
{
	switch (input)
	{
	case BLOB_UP:
		return "Up";
		break;
	case BLOB_DOWN:
		return "Down";
		break;
	case BLOB_LEFT:
		return "Left";
		break;
	case BLOB_RIGHT:
		return "Right";
		break;
	case BLOB_INTERACT:
		return "Interact";
		break;
	case BLOB_PAUSE:
		return "Pause";
		break;
	default:
		return "";
		break;
	}
}

const char* GetBlobKeyName(BlobInput input, int keyNum)
{
	if (input <= BLOB_PAUSE && keyNum < 3)
		return keys[input].c_key[keyNum];
	else
		return keys[BLOB_PAUSE].c_key[2];
}

void EditBlobInput(BlobInput blobInput, int keyNum, CP_KEY newInput)
{
	for (int i = 0; i <= BLOB_PAUSE; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			if (keys[i].key[j] == newInput)
			{
				keys[i].key[j] = keys[blobInput].key[keyNum];
				keys[i].c_key[j] = keys[blobInput].c_key[keyNum];
			}
		}
	}
	keys[blobInput].key[keyNum] = newInput;
	switch (newInput)
	{
	case KEY_UP:
		keys[blobInput].c_key[keyNum] = "UP";
		break;
	case KEY_DOWN:
		keys[blobInput].c_key[keyNum] = "DOWN";
		break;
	case KEY_LEFT:
		keys[blobInput].c_key[keyNum] = "LEFT";
		break;
	case KEY_RIGHT:
		keys[blobInput].c_key[keyNum] = "RIGHT";
		break;
	case KEY_ENTER:
		keys[blobInput].c_key[keyNum] = "ENTER";
		break;
	case KEY_SPACE:
		keys[blobInput].c_key[keyNum] = "SPACE";
		break;
	case KEY_ESCAPE:
		keys[blobInput].c_key[keyNum] = "ESC";
		break;
	default:
		sprintf_s(keys[blobInput].new_c_key[keyNum], sizeof newInput, "%c", newInput);
		keys[blobInput].c_key[keyNum] = keys[blobInput].new_c_key[keyNum];
		break;
	}
}