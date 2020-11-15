#include <stdio.h>
#include "../include/instructions.h"
#include "../include/register.h"
#include "../include/memory.h"
#include "../include/linkedList.h"

int main(int argc, char *args[])
{
    printf("//========== MIPS Emulator ==========\\\\\n\n");
    if (argc == 1)
    {
        perror("Missing argument : input file required\n");
        return -1;
    }
    if (argc > 3)
    {
        perror("Too many arguments\n");
        return -1;
    }
    if (argc != 3)
    {
        perror("Missing argument : output file required\n");
        return -1;
    }

    assemblyToHex(args[1], args[2]);
    initMemory();
    initRegisters();
    displayRegisters();
    printf("\n\n");
    displayMemory();
    printf("=== Done ===\n");
    return 0;
}
