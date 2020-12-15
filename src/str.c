#include "../include/str.h"

char *trim(char *str) 
{
    int i = 0;
    while (isspace((unsigned char) str[i]))
    {
        int j = i;
        while (str[j] != '\0')
        {
            str[j] = str[j + 1];
            j++;
        }
        i++;
    }
    if (*str) 
    {
        char *p = str;
        while (*p) p++;
        while (isspace((unsigned char) *(--p)));
        p[1] = '\0';
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

void formatString(char *str)
{
    str = trim(str);
    removeComment(str);

    if(strlen(str) == 0)
        return;
    
    char tmp[50] = "";
    char * ptr = strtok(str," ,\t");
    int i = 0;
    strcat(tmp, ptr);
    while (ptr != NULL)
    {
        ptr = strtok(NULL, " ,\t");
        if(ptr != NULL)
        {
            if(i != 0)
            {
                strcat(tmp, ",");
            }
            strcat(tmp, " ");
            strcat(tmp, ptr);
            i++;
        }
    }
    strcpy(str, tmp);
}