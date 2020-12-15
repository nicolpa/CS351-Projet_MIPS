#include "../include/register.h"

int registers[N_REGISTER];

int PC, HI, LO;

void initRegisters()
{
    for (int i = 0; i < N_REGISTER; i++)
        registers[i] = 0;

    PC = HI = LO = 0;
}

int getRegisterValue(int registerId)
{
    return registers[registerId];
}

int getLO()
{
    return LO;
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

void setLO(int value)
{
    LO = value;
}

void setHI(int value)
{
    HI = value;
}

void setPC(int value)
{
    PC = value;
    // printf("PC set = %d\n", getPC());
}

void displayRegisters()
{
    printf("*** Register states ***\n\n");
    for (int i = 0; i < N_REGISTER; i += 4)
    {
        printf("   $%.2d: %.2d", i, registers[i]);
        for (int j = 1; j < 4; j++)
            printf("\t\t $%.2d: %.2d", i + j, registers[i + j]);
        printf("\n");
    }

    printf("   HI : %d\n   LO : %d\n\n", HI, LO);
}
