#pragma once
#include <cprocessing.h>

typedef enum BlobInput {
	BLOB_UP,
	BLOB_DOWN,
	BLOB_LEFT,
	BLOB_RIGHT,
	BLOB_INTERACT,
	BLOB_PAUSE,
}BlobInput;

typedef struct BlobButtons {
	CP_KEY key[3];
	const char* c_key[3];
}BlobButtons;

void BlobInputInit();
int GetBlobInput(BlobInput input);