#include "../include/exceptions.h"

void exceptionToString(int *nExcept, char *cExcept) 
{
    switch (*nExcept)
    {
    case UNKOWN_OP:
        strcpy(cExcept, "Unknown operande");
        break;
    case OVERFLOW:
        strcpy(cExcept, "Overflock");
        break;
    case SYNTAX_ERROR:
        strcpy(cExcept, "Syntax error");
        break;
    case REG_EXPECTED:
        strcpy(cExcept, "Expected register");
        break;
    case IMM_EXPECTED:
        strcpy(cExcept, "Expected immediate value");
        break;
    case UNDEFINED_REG:
        strcpy(cExcept, "Undefined register");;
        break;
    case INVALID_ADDRESS:
        strcpy(cExcept, "Invalid address");
        break;
    case LOADING_ERROR:
        strcpy(cExcept, "Unable to open file : No such file or directory");
    break;
    default:
        strcpy(cExcept, "Unknown error");
        break;
    }
}
