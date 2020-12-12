#include "../include/str.h"

char *trim(char *str) 
{
    while (isspace((unsigned char) *str)) str++;
    if (*str) 
    {
        char *p = str;
        while (*p) p++;
        while (isspace((unsigned char) *(--p)));
        p[1] = '\0';
    }

    return str;
}

char *removeSpaces(char *str)
{
    if (str == NULL)
        return NULL;


    int i = 0;
    while (str[i] != '\0')
    {
        if(isspace(str[i]))
        {
            int j = i;
            while (str[j] != '\0')
            {
                str[j] = str[j + 1];
                j++;
            }
        }

        if(!isspace(str[i]))
            i++;
    }
    
    return str;
}

int strToInt(const char *str, int *except)
{
    int size = strlen(str);
    if(size == 0)
        return 0;
    
    int res = 0;
    for(int i = (str[0] == '-') ? 1 : 0; i < size ; i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            *except = -1;
            return 0;
        }
        
        res = res * 10 + str[i] - '0';
    }

    return (str[0] == '-') ? -res : res;
}

void removeComment(char *str) 
{
    int i = 0;

    while (str[i] != '#' && str[i] != '\0')
        i++;
    
    str[i] = '\0';
}

int isAlphaNum(char c) 
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}