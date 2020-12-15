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

char *removeSpaces(char *str)
{
    if (str == NULL)
        return NULL;


    int i = 0;
    int firtSpace = 1;
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

char** split(char *str, int *size)
{
    int i = 0;
    *size = 0;
    while (str[i] != '\0')
    {
        if(str[i] == ',')
        {
            (*size)++;
        }
        i++;
    }

    if(*size == 0)
        return NULL;

    char * ptr = strtok(str," ,");
    while (ptr != NULL)
    {
        printf ("%s\n", ptr);
        ptr = strtok(NULL, " ,");
    }

    // char res[*size][255];
    // strcpy(res[0], strtok(str, ","));
    // for(int i = 1; i < *size; i++)
    // {
    //     strcpy(res[0], strtok(NULL, ","));
    // }

    // for(int i = 0; i < *size; i++)
    // {
    //     printf("%s\n", res[i]);
    // }
}