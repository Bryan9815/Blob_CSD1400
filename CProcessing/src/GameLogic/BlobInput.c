#pragma once
#include "BlobInput.h"

BlobKeys keys[6];

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
	keys[BLOB_UP] = CreateBlobButton(KEY_UP, KEY_UP, KEY_UP, "UP", "UP", "UP");
	keys[BLOB_DOWN] = CreateBlobButton(KEY_DOWN, KEY_DOWN, KEY_DOWN, "DOWN", "DOWN", "DOWN");
	keys[BLOB_LEFT] = CreateBlobButton(KEY_LEFT, KEY_LEFT, KEY_LEFT, "LEFT", "LEFT", "LEFT");
	keys[BLOB_RIGHT] = CreateBlobButton(KEY_RIGHT, KEY_RIGHT, KEY_RIGHT, "RIGHT", "RIGHT", "RIGHT");
	keys[BLOB_INTERACT] = CreateBlobButton(KEY_SPACE, KEY_ENTER, KEY_ENTER, "SPACE", "ENTER", "ENTER");
	keys[BLOB_PAUSE] = CreateBlobButton(KEY_ESCAPE, KEY_ESCAPE, KEY_ESCAPE, "ESC", "ESC", "ESC");
}

int GetBlobInput(BlobInput input)
{
	for (int i = 0; i < 3; i++)
	{
		if (CP_Input_KeyTriggered(keys[input].key[i]))
			return 1;
	}
	return 0;
}