#include <stdio.h>
#include <stdlib.h>
#include "ScreenManager.h"

char fileName[] = "././savedata.txt";

#define DATA_ELEMENTS 3 //Number of elements to save inc of last line
#define BUFFER 255

typedef struct Data
{
    //char dataStr[BUFFER];
    char* dataStr;
}Data;

//Data gameData[DATA_ELEMENTS];//Maybe use malloc for this
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
        if ((gameData)->dataStr) 
            SetBGMVolume((float)atof(gameData->dataStr));               //printf("Volume is set to %f, from %s\n", GetBGMVolume(), gameData[0].dataStr);
            
        if ((gameData[1].dataStr))
            SetSFXVolume((float)atof((gameData + 1)->dataStr));         //printf("Volume is set to %f, from %s\n", GetSFXVolume(), gameData[1].dataStr);
                    

        for (size_t j = 0; j < DATA_ELEMENTS; j++)
        {
            free((gameData + j)->dataStr);
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
    char _buffer[50];

    //Volume
    sprintf_s(_buffer, 50, "%.2f", GetBGMVolume());
    fprintf(stream, "%s\n", _buffer);

    sprintf_s(_buffer, 50, "%.2f", GetSFXVolume());
    fprintf(stream, "%s\n", _buffer);

    //Score



    //Controls

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