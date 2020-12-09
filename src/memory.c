#include "../include/memory.h"

List mem;

void initMemory()
{
    mem = NULL;
}

int load(unsigned int address, int *except) 
{
    if(address > LAST_ADDRESS)
    {
        *except = INVALID_ADDRESS;
        return 0;
    }

    return fetch(&mem, address);
}

void store(unsigned int address, int value, int *except) 
{
    if(address < 0 || address > LAST_ADDRESS)
        *except = INVALID_ADDRESS;
    else
        insert(&mem, value, address);
}

void displayMemory(unsigned int lastAddress) 
{
    printf("*** Memory state ***\n\n");
    print(&mem, lastAddress);
}

void clearMemory()
{
    clear(&mem);
}

int translateProgramAddress(unsigned int address) 
{
    return LAST_ADDRESS - address;
}