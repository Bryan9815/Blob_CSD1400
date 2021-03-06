﻿//---------------------------------------------------------
// file:	BlobInput.h
// author:	[Teh Kai Hong Bryan]
// email:	[t.kaihongbryan@digipen.edu]
//
// brief:	Header file for BlobInput.c
//
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include <cprocessing.h>

typedef enum BlobInput {
	BLOB_UP,
	BLOB_DOWN,
	BLOB_LEFT,
	BLOB_RIGHT,
	BLOB_INTERACT,
	BLOB_PAUSE,
	BLOB_SKIP,
	ANY,
}BlobInput;

typedef struct BlobKeys {
	CP_KEY key[2];
	const char* c_key[2];
	char new_c_key[2][40];
}BlobKeys;

void BlobInputInit();
int GetBlobInputTriggered(BlobInput input);
int GetBlobInputDown(BlobInput input);
int GetBlobInputReleased(BlobInput input);
const char* GetBlobInputName(BlobInput input);
const char* GetBlobKeyName(BlobInput input, int keyNum);
void EditBlobInput(BlobInput blobInput, int keyNum, CP_KEY newInput);