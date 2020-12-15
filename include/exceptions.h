#include <string.h>
#include "../include/ANSIColor.h"

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

// Exceptions

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
    int nCode;          // The code of the exception
    char *sCode;        // The string representation of the exception
    char *sMetaData;    // Optional metadata for the exception
} exception;

/**
 * The current exception state
 */
void setException(int nCode);

/**
 * Print the exception into  readable format with its metadata when available
 */
void printException();

/**
 * Get the exception code from the current exception
 */
int getExceptionCode();

/**
 * Set the metadata for the current exception
 * @param metaDate The metadata of the exception
 */
void setExceptionMetaData(const char *metaData);

#endif