#include "../include/memory.h"

List mem;

void initMemory()
{
    mem = NULL;
}

int load(int address) 
{
    return fetch(&mem, address * 4);
}

void store(int address, int32_t value) 
{
    if(value == 0)
        delete(&mem, address * 4);
    else
        insert(&mem, value, address * 4);
}

void displayMemory() 
{
    printf("===== Memory =====\n");
    print(&mem);
}

void clearMemory()
{
    clear(&mem);
}