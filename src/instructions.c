#include "../include/instructions.h"

void assemblyToHex(const char* src, const char* dst) 
{
    FILE *fIn = fopen(src, "r");
    if(fIn == NULL)
    {
        perror("Unable to open file : No such file or directory");
    }
    else
    {
        FILE* fOut = fopen(dst, "w");;
        if (fOut == NULL)
        {
            perror("Unable to open file : No such file or directory");
        }
        else
        {
            char inst[255];
            int line = 1;
            while (fgets(inst, 255, fIn))
            {
                if(strlen(inst) > 1 && inst[0] != '#')
                {
                    if(inst[strlen(inst) - 1] == '\n')
                        inst[strlen(inst) - 1] = '\0';
                    char *tmp = strchr(inst, '#');
                    if(tmp != NULL)
                        *tmp = '\0';
                    
                    int except = OK;
                    int intHex = instructionHex(inst, &except);
                    switch (except)
                    {
                    case OK:
                        fprintf(fOut, "%.8x\t{ %s }\n", intHex, inst);
                        break;
                    
                    default:
                        fprintf(fOut, "Error found at line %d\n", line);
                        fprintf(fOut, "%.8x\t{ %s }\n", 0, inst);
                        break;
                    }
                    line++;
                }
            }
            fclose(fIn);
            fclose(fOut);
        }
    }
}

int instructionHex(const char* inst, int *except) 
{
    char *op = getOpcode(inst);
    int res = 0;
    *except = 0;
    if(strcmp(op, "ADD") == 0)
    {
        res += (getOperande(inst, 1, 1, except) << 21) + (getOperande(inst, 2, 1, except) << 16) + (getOperande(inst, 0, 1, except) << 11) + ADD;
    }
    else if(strcmp(op, "ADDI") == 0)
    {
        res += (ADDI << 26) + (getOperande(inst, 1, 1, except) << 21) + (getOperande(inst, 0, 1, except) << 16) + getOperande(inst, 2, 0, except);
    }
    else if(strcmp(op, "AND") == 0)
    {
        res += (getOperande(inst, 1, 1, except) << 21) + (getOperande(inst, 2, 1, except) << 16) + (getOperande(inst, 0, 1, except) << 11) + AND;
    }
    else if(strcmp(op, "BEQ") == 0)
    {
        res += (BEQ << 26) + (getOperande(inst, 0, 1, except) << 21) + (getOperande(inst, 1, 1, except) << 16) + getOperande(inst, 2, 0, except);
    }
    else if(strcmp(op, "BGTZ") == 0)
    {
        res += (BGTZ << 26) + (getOperande(inst, 0, 1, except) << 21) + getOperande(inst, 1, 0, except);
    }
    else if(strcmp(op, "BLEZ") == 0)
    {
         res += (BLEZ << 26) + (getOperande(inst, 0, 1, except) << 21) + getOperande(inst, 1, 0, except);
    }
    else if(strcmp(op, "BNE") == 0)
    {
         res += (BNE << 26) + (getOperande(inst, 0, 1, except) << 21) + (getOperande(inst, 1, 1, except) << 16) + getOperande(inst, 2, 0, except);
    }
    else if(strcmp(op, "DIV") == 0)
    {
        res += (getOperande(inst, 0, 1, except) << 21) + (getOperande(inst, 1, 1, except) << 16) + DIV;
    }
    else if(strcmp(op, "J") == 0)
    {
        res += (J << 26) + getOperande(inst, 0, 0, except);
    }
    else if(strcmp(op, "JAL") == 0)
    {
        res += (JAL << 26) + getOperande(inst, 0, 0, except);
    }
    else if(strcmp(op, "JR") == 0)
    {
        int hint = 0; // ??
        res += (getOperande(inst, 0, 1, except) << 21) + (hint << 6) + JR;
    }
    else if(strcmp(op, "LUI") == 0)
    {
        res += (LUI << 26) + (getOperande(inst, 1, 0, except) << 16) + getOperande(inst, 1, 0, except);
    }
    else if(strcmp(op, "LW") == 0)
    {
        res += (LW << 26) + (getBase(inst, except) << 21) + (getOperande(inst, 0, 1, except) << 16) + getOffset(inst, except);
    }
    else if(strcmp(op, "MFHI") == 0)
    {
        res += (getOperande(inst, 0, 1, except) << 11) + MFHI;
    }
    else if(strcmp(op, "MFLO") == 0)
    {
        res += (getOperande(inst, 0, 1, except) << 11) + MFLO;
    }
    else if(strcmp(op, "MULT") == 0)
    {
        res += (getOperande(inst, 0, 1, except) << 21) + (getOperande(inst, 1, 1, except) << 16) + MULT;
    }
    else if(strcmp(op, "NOP") == 0)
    {
        res = 0;
    }
    else if(strcmp(op, "OR") == 0)
    {
        res += (getOperande(inst, 1, 1, except) << 21) + (getOperande(inst, 2, 1, except) << 16) + (getOperande(inst, 0, 1, except) < 11) + OR;
    }
    else if(strcmp(op, "ROTR") == 0)
    {
        res += (getOperande(inst, 1, 1, except) << 16) + (getOperande(inst, 0, 1, except) << 11) + (getOperande(inst, 2, 0, except) << 6) + ROTR;
    }
    else if(strcmp(op, "SLL") == 0)
    {
        res += (getOperande(inst, 1, 1, except) << 16) + (getOperande(inst, 0, 1, except) << 11) + (getOperande(inst, 2, 0, except) << 6) + SLL;
    }
    else if(strcmp(op, "SLT") == 0)
    {
        res += (getOperande(inst, 1, 1, except) << 21) + (getOperande(inst, 2, 1, except) << 16) + (getOperande(inst, 0, 1, except) << 11) + SLT;
    }
    else if(strcmp(op, "SRL") == 0)
    {
        res += (getOperande(inst, 1, 1, except) << 16) + (getOperande(inst, 0, 1, except) << 11) + (getOperande(inst, 2, 0, except) << 6) + SRL;
    }
    else if(strcmp(op, "SUB") == 0)
    {
        res += (getOperande(inst, 1, 1, except) << 21) + (getOperande(inst, 2, 1, except) << 16) + (getOperande(inst, 0, 1, except) << 11) + SUB;
    }
    else if(strcmp(op, "SW") == 0)
    {
        res += (SW << 26) + (getBase(inst, except) << 21) + (getOperande(inst, 0, 1, except) << 16) + getOffset(inst, except);
    }
    else if(strcmp(op, "SYSCALL") == 0)
    {
        int code = 0; // ??
        res += (code << 6) + SYSCALL;
    }
    else if(strcmp(op, "XOR") == 0)
    {
        res += (getOperande(inst, 1, 1, except) << 21) + (getOperande(inst, 2, 1, except) << 16) + (getOperande(inst, 0, 1, except) << 6) + XOR;
    }
    else
    {
        *except = UNKOWN_OP;
    }
    
    free(op);
    return res;
}

char* getOpcode(const char* inst) 
{
    int i = 0;
    
    while (inst[i] != ' ' && inst[i] != '\0')
        i++;

    char* op = (char *)malloc(i * sizeof(char));
    for(int j = 0; j < i; j++)
        op[j] = inst[j];
    op[i] = '\0';

    return op; 
}

int getOperande(const char* inst, int placement, int reg, int* except) 
{
    if(*except != OK)
        return 0;

    char* op = strchr(inst, ' ') + 1;
    if(placement == 1)
        op = strchr(op, ',') + 1;
    else if(placement == 2)
        op = strchr(strchr(op, ',' ) + 1, ',') + 1;
    
    while (*op == ' ')
        op +=1;
    
    if(reg && op[0] != '$')
    {
        *except = REG_EXPECTED;
        return 0;
    }
    if(!reg && op[0] == '$')
    {
        *except = IMM_EXPECTED;
        return 0;
    }

    int i = 0;
    if(reg) op = op + 1;

    while (op[i] != ',' && op[i] != '\0')
        i++;
    
    char res[i + 1];
    for(int j = 0; j < i; j++)
        res[j] = op[j];
    res[i] = '\0';

    return atoi(res);
}

int getBase(const char* inst, int* except) 
{
    char* base = strchr(inst, '(') + 1;
    if(base[0] != '$')
    {
        *except = REG_EXPECTED;
        return 0;
    }
    int i = 0;
    base += 1;
    while(base[i] != ')' && base[i] != '\0')
        i++;
    
    if(base[i] == '\0')
    {
        *except = SYNTAX_ERROR;
        return 0;
    }

    char res[i + 1];
    for(int j = 0; j < i; j++)
        res[j] = base[j];
    res[i] = '\0';
    return atoi(res);

}

int getOffset(const char* inst, int* except) 
{
    char* offset = strchr(inst, ',') + 2;
    if(offset[0] == '$')
    {
        *except = IMM_EXPECTED;
        return 0;
    }
    int i = 0;
    while(offset[i] != '(' && offset[i] != '\0')
        i++;
    
    if(offset[i] == '\0')
    {
        *except = SYNTAX_ERROR;
        return 0;
    }

    char res[i + 1];
    for(int j = 0; j < i; j++)
        res[j] = offset[j];
    res[i] = '\0';
    return atoi(res);
}