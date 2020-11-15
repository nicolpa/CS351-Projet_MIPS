#include "../include/register.h"

int32_t registers[N_REGISTER];

int32_t PC, HI, HO;

void initRegisters() 
{
    for(int i = 0; i < N_REGISTER; i++)
        registers[i] = 0;

    PC = HI = HO = 0;
}

int32_t getRegisterValue(int registerId) 
{
    return registers[registerId];
}

int32_t getHO() 
{
    return HO;
}

int32_t getHI() 
{
    return HI;
}

int32_t getPC() 
{
    return PC;
}

void setRegisterValue(int registerId, int32_t value) 
{
    registers[registerId] = value;
}

void setHO(int32_t value) 
{
    HO = value;
}

void setHI(int32_t value) 
{
    HI = value;
}

void setPC(int32_t value) 
{
    PC = value;
}

void displayRegisters() 
{
    for(int i = 0; i < N_REGISTER; i += 4)
    {
        printf("$%.2d : %d", i, registers[i]);
        for(int j = 1; j < 4; j++)
            printf("\t\t$%.2d : %d", i + j, registers[i + j]);
        printf("\n");
    }

    printf("PC  : %d\t\tHI  : %d\t\tHO  : %d", PC, HI, HO);
}
