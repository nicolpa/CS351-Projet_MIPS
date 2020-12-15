#include "../include/exceptions.h"

const exception exceptions[] =
{
    { OK                , NULL                                              , NULL},
    { UNKOWN_OP         , "Unknown operande"                                , NULL},
    { OVERFLOW          , "Overflow"                                        , NULL},
    { SYNTAX_ERROR      ,  "Syntax error"                                   , NULL},
    { REG_EXPECTED      , "Expected register"                               , NULL},
    { IMM_EXPECTED      , "Expected immediate value"                        , NULL},
    { UNDEFINED_REG     , "Undefined register"                              , NULL},
    { INVALID_ADDRESS   , "Invalid address"                                 , NULL},
    { LOADING_ERROR     , "Unable to open file : No such file or directory" , NULL},
    { UNKWNOW           , "Unknown error"                                   , NULL}
};

exception currentException;

void setException(int nCode) 
{
    for(int i = 0; i < 9; i++)
    {
        if(exceptions[i].nCode == nCode)
        {
            currentException = exceptions[i];
            return;
        }
    }

    currentException = exceptions[9];
}

void setExceptionMetaData(const char *metaData)
{
    if(metaData == NULL && currentException.sMetaData != NULL)
        free(currentException.sMetaData);
    else if(metaData != NULL && currentException.sMetaData != NULL)
    {
        currentException.sMetaData = (char *) realloc(currentException.sMetaData, sizeof(char) * strlen(metaData));
        strcpy(currentException.sMetaData, metaData);
    }
    else
    {
        currentException.sMetaData = (char *) malloc(sizeof(char) * strlen(metaData));
        strcpy(currentException.sMetaData, metaData);
    }
}

void printException() 
{
    setForegroundColor(YELLOW_CODE);
    printf("%s", currentException.sCode);
    if(currentException.sMetaData != NULL)
        printf(" : %s", currentException.sMetaData);
    printf("\n");
    resetAttributes();
}

int getExceptionCode() 
{
    return currentException.nCode;   
}
