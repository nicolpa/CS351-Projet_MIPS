#include <string.h>
#include "../include/ANSIColor.h"

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

//exception
#define UNKWNOW        -1
#define OK              0
#define UNKOWN_OP       1
#define OVERFLOW        2
#define SYNTAX_ERROR    3
#define REG_EXPECTED    4
#define IMM_EXPECTED    5
#define UNDEFINED_REG   6
#define INVALID_ADDRESS 7
#define LOADING_ERROR   8

typedef struct
{
    int nCode;
    char *sCode;
    char *sMetaData;
} exception;


// exception fetchException(int nCode);

void setException(int nCode);

void printException();

int getExceptionCode();

void setExceptionMetaData(const char *metaData);

// /**
//  * Get a string representtion of an error code
//  * @param nExcept The exception code
//  * @param cExcept The corresponding message
//  */
// void exceptionToString(int *nExcept, char *cExcept);

#endif