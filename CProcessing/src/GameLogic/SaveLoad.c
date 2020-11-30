#include <stdio.h>
#include <stdlib.h>
#include "ScreenManager.h"

char fileName[] = "././savedata.txt";

typedef struct Data
{
    char dataStr[255];

}Data;

Data gameData[4];//Maybe use malloc for this


void LoadData(FILE* stream)
{
    int i = 0;
    while (!feof(stream))
    {
        char buffer[255];

        fgets(buffer, 255, stream);
        strcpy_s((gameData + i)->dataStr, 255, buffer);
        i++;
    }


    //Volume
    SetBGMVolume((float)atof(gameData[0].dataStr));
    printf("Volume is set to %f, from %s\n", GetBGMVolume(), gameData[0].dataStr);
  
    SetSFXVolume((float)atof(gameData[1].dataStr));
    printf("Volume is set to %f, from %s\n", GetSFXVolume(), gameData[1].dataStr);



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