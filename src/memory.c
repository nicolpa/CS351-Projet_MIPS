#include "../include/memory.h"

List mem;

void initMemory()
{
    mem = NULL;
}

int load(unsigned int address) 
{
    if(address > LAST_ADDRESS || ((address) & 0x3) != 0)
    {
        // *except = fetchException(INVALID_ADDRESS);
        setException(INVALID_ADDRESS);
        
        printf("%u\n", address);
        return 0;
    }

    return fetch(&mem, address)->value;
}

void store(unsigned int address, int value, char* sInstruction) 
{
    if(address > LAST_ADDRESS || ((address) & 0x3) != 0)
    {
        // *except = fetchException(INVALID_ADDRESS);
        setException(INVALID_ADDRESS);
        printf("%u\n", address);
    }
    else
        insert(&mem, value, address, sInstruction);
}

void displayMemory(unsigned int lastAddress) 
{
    printf("*** Memory state ***\n\n");
    print(&mem, lastAddress);
}

char* getInstructionStr(unsigned int address) 
{
    if(address > LAST_ADDRESS || ((address) & 0x3) != 0)
    {
        // *except = fetchException(INVALID_ADDRESS);
        setException(INVALID_ADDRESS);
        printf("%u\n", address);
        return NULL;
    }
    else
        return fetch(&mem, address)->sInstruction;
}

void clearMemory()
{
    clear(&mem);
}

int translateProgramAddress(unsigned int address) 
{
    return LAST_ADDRESS - address;
}