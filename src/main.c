#include <stdio.h>
#include "../include/instructions.h"

int main(int argc, char* args[])
{
    printf("//========== MIPS Emulator ==========\\\\\n\n");
    if(argc == 1)
    {
        perror("Missing argument : input file required\n");
        return -1;
    }
    if(argc > 3)
    {
        perror("Too many arguments\n");
        return -1;
    }
    if(argc != 3)
    {
        perror("Missing argument : out file required\n");
    }

    assemblyToHex(args[1], args[2]);
    printf("=== Done ===\n");
    return 0;
}
