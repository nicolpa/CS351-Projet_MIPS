#include "../include/register.h"

int registers[N_REGISTER];

int PC, HI, HO;

void initRegisters()
{
    for (int i = 0; i < N_REGISTER; i++)
        registers[i] = 0;

    PC = HI = HO = 0;
}

int getRegisterValue(int registerId)
{
    return registers[registerId];
}

int getHO()
{
    return HO;
}

int getHI()
{
    return HI;
}

int getPC()
{
    return PC;
}

void setRegisterValue(int registerId, int value)
{
    registers[registerId] = value;
}

void setHO(int value)
{
    HO = value;
}

void setHI(int value)
{
    HI = value;
}

void setPC(int value)
{
    PC = value;
}

void displayRegisters()
{
    for (int i = 0; i < N_REGISTER; i += 4)
    {
        printf("$%.2d : %d", i, registers[i]);
        for (int j = 1; j < 4; j++)
            printf("\t\t$%.2d : %d", i + j, registers[i + j]);
        printf("\n");
    }

    printf("PC  : %d\t\tHI  : %d\t\tHO  : %d", PC, HI, HO);
}
