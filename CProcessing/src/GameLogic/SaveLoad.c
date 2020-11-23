#include <stdio.h>
#include <stdlib.h>

char fileName[] = "/userdata/savedata.txt";

char* data;

void ReadSaveFile()
{
    FILE* fp;

    fopen_s(&fp, fileName, "rt");

    if (fp) 
    {
        fclose(fp);
    }      
    
}

void WriteSaveFile()
{
   // FILE  *fp;
    //fclose(fp);
}