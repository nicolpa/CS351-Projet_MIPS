#include "../include/cpu.h"

void initCPU() 
{
    initMemory();
    initRegisters();
}

int loadFile(char *src, exception *except) 
{
    printf("*** Loading program ***\n\n");
    FILE *fIn = fopen(src, "r");
    if(fIn != NULL)
    {
        char inst[255];
        int nbError = 0;
        int line = 1;
        while (fgets(inst, 255, fIn))
        {
            if(inst[strlen(inst) - 1] == '\n')
                inst[strlen(inst) - 1] = '\0';
            formatString(inst);
            if(strlen(inst) > 1)
            {
            // printf("|%s|\n", inst);
                
                int intHex = instructionHex(inst, except);
                
                if(except->nCode != OK)
                {
                    printf("Error on line %d : %s\n", line, inst);
                    nbError++;
                    *except = fetchException(OK);
                }

                printf("   %.8d   %.8x    { %s }\n", (line - 1) * 4, intHex, inst);

                store(translateProgramAddress((line - 1) * 4), intHex, inst, except);
                line++;
            }
        }

        if(nbError == 0)
        {
            printf("\n*** Done ***\n\n");

        }
        else
        {
            printf("\n   %.2d Error found\n   Aborting\n\n", nbError);
            *except = fetchException(LOADING_ERROR);
        }
        fclose(fIn);
        return line - 1;
    }
    else
    {
        *except = fetchException(LOADING_ERROR);
        printf("   %s\n", except->sCode);
        printf("Aborting\n");
        return -1;
    }
    
}

void run(char* flag, char* src) 
{
    initCPU();
    exception except = fetchException(OK);
    int programLength = -1;

    if(src != NULL)
        programLength = loadFile(src, &except);

    if(except.nCode == OK)
    {
        printf("*** Starting program execution ***\n\n");
        while ((getPC() < programLength * 4 || programLength == -1) && except.nCode == OK)
        {
            int toExec;
            if(flag != NULL && strcmp(flag, "-int") == 0 && readFromTerminal() == 1)
                break;

            toExec = load(translateProgramAddress(getPC()), &except);
            char *sInst = getInstructionStr(translateProgramAddress(getPC()), &except);
            printf("   %.8d   %.8x   { %s }\n", getPC(), toExec, sInst);

            if(flag != NULL)
            {
                char option;
                do
                {
                    printf("display registers [r]; memory [m]; continue [c]\n");
                    scanf("%c", &option);
                    getchar();  //remove newline garbage in buffer
                    switch (option)
                    {
                    case 'r':
                        displayRegisters();
                        break;
                    case 'm':
                        displayMemory(translateProgramAddress((programLength == -1) ? getPC() : programLength * 4));
                        break;
                    }
                } while (option != 'c');
            }

            if((toExec & 0xFC000000) == 0)
                fetchOpcode(toExec & 0x3F, 1, &except).exec(toExec, &except);
            else
                fetchOpcode((toExec & 0xFC000000) >> 0x1A, 0, &except).exec(toExec, &except);
            
            setPC(getPC() + 4);
        }
    }
    
    if(getPC() != 0)
    {
        printf("\n*** Done ***\n\n");
        displayRegisters();
        displayMemory(translateProgramAddress((programLength == -1) ? getPC() : programLength * 4));

        if(except.nCode != OK)
        {
            printf("Error : %s\n", except.sCode);
            if(except.sMetaData != NULL)
            {
                printf("%s\n", except.sMetaData);
            }
            printf("Aborting\n");
        }
    }

    clearMemory();
}

int readFromTerminal() 
{
    char inst[255];
    int toExec;
    exception except = fetchException(-1);
    do
    {
        printf("> ");
        fgets(inst, 255, stdin);
        inst[strlen(inst) - 1] = '\0';
        formatString(inst);
        if(strlen(inst) != 0 && strcmp(inst, "exit") != 0)
        {
            toExec = instructionHex(inst, &except);
            if(except.nCode != OK)
            {
                printf("Error : %s\n", except.sCode);
            }
        }

    } while (!((except.nCode == OK || strcmp(inst, "exit") == 0) && strlen(inst) != 0));

    if(strcmp(inst, "exit") == 0)
        return 1;

    store(translateProgramAddress(getPC()), toExec, inst, &except);
    return 0;
}