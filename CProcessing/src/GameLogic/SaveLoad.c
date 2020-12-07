#include <stdio.h>
#include <stdlib.h>
#include "ScreenManager.h"
#include <string.h>

char fileName[] = "././savedata.txt";

#define DATA_ELEMENTS 9 //Number of elements to save inc of last line
#define BUFFER 255

typedef struct Data
{
    char* dataStr;

}Data;

Data * gameData;

void LoadData(FILE* stream)
{
    
    gameData = (Data*)malloc(DATA_ELEMENTS * sizeof(Data));
    if (gameData)
    {
        for (size_t i = 0; i < DATA_ELEMENTS; i++)
        {
            (gameData + i)->dataStr = malloc(BUFFER);
        }


        int i = 0;
        while (!feof(stream))
        {
            char buffer[BUFFER];

            fgets(buffer, BUFFER, stream);
            if ((gameData + i)->dataStr)
            {
                strcpy_s((gameData + i)->dataStr, BUFFER, buffer);
            }
            i++;
        }


        //Volume
        //if ((gameData)->dataStr) 
        SetBGMVolume((float)atof(gameData->dataStr));               //printf("Volume is set to %f, from %s\n", GetBGMVolume(), gameData[0].dataStr);
            
        //if ((gameData[1].dataStr))
        SetSFXVolume((float)atof((gameData + 1)->dataStr));         //printf("Volume is set to %f, from %s\n", GetSFXVolume(), gameData[1].dataStr);
           
        /*
        for (size_t j = 0; j < BLOB_PAUSE + 1; j++)
        {
            CP_KEY key0, key1, key2;
            char c_key0[40], c_key1[40], c_key2[40];

            int errorcheck = sscanf_s((gameData + 2 + j)->dataStr, "%ld %ld %ld %s %s %s", &key0, &key1, &key2, c_key0, 40, c_key1, 40, c_key2, 40);

            printf("%d %d %d %s %s %s, %d\n", key0, key1, key2, c_key0, c_key1, c_key2, errorcheck);
            if(errorcheck == 6)
                keys[j] = CreateBlobButton(key0, key1, key2, c_key0, c_key1, c_key2);
        }*/
        
        for (size_t k = 0; k < DATA_ELEMENTS; k++)
        {
            free((gameData + k)->dataStr);
        }
    }
    free(gameData);

}

void LoadGame()
{
    FILE* fp;

    fopen_s(&fp, fileName, "rt");

    if (fp != NULL) 
    {
        LoadData(fp);
        fclose(fp);
    }      
    
}

void SaveData(FILE * stream) 
{
    char _buffer[BUFFER];

    //Volume
    sprintf_s(_buffer, BUFFER, "%.2f", GetBGMVolume());
    fprintf(stream, "%s\n", _buffer);

    sprintf_s(_buffer, BUFFER, "%.2f", GetSFXVolume());
    fprintf(stream, "%s\n", _buffer);

    //Controls
    /*for (size_t i = 0; i < BLOB_PAUSE + 1; i++)
    {
        sprintf_s(_buffer, BUFFER, "%ld %ld %ld %s %s %s", keys[i].key[0], keys[i].key[1], keys[i].key[2], keys[i].c_key[0], keys[i].c_key[1], keys[i].c_key[2]);
        fprintf(stream, "%s\n", _buffer);
    }*/
   
    //Score



    

}

void SaveGame()
{

    FILE *fp;
    fopen_s(&fp, fileName, "wt");

    if (fp)
    {
        
        SaveData(fp);
        
        fclose(fp);
    }
}