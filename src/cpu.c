#include "../include/cpu.h"

void initCPU() 
{
    initMemory();
    initRegisters();
}

int loadFile(char *src) 
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
                int intHex = instructionHex(inst);
                printf("   %.8d   %.8x    { %s }\n", (line - 1) * 4, intHex, inst);
                
                if(getExceptionCode() != OK)
                {
                    setForegroundColor(LIGHT_YELLOW_CODE);
                    printf("Error on line %d : %s\n", line, inst);
                    printException();
                    nbError++;
                    setException(OK);
                }

                store(translateProgramAddress((line - 1) * 4), intHex, inst);
                line++;
            }
        }

        printf("\n*** Done ***\n\n");

        if(nbError != 0)
        {
            setForegroundColor(YELLOW_CODE);
            printf("\n   %.2d Error found\n   Aborting\n\n", nbError);
            resetAttributes();
            setException(LOADING_ERROR);
        }
        fclose(fIn);
        return line - 1;
    }
    else
    {
        setException(LOADING_ERROR);
        printException();
        printf("Aborting\n");
        return -1;
    }
}

void run(char* flag, char* src) 
{
    initCPU();
    setException(OK);
    int programLength = -1;

    if(src != NULL)
        programLength = loadFile(src);

    if(getExceptionCode() == OK)
    {
        printf("*** Starting program execution ***\n\n");
        while ((getPC() < programLength * 4 || programLength == -1) && getExceptionCode() == OK)
        {
            int toExec;
            if(flag != NULL && strcmp(flag, "-int") == 0 && readFromTerminal() == 1)
                break;

            toExec = load(translateProgramAddress(getPC()));
            char *sInst = getInstructionStr(translateProgramAddress(getPC()));
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
                fetchOpcode(toExec & 0x3F, 1).exec(toExec);
            else
                fetchOpcode((toExec & 0xFC000000) >> 0x1A, 0).exec(toExec);
            
            setPC(getPC() + 4);
        }
    }
    
    if(getPC() != 0)    // Don't display anything if the program failed to load or no instruction where execute in interactive mode
    {
        printf("\n*** Done ***\n\n");
        displayRegisters();
        displayMemory(translateProgramAddress((programLength == -1) ? getPC() : programLength * 4));

        if(getExceptionCode() != OK)
        {
            printException();
            printf("Aborting\n");
        }
    }

    clearMemory();
}

int readFromTerminal() 
{
    char inst[255];
    int toExec;
    setException(-1);
    do
    {
        printf("> ");
        fgets(inst, 255, stdin);
        inst[strlen(inst) - 1] = '\0';
        formatString(inst);
        if(strlen(inst) != 0 && strcmp(inst, "exit") != 0)
        {
            toExec = instructionHex(inst);
            if(getExceptionCode() != OK)
                printException();
        }

    } while (!((getExceptionCode() == OK || strcmp(inst, "exit") == 0) && strlen(inst) != 0));

    if(strcmp(inst, "exit") == 0)
        return 1;

    store(translateProgramAddress(getPC()), toExec, inst);
    return 0;
}