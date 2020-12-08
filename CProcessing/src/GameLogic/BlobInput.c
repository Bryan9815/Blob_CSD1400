//---------------------------------------------------------
// file:	BlobInput.c
// author:	[Teh Kai Hong Bryan]
// email:	[t.kaihongbryan@digipen.edu]
//
// brief:	Get and set custom inputs for the whole game
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include "BlobInput.h"
#include <stdio.h>

BlobKeys keys[6];	//Use Enum Any as the greatest num instead of hardcoding it at 6
char turnInputToChar[40];

// Creates BlobKey
BlobKeys CreateBlobButton(CP_KEY k1, CP_KEY k2, const char* ck1, const char* ck2)
{
	BlobKeys newKey;
	newKey.key[0] = k1;
	newKey.key[1] = k2;

	newKey.c_key[0] = ck1;
	newKey.c_key[1] = ck2;

	return newKey;
}

// Initializes default controls
void BlobInputInit()
{
	keys[BLOB_UP] = CreateBlobButton(KEY_UP, KEY_W, "UP", "W");
	keys[BLOB_DOWN] = CreateBlobButton(KEY_DOWN, KEY_S, "DOWN", "S");
	keys[BLOB_LEFT] = CreateBlobButton(KEY_LEFT, KEY_A, "LEFT", "A");
	keys[BLOB_RIGHT] = CreateBlobButton(KEY_RIGHT, KEY_D, "RIGHT", "D");
	keys[BLOB_INTERACT] = CreateBlobButton(KEY_SPACE, KEY_ENTER, "SPACE", "ENTER");
	keys[BLOB_PAUSE] = CreateBlobButton(KEY_ESCAPE, KEY_P, "ESC", "P");
	//keys[BLOB_SKIP] = CreateBlobButton(KEY_X, KEY_X, KEY_X, "X", "X", "X");
}

// Checks if a BlobInput was triggered
int GetBlobInputTriggered(BlobInput input)
{
	for (int i = 0; i < 3; i++)
	{
		if (CP_Input_KeyTriggered(keys[input].key[i]))
			return 1;
	}
	return 0;
}

// Checks if a BlobInput is held down
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

// Checks if a BlobInput was released
int GetBlobInputReleased(BlobInput input)
{
	for (int i = 0; i < 3; i++)
	{
		if (CP_Input_KeyReleased(keys[input].key[i]))
			return 1;
	}
	return 0;
}

// Returns the requested BlobInput name
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

// Returns the requested BlobKey name
const char* GetBlobKeyName(BlobInput input, int keyNum)
{
	if (input <= BLOB_PAUSE && keyNum < 2)
		return keys[input].c_key[keyNum];
	else
		return keys[BLOB_PAUSE].c_key[1];
}

// Setter function for BlobInput, also checks if new input is already in a different BlobInput and swaps them if it is
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