#include <stdio.h>
#include "../include/instructions.h"
#include "../include/register.h"
#include "../include/memory.h"
#include "../include/cpu.h"
#include "../include/exceptions.h"
int main(int argc, char *args[])
{
    printf("//========== MIPS Emulator ==========\\\\\n\n");

    if (argc == 1)
        perror("Missing argument\n");
    else if (argc > 3)
        perror("Too many arguments\n");
    else
    {
        if(strcmp(args[1], "-pas") == 0)
        {
            perror("Input file required\n");
            return 1;
        }
        else if(strcmp(args[1], "-int") == 0)
        {
            // printf("Interactive mode\n");
            run(args[1], NULL);
        }
        else
        {
            if(argc == 2)
            {
                if(args[1][0] == '-')
                {
                    perror("Invalid flag\n");
                    return -1;
                }
                //exec fichier
                // printf("Normal mode\n");
                run(NULL, args[1]);
                
            }
            else if(argc == 3 && strcmp(args[2], "-pas") == 0)
            {
                // printf("Step by step mode");
                run(args[2], args[1]);
                //exec mode step by step
            }
            else
            {
                perror("Invalid flag");
                return -1;
            }
            
        }

        return 0;   
    }

    return -1;
}
