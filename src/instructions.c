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

int instructionHex(char* inst, int *except) 
{
    char *op = getOpcode(inst);
    if(strcmp(op, "NOP") == 0)
    {
        free(op);
        return 0;
    }
    char *ope = removeSpaces(strchr(inst, ' '));
    int res = 0;
    *except = 0;
    if(strcmp(op, "ADD") == 0)
    {
        res += (getOperande(ope, 1, 1, except) << 21) + (getOperande(ope, 2, 1, except) << 16) + (getOperande(ope, 0, 1, except) << 11) + ADD;
    }
    else if(strcmp(op, "ADDI") == 0)
    {
        res += (ADDI << 26) + (getOperande(ope, 1, 1, except) << 21) + (getOperande(ope, 0, 1, except) << 16) + getOperande(ope, 2, 0, except);
    }
    else if(strcmp(op, "AND") == 0)
    {
        res += (getOperande(ope, 1, 1, except) << 21) + (getOperande(ope, 2, 1, except) << 16) + (getOperande(ope, 0, 1, except) << 11) + AND;
    }
    else if(strcmp(op, "BEQ") == 0)
    {
        res += (BEQ << 26) + (getOperande(ope, 0, 1, except) << 21) + (getOperande(ope, 1, 1, except) << 16) + getOperande(ope, 2, 0, except);
    }
    else if(strcmp(op, "BGTZ") == 0)
    {
        res += (BGTZ << 26) + (getOperande(ope, 0, 1, except) << 21) + getOperande(ope, 1, 0, except);
    }
    else if(strcmp(op, "BLEZ") == 0)
    {
         res += (BLEZ << 26) + (getOperande(ope, 0, 1, except) << 21) + getOperande(ope, 1, 0, except);
    }
    else if(strcmp(op, "BNE") == 0)
    {
         res += (BNE << 26) + (getOperande(ope, 0, 1, except) << 21) + (getOperande(ope, 1, 1, except) << 16) + getOperande(ope, 2, 0, except);
    }
    else if(strcmp(op, "DIV") == 0)
    {
        res += (getOperande(ope, 0, 1, except) << 21) + (getOperande(ope, 1, 1, except) << 16) + DIV;
    }
    else if(strcmp(op, "J") == 0)
    {
        res += (J << 26) + getOperande(ope, 0, 0, except);
    }
    else if(strcmp(op, "JAL") == 0)
    {
        res += (JAL << 26) + getOperande(ope, 0, 0, except);
    }
    else if(strcmp(op, "JR") == 0)
    {
        int hint = 0; // ??
        res += (getOperande(ope, 0, 1, except) << 21) + (hint << 6) + JR;
    }
    else if(strcmp(op, "LUI") == 0)
    {
        res += (LUI << 26) + (getOperande(ope, 1, 0, except) << 16) + getOperande(ope, 1, 0, except);
    }
    else if(strcmp(op, "LW") == 0)
    {
        res += (LW << 26) + (getBase(ope, except) << 21) + (getOperande(ope, 0, 1, except) << 16) + getOffset(ope, except);
    }
    else if(strcmp(op, "MFHI") == 0)
    {
        res += (getOperande(ope, 0, 1, except) << 11) + MFHI;
    }
    else if(strcmp(op, "MFLO") == 0)
    {
        res += (getOperande(ope, 0, 1, except) << 11) + MFLO;
    }
    else if(strcmp(op, "MULT") == 0)
    {
        res += (getOperande(ope, 0, 1, except) << 21) + (getOperande(ope, 1, 1, except) << 16) + MULT;
    }
    else if(strcmp(op, "OR") == 0)
    {
        res += (getOperande(ope, 1, 1, except) << 21) + (getOperande(ope, 2, 1, except) << 16) + (getOperande(ope, 0, 1, except) < 11) + OR;
    }
    else if(strcmp(op, "ROTR") == 0)
    {
        res +=(1 << 21) + (getOperande(ope, 1, 1, except) << 16) + (getOperande(ope, 0, 1, except) << 11) + (getOperande(ope, 2, 0, except) << 6) + ROTR;
    }
    else if(strcmp(op, "SLL") == 0)
    {
        res += (getOperande(ope, 1, 1, except) << 16) + (getOperande(ope, 0, 1, except) << 11) + (getOperande(ope, 2, 0, except) << 6) + SLL;
    }
    else if(strcmp(op, "SLT") == 0)
    {
        res += (getOperande(ope, 1, 1, except) << 21) + (getOperande(ope, 2, 1, except) << 16) + (getOperande(ope, 0, 1, except) << 11) + SLT;
    }
    else if(strcmp(op, "SRL") == 0)
    {
        res += (getOperande(ope, 1, 1, except) << 16) + (getOperande(ope, 0, 1, except) << 11) + (getOperande(ope, 2, 0, except) << 6) + SRL;
    }
    else if(strcmp(op, "SUB") == 0)
    {
        res += (getOperande(ope, 1, 1, except) << 21) + (getOperande(ope, 2, 1, except) << 16) + (getOperande(ope, 0, 1, except) << 11) + SUB;
    }
    else if(strcmp(op, "SW") == 0)
    {
        res += (SW << 26) + (getBase(ope, except) << 21) + (getOperande(ope, 0, 1, except) << 16) + getOffset(ope, except);
    }
    else if(strcmp(op, "SYSCALL") == 0)
    {
        int code = 0; // ??
        res += (code << 6) + SYSCALL;
    }
    else if(strcmp(op, "XOR") == 0)
    {
        res += (getOperande(ope, 1, 1, except) << 21) + (getOperande(ope, 2, 1, except) << 16) + (getOperande(ope, 0, 1, except) << 6) + XOR;
    }
    else
    {
        *except = UNKOWN_OP;
    }
    
    free(op);
    free(ope);
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

    char* op = inst;
    if(placement == 1)
        op = strchr(op, ',') + 1;
    else if(placement == 2)
        op = strchr(strchr(op, ',' ) + 1, ',') + 1;
    
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
    if(reg) op++;

    while (op[i] != ',' && op[i] != '\0')
        i++;
    
    char res[i + 1];
    for(int j = 0; j < i; j++)
        res[j] = op[j];
    res[i] = '\0';

    if(reg)
        return getRegister(res, except);
    else
    {
        int strToIntErr = 0;
        int n = strToInt(res, &strToIntErr);
        if(strToIntErr == -1)
        {
            *except = SYNTAX_ERROR;
            return 0;
        }

        return n;
    }
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
    return getRegister(res, except);

}

int getOffset(const char* inst, int* except) 
{
    char* offset = strchr(inst, ',') + 1;
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
    
    int strToIntErr = 0;
    int n = strToInt(res, &strToIntErr);
    if(strToIntErr == -1)
    {
        *except = SYNTAX_ERROR;
        return 0;
    }

    return n;
}

int getRegister(const char* reg, int *except)
{
    int strToIntErr;
    if      (strcmp(reg, "zero") == 0)     return 0;
    else if (strcmp(reg, "at"  ) == 0)     return 1;
    else if (strcmp(reg, "gp"  ) == 0)     return 28;
    else if (strcmp(reg, "sp"  ) == 0)     return 29;
    else if (strcmp(reg, "fp"  ) == 0)     return 30;
    else if (strcmp(reg, "ra"  ) == 0)     return 31;
    else
    {
        if(strchr("vatsk", reg[0]) != NULL)
        {
            int num = strToInt(reg + 1, &strToIntErr);
            if(strToIntErr != -1) 
            {
                if(reg[0] == 'v' && (num == 0 || num == 1))  return num + 2;
                if(reg[0] == 'a' && (num >= 0 && num <= 3))  return num + 4;
                if(reg[0] == 's' && (num >= 0 && num <= 7))  return num + 16;
                if(reg[0] == 'k' && (num == 0 || num == 1))  return num + 26;
                if(reg[0] == 't')
                {
                    if(num >= 0 && num <= 7)
                        return num + 8;
                    else if(num == 8 || num == 9)
                        return num + 16;
                }
            }
        }
        else if(strToInt(reg, &strToIntErr) >= 0 && strToInt(reg, &strToIntErr) <= 31 && strToIntErr != -1)
            return atoi(reg);

        *except = UNDEFINED_REG;
        return 0;
    }
}

void execADDI(int inst, int *execpt) 
{
    int rs = (inst & 0x3E00000) >> 21;
    int rt = (inst & 0x1F0000) >> 16;
    int immediate = inst & 0xFFFF;
    setRegisterValue(rt, getRegisterValue(rs) + immediate);
}

void execADD(int inst, int *execpt) 
{
    int rs = (inst & 0x3E00000) >> 21;
    int rt = (inst & 0x1F0000) >> 16;
    int rd = (inst & 0xF800) >> 11;
    setRegisterValue(rd, getRegisterValue(rs) + getRegisterValue(rt));
}

void execAND(int inst, int *execpt) 
{
    
}

void execBEQ(int inst, int *execpt) 
{
    
}

void execBGTZ(int inst, int *execpt) 
{
    
}

void execBLEZ(int inst, int *execpt) 
{
    
}

void execBNE(int inst, int *execpt) 
{
    
}

void execDIV(int inst, int *execpt) 
{
    
}

void execJ(int inst, int *execpt) 
{
    
}

void execJAL(int inst, int *execpt) 
{
    
}

void execJR(int inst, int *execpt) 
{
    
}

void execLUI(int inst, int *execpt) 
{
    
}

void execLW(int inst, int *execpt) 
{
    
}

void execMHFI(int inst, int *execpt) 
{
    
}

void execMHLO(int inst, int *execpt) 
{
    
}

void execMULT(int inst, int *execpt) 
{
    
}

void execNOP(int inst, int *execpt) 
{
    
}

void execOR(int inst, int *execpt) 
{
    
}

void execROTR(int inst, int *execpt) 
{
    
}

void execSLL(int inst, int *execpt) 
{
    
}

void execSLT(int inst, int *execpt) 
{
    
}

void execSRL(int inst, int *execpt) 
{
    
}

void execSUB(int inst, int *execpt) 
{
    int rs = (inst & 0x3E00000) >> 21;
    int rt = (inst & 0x1F0000) >> 16;
    int rd = (inst & 0xF800) >> 11;
    setRegisterValue(rd, getRegisterValue(rs) - getRegisterValue(rt));
}

void execSW(int inst, int *execpt) 
{
    
}

void execSYSCALL(int inst, int *execpt) 
{
    
}

void execXOR(int inst, int *execpt) 
{
    
}
