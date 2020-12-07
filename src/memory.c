#include "../include/memory.h"

List mem;

void initMemory()
{
    mem = NULL;
}

int load(int address, int *except) 
{
    return fetch(&mem, address);
}

void store(int address, int value, int *excepte) 
{
    insert(&mem, value, address);
}

void displayMemory() 
{
    printf("*** Memory state ***\n\n");
    print(&mem);
}

void clearMemory()
{
    clear(&mem);
}