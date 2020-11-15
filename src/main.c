#include <stdio.h>
#include "../include/instructions.h"
#include "../include/register.h"
#include "../include/memory.h"
#include "../include/linkedList.h"

int main(int argc, char* args[])
{
    List l = NULL;
    int n = 100000;
    printf("Allocating memory...\n");
    for(int i = 0; i < n; i++)
    {
        // printf("\r%.8d", n - i);
        insert(&l, i, i << 2);
    }
    printf("Done\n");
   /*  insert(&l, 1, 0);
    insert(&l, 2, 4);
    insert(&l, 3, 8);
    insert(&l, 4, 12);
    insert(&l, 5, 16);
    insert(&l, 6, 20);
    insert(&l, 0, 24);
    print(&l);
    delete(&l, 0);
    print(&l);
    delete(&l, 20);
    print(&l);
    delete(&l, 8);
    print(&l);
    insert(&l, 78, 12); */
    char u;
    print(&l);
    scanf("%c", &u);
    printf("?");
    clear(&l);
    scanf("%c", &u);
    printf("!");
    print(&l);
    // printf("//========== MIPS Emulator ==========\\\\\n\n");
    // if(argc == 1)
    // {
    //     perror("Missing argument : input file required\n");
    //     return -1;
    // }
    // if(argc > 3)
    // {
    //     perror("Too many arguments\n");
    //     return -1;
    // }
    // if(argc != 3)
    // {
    //     perror("Missing argument : output file required\n");
    //     return -1;
    // }

    // // assemblyToHex(args[1], args[2]);
    // initMemory();
    // initRegisters();
    // displayRegisters();
    // printf("\n\n");
    // displayMemory();
    // printf("=== Done ===\n");
    return 0;
}
