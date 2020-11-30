#include <stdio.h>
#include <stdlib.h>
#include "ScreenManager.h"

char fileName[] = "././savedata.txt";

typedef struct Data
{
    char* dataStr;

}Data;

Data gameData[2];


void LoadData(FILE* stream)
{

}

void LoadGame()
{
    FILE* fp;

    fopen_s(&fp, fileName, "rt");

    if (fp) 
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