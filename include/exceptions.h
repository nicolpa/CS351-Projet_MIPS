#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

//exception
#define OK              0
#define UNKOWN_OP       1
#define OVERFLOW        2
#define SYNTAX_ERROR    3
#define REG_EXPECTED    4
#define IMM_EXPECTED    5
#define UNDEFINED_REG   6
#define INVALID_ADDRESS 7

void exceptionToString(int nExcept, char *cExcept);

#endif