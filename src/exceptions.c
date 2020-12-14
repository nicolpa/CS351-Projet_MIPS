#include "../include/exceptions.h"

const exception exceptions[] =
{
    {OK},
    {UNKOWN_OP, "Unknown operande"},
    {OVERFLOW, "Overflow"},
    {SYNTAX_ERROR, "Syntax error"},
    {REG_EXPECTED, "Expected register"},
    {IMM_EXPECTED, "Expected immediate value"},
    {UNDEFINED_REG, "Undefined register"},
    {INVALID_ADDRESS, "Invalid address"},
    {LOADING_ERROR, "Unable to open file : No such file or directory"},
    {UNKWNOW, "Unknown error"}
};

exception fetchException(int nCode) 
{
    for(int i = 0; i < 9; i++)
    {
        if(exceptions[i].nCode == nCode)
            return exceptions[i];
    }

    return exceptions[9];
}
