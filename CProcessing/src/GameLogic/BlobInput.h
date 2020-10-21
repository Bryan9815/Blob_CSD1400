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

typedef struct BlobKeys {
	CP_KEY key[3];
	const char* c_key[3];
}BlobKeys;

void BlobInputInit();
int GetBlobInput(BlobInput input);