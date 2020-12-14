#include "../include/instructions.h"

const instruction instructionSet[] = 
{
    { "ADD"      , ADD      , 1, execADD    },
    { "ADDI"     , ADDI     , 0, execADDI   },
    { "AND"      , AND      , 1, execAND    },
    { "BEQ"      , BEQ      , 0, execBEQ    },
    { "BGTZ"     , BGTZ     , 0, execBGTZ   },
    { "BLEZ"     , BLEZ     , 0, execBLEZ   },
    { "BNE"      , BNE      , 0, execBNE    },
    { "DIV"      , DIV      , 1, execDIV    },
    { "J"        , J        , 0, execJ      },
    { "JAL"      , JAL      , 0, execJAL    },
    { "JR"       , JR       , 1, execJR     },
    { "LUI"      , LUI      , 0, execLUI    },
    { "LW"       , LW       , 0, execLW     },
    { "MFHI"     , MFHI     , 1, execMHFI   },
    { "MFLO"     , MFLO     , 1, execMHLO   },
    { "MULT"     , MULT     , 1, execMULT   },
    { "NOP"      , NOP      , 1, execNOP    },
    { "OR"       , OR       , 1, execOR     },
    { "ROTR"     , ROTR     , 1, execSRL    },
    { "SLL"      , SLL      , 1, execSLL    },
    { "SLT"      , SLT      , 1, execSLT    },
    { "SRL"      , SRL      , 1, execSRL    },
    { "SUB"      , SUB      , 1, execSUB    },
    { "SW"       , SW       , 0, execSW     },
    { "SYSCALL"  , SYSCALL  , 1, execSYSCALL},
    { "XOR"      , XOR      , 1, execXOR    },
    { "ILLEGAL"  , -1       ,-1             }
};

int instructionHex(char* inst, exception *except) 
{
    *except = fetchException(OK);
    instruction opcode = getOpcode(inst, except);
    if(strcmp(opcode.sOpcode, "NOP") == 0)
        return 0;
    
    char *operand = strchr(inst, ' ') + 1;
    if(operand == 1)
    {
        *except = fetchException(SYNTAX_ERROR);
        return 0;
    }
    int res = 0;
    if(opcode.bSpecial)
    {
        if(opcode.nOpcode == SLL || opcode.nOpcode == SRL)        
        {
            char *tmp = (char *)malloc(sizeof(char) * strlen(inst));
            strcpy(tmp, inst);
            char *ptr = strtok(tmp, " ");
            int bROTR = (strcmp(ptr, "ROTR") == 0) ? 1 : 0;
            free(tmp);
            res += (bROTR << 21) + (getOperande(operand, 1, 1, except) << 16) + (getOperande(operand, 0, 1, except) << 11) + signedNBitsToMBits(getOperande(operand, 2, 0, except) << 6, 32, 5) + opcode.nOpcode;
        }
        else if(opcode.nOpcode == MULT || opcode.nOpcode == DIV)
        {
            res += (getOperande(operand, 0, 1, except) << 21) + (getOperande(operand, 1, 1, except) << 16) + opcode.nOpcode;
        }
        else if(opcode.nOpcode == MFHI || opcode.nOpcode == MFLO)
        {
            res += (getOperande(operand, 0, 1, except) << 11) + opcode.nOpcode;
        }
        else if(opcode.nOpcode == JR)
        {
            int hint = 0;   // ?
            res += (getOperande(operand, 0, 1, except) << 21) + (hint << 6) + JR;
        }
        else if(opcode.nOpcode == SYSCALL)
        {
            int code = 0;   // ?
            res += (code << 6) + SYSCALL;
        }
        else
        {
            res += (getOperande(operand, 1, 1, except) << 21) + (getOperande(operand, 2, 1, except) << 16) + (getOperande(operand, 0, 1, except) << 11) + opcode.nOpcode;
        }
    }
    else
    {
        if(opcode.nOpcode == LW || opcode.nOpcode == SW)        
        {
            res += (opcode.nOpcode << 26) + (getBase(operand, except) << 21) + (getOperande(operand, 0, 1, except) << 16) + signedNBitsToMBits(getOffset(operand, except), 32, 16);
        }
        else if(opcode.nOpcode == BLEZ || opcode.nOpcode == BGTZ)
        {
            res += (opcode.nOpcode << 26) + (getOperande(operand, 0, 1, except) << 21) + signedNBitsToMBits(getOperande(operand, 1, 0, except), 32, 16);
        }
        else if(opcode.nOpcode == LUI)
        {
            res += (LUI << 26) + (getOperande(operand, 1, 0, except) << 16) + signedNBitsToMBits(getOperande(operand, 1, 0, except), 32, 16);
        }
        else if(opcode.nOpcode == J || opcode.nOpcode == JAL)
        {
            res += (opcode.nOpcode << 26) + signedNBitsToMBits(getOperande(operand, 0, 0, except), 32, 26);
        }
        else
        {
            res += (opcode.nOpcode << 26) + (getOperande(operand, 1, 1, except) << 21) + (getOperande(operand, 0, 1, except) << 16) + signedNBitsToMBits(getOperande(operand, 2, 0, except), 32, 16);
        }
    }
    return res;
}

instruction getOpcode(const char* inst, exception *except) 
{
    char *tmp = (char *)malloc(sizeof(char) * strlen(inst));
    strcpy(tmp, inst);
    char *ptr = strtok(tmp, " ");
    
    instruction instOp = parseOpcode(ptr, except);
    free(tmp);

    return instOp;
}

instruction parseOpcode(const char *str, exception *except) 
{
    for(int i = 0; i < 26; i++)
    {
        if(strcmp(str, instructionSet[i].sOpcode) == 0)
            return instructionSet[i];
    }

    *except = fetchException(UNKOWN_OP);
    return instructionSet[26];
}

instruction fetchOpcode(const int opcode, const int bSpecial, exception *except) 
{
    for(int i = 0; i < 26; i++)
    {
        if(instructionSet[i].nOpcode == opcode && instructionSet[i].bSpecial == bSpecial)
            return instructionSet[i];
    }

    *except = fetchException(UNKOWN_OP);
    return instructionSet[26];
}

int getOperande(const char* inst, int placement, int reg, exception *except) 
{
    if(except->nCode != OK)
        return 0;

    char *tmp = (char *)malloc(sizeof(char) * strlen(inst));
    strcpy(tmp, inst);

    char *op = strtok(tmp," ,");
    switch (placement)
    {
    case 2:
        op = strtok(NULL, " ,");
    case 1:
        op = strtok(NULL, " ,");
        break;
    }
    
    if(op == NULL)
    {
        *except = fetchException(SYNTAX_ERROR);
        return 0;
    }
    
    if(reg && op[0] != '$')
    {
        *except = fetchException(REG_EXPECTED);
        return 0;
    }
    if(!reg && op[0] == '$')
    {
        *except = fetchException(IMM_EXPECTED);
        return 0;
    }

    int res;
    if(reg)
    {
        res = getRegister(++op, except);
        free(tmp);
        return res;
    }
    else
    {
        int strToIntErr = 0;
        int n = strToInt(op, &strToIntErr);
        free(tmp);
        if(strToIntErr == -1)
        {
            *except = fetchException(SYNTAX_ERROR);
            return 0;
        }

        return n;
    }
}

int getBase(const char* inst, exception *except) 
{
    char* base = strchr(inst, '(') + 1;
    if(base[0] != '$')
    {
        *except = fetchException(REG_EXPECTED);
        return 0;
    }

    int i = 0;
    base += 1;
    while(base[i] != ')' && base[i] != '\0')
        i++;
    
    if(base[i] == '\0')
    {
        *except = fetchException(SYNTAX_ERROR);
        return 0;
    }

    char res[i + 1];
    for(int j = 0; j < i; j++)
        res[j] = base[j];
    res[i] = '\0';
    return getRegister(res, except);

}

int getOffset(const char* inst, exception *except) 
{
    char* offset = strchr(inst, ',') + 2;
    if(offset[0] == '$')
    {
        *except = fetchException(IMM_EXPECTED);
        return 0;
    }
    int i = 0;
    while(offset[i] != '(' && offset[i] != '\0')
        i++;
    
    if(offset[i] == '\0')
    {
        *except = fetchException(SYNTAX_ERROR);
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
        *except = fetchException(SYNTAX_ERROR);
        return 0;
    }

    return n;
}

int getRegister(const char* reg, exception *except)
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

        *except = fetchException(UNDEFINED_REG);
        return 0;
    }
}

int signedNBitsToMBits(int value, int n, int m) 
{
    long int signedNBitMask = pow(2, n) - 1;

    if((value & ((signedNBitMask + 1) >> 1)) >> (n - 1) == 0)
        return value;

    long int signedMBitMask = pow(2, m) - 1;

    int res = ((~value) & signedNBitMask) + 1;
    res = ((~res) & signedMBitMask) + 1;

    return res;
}

void execADDI(int inst, exception *except) 
{
    setRegisterValue(RT(inst), getRegisterValue(RS(inst)) + signedNBitsToMBits(IMM(inst), 16, 32));
}

void execADD(int inst, exception *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RS(inst)) + getRegisterValue(RT(inst)));
}

void execAND(int inst, exception *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RS(inst)) & getRegisterValue(RT(inst)));
}

void execBEQ(int inst, exception *except) 
{
    if(getRegisterValue(RS(inst)) == getRegisterValue(RT(inst)))
        setPC(getPC() + (signedNBitsToMBits(IMM(inst), 16, 32) * 4));
}

void execBGTZ(int inst, exception *except) 
{
    if(getRegisterValue(RS(inst)) > 0)
        setPC(getPC() + (signedNBitsToMBits(IMM(inst), 16, 32) * 4));
}

void execBLEZ(int inst, exception *except) 
{
    if(getRegisterValue(RS(inst)) <= 0)
        setPC(getPC() + (signedNBitsToMBits(IMM(inst), 16, 32) * 4));
}

void execBNE(int inst, exception *except) 
{
    if(getRegisterValue(RS(inst)) != getRegisterValue(RT(inst)))
        setPC(getPC() + (signedNBitsToMBits(IMM(inst), 16, 32) * 4));
}

void execDIV(int inst, exception *except) 
{
    int rs = RS(inst);
    int rt = RT(inst);
    
    setLO(getRegisterValue(rs) / getRegisterValue(rt));
    setHI(getRegisterValue(rs) % getRegisterValue(rt));
}

void execJ(int inst, exception *except) 
{
    printf("Gne\n");
    setPC(getPC() + (RS(inst) * 4));
}

void execJAL(int inst, exception *except) 
{
    // TODO
}

void execJR(int inst, exception *except) 
{
    setPC(getRegisterValue(RS(inst)));
    printf("PC = %d\n", getPC());
}

void execLUI(int inst, exception *except) 
{
    setRegisterValue(RT(inst), signedNBitsToMBits(IMM(inst), 16, 32) << 16);
}

void execLW(int inst, exception *except) 
{
    int base = getRegisterValue(RS(inst));
    int rt = RT(inst);
    int offset = IMM(inst);

    setRegisterValue(rt, load((offset * 4) + base, except));
}

void execMHFI(int inst, exception *except) 
{
    setRegisterValue(RD(inst), getHI());
}

void execMHLO(int inst, exception *except) 
{
    setRegisterValue(RD(inst), getLO());
}

void execMULT(int inst, exception *except) 
{
    long int res = getRegisterValue(RS(inst)) * getRegisterValue(RT(inst));
    setLO(res & 0xFFFFFFFF);
    setHI(res >> 32);
}

void execNOP(int inst, exception *except) 
{
    // do nothing
}

void execOR(int inst, exception *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RS(inst)) | getRegisterValue(RT(inst)));
}

void execSLL(int inst, exception *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RT(inst) << signedNBitsToMBits(SA(inst), 5, 32)));
}

void execSLT(int inst, exception *except) 
{
    if(getRegisterValue(RS(inst)) < getRegisterValue(RT(inst)))
        setRegisterValue(RD(inst), 1);
    else
        setRegisterValue(RD(inst), 0);
}

void execSRL(int inst, exception *except) 
{
    int tmp = 0;
    if((inst & 0x200000) == 0x200000)
        tmp = getRegisterValue(RT(inst)) << (32 - signedNBitsToMBits(SA(inst), 5, 32));

    setRegisterValue(RD(inst), tmp + (getRegisterValue(RT(inst)) >> signedNBitsToMBits(SA(inst), 5, 32)));
}

void execSUB(int inst, exception *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RD(inst)) - getRegisterValue(RT(inst)));
}

void execSW(int inst, exception *except) 
{
    int base = getRegisterValue(RS(inst));
    int offset = IMM(inst);

    store(base + (offset * 4), getRegisterValue(RT(inst)), except);
}

void execSYSCALL(int inst, exception *except) 
{
    // TODO
}

void execXOR(int inst, exception *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RS(inst)) ^ getRegisterValue(RT(inst)));
}