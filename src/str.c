#include "../include/str.h"

char* removeSpaces(const char* str) 
{
    if(str == NULL)
        return NULL;
    
    int nSpace = 0;
    for(int i = 0; i <= strlen(str); i++)
    {
        if(str[i] == ' ')
            nSpace++;
    }

    int sizeRes = strlen(str) - nSpace ;
    char* res = (char*)malloc(sizeRes * sizeof(char));

    int j = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] != ' ')
        {
            res[j] = str[i];
            j++;
        }
    }
    res[sizeRes] = '\0';

    return res;
}

int strToInt(const char* str, int* except) 
{
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] < '0' || str[i] > '9')
        {
            *except = -1;
            return 0;
        }
    }

    *except = 0;
    return atoi(str);
}
