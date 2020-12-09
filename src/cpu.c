#include "../include/cpu.h"

void initCPU() 
{
    initMemory();
    initRegisters();
}

int loadFile(char *src, int *except) 
{
    printf("*** Loading program ***\n\n");
    FILE *fIn = fopen(src, "r");
    if(fIn != NULL)
    {
        char inst[255];
        int line = 1;
        while (fgets(inst, 255, fIn))
        {
            removeComment(inst);
            if(strlen(inst) > 1)
            {
                if(inst[strlen(inst) - 1] == '\n')
                    inst[strlen(inst) - 1] = '\0';
                
                int intHex = instructionHex(inst, except);
                
                if(*except != OK)
                {
                    char err[255];
                    exceptionToString(except, err);
                    printf("Error on line %d : %s\n", line, inst);
                    printf("   %s\n", err);
                    printf("Aborting\n");
                    fclose(fIn);
                    return -1;
                }

                printf("   %.8d   %.8x    { %s }\n", (line - 1) * 4, intHex, inst);

                store(translateProgramAddress((line - 1) * 4), intHex, except);
            }
            line++;
        }

        printf("\n*** Done ***\n");
        fclose(fIn);
        return line - 1;
    }
    else
    {
        *except = LOADING_ERROR;
        char err[255];
        exceptionToString(except, err);
        printf("   %s\n", err);
        printf("Aborting\n");
        return -1;
    }
    
}

void run(char* flag, char* src) 
{
    initCPU();
    int except = OK;
    int programLength = -1;

    if(src != NULL)
        programLength = loadFile(src, &except);


    if(except == OK)
    {
        printf("*** Starting program execution ***\n\n");
        while ((getPC() < programLength * 4 || programLength == -1) && except == OK)
        {
            int toExec;

            if(flag != NULL && strcmp(flag, "-int") == 0 && readFromTerminal() == 1)
                break;

            toExec = load(translateProgramAddress(getPC()), &except);
            
            printf("   %.8d   %.8x\n", getPC(), toExec);

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
            {
                switch (toExec & 0x3F)
                {
                case ADD:
                    execADD(toExec, &except);
                    break;
                case AND:
                    execAND(toExec, &except);
                    break;
                case DIV:
                    execDIV(toExec, &except);
                    break;
                case JR:
                    execJR(toExec, &except);
                    break;
                case MFHI:
                    execMHFI(toExec, &except);
                    break;
                case MFLO:
                    execMHLO(toExec, &except);
                    break;
                case MULT:
                    execMULT(toExec, &except);
                    break;
                case NOP:
                    execNOP(toExec, &except);
                    break;
                case OR:
                    execOR(toExec, &except);
                    break;
                case ROTR:
                    execROTR(toExec, &except);
                    break;
                // case SLL:
                //     break;
                case SLT:
                    execSLT(toExec, &except);
                    break;
                // case SRL:
                //     break;
                case SUB:
                    execSUB(toExec, &except);
                    break;
                case SYSCALL:
                    execSYSCALL(toExec, &except);
                    break;
                case XOR:
                    execXOR(toExec, &except);
                    break;
                }
            }
            else
            {
                switch ((toExec & 0xFC000000) >> 0x1A)
                {
                case ADDI:
                    execADDI(toExec, &except);
                    break;
                case BEQ:
                    execBEQ(toExec, &except);
                    break;
                case BGTZ:
                    execBGTZ(toExec, &except);
                    break;
                case BLEZ:
                    execBLEZ(toExec, &except);
                    break;
                case BNE:
                    execBNE(toExec, &except);
                    break;
                case J:
                    execJ(toExec, &except);
                    break;
                case LUI:
                    execLUI(toExec, &except);
                    break;
                case LW:
                    execLW(toExec, &except);
                    break;
                case SW:
                    execSW(toExec, &except);
                    break;
                }
            }
            

            setPC(getPC() + 4);
        }
        
    }
    printf("\n*** Done ***\n\n");
    displayRegisters();
    displayMemory(translateProgramAddress((programLength == -1) ? getPC() : programLength * 4));

    if(except != OK)
    {
        char err[255];
        exceptionToString(&except, err);
        printf("Error : %s\n", err);
        printf("Aborting\n");
    }

    clearMemory();
}

int readFromTerminal() 
{
    char inst[255];
    int toExec;
    int except = -1;
    do
    {
        printf("> ");
        fgets(inst, 255, stdin);
        inst[strlen(inst) - 1] = '\0';
        removeComment(inst);
        if(strlen(inst) != 0 && strcmp(inst, "exit") != 0)
        {
            toExec = instructionHex(inst, &except);
            if(except != OK)
            {
                char msg[255];
                exceptionToString(&except, msg);
                printf("Error : %s\n", msg);
            }
        }

    } while (!((except == OK || strcmp(inst, "exit") == 0) && strlen(inst) != 0));

    if(strcmp(inst, "exit") == 0)
        return 1;

    store(translateProgramAddress(getPC()), toExec, &except);
    return 0;
}

