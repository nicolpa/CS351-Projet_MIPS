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
    { "ROTR"     , ROTR     , 1, execROTR   },
    { "SLL"      , SLL      , 1, execSLL    },
    { "SLT"      , SLT      , 1, execSLT    },
    { "SRL"      , SRL      , 1, execSRL    },
    { "SUB"      , SUB      , 1, execSUB    },
    { "SW"       , SW       , 0, execSW     },
    { "SYSCALL"  , SYSCALL  , 1, execSYSCALL},
    { "XOR"      , XOR      , 1, execXOR    },
    { "ILLEGAL"  , -1       ,-1             }
};

int instructionHex(char* inst, int *except) 
{
    inst = trim(inst);
    instruction opcode = getOpcode(inst, except);
    *except = 0;
    if(strcmp(opcode.sOpcode, "NOP") == 0)
        return 0;
    
    char *operand = removeSpaces(strchr(inst, ' '));
    int res = 0;
    if(opcode.bSpecial)
    {
        if(opcode.nOpcode == SLL || opcode.nOpcode == SRL || opcode.nOpcode == ROTR)        
        {
            res += (opcode.nOpcode == ROTR) ? (1 << 21) : 0 + (getOperande(operand, 1, 1, except) << 16) + (getOperande(operand, 0, 1, except) << 11) + signedNBitsToMBits(getOperande(operand, 2, 0, except) << 6, 32, 5) + opcode.nOpcode;
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
            (opcode.nOpcode << 26) + (getBase(operand, except) << 21) + (getOperande(operand, 0, 1, except) << 16) + signedNBitsToMBits(getOffset(operand, except), 32, 16);
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

instruction getOpcode(const char* inst, int *except) 
{
    int i = 0;
    while (inst[i] != ' ' && inst[i] != '\0')
        i++;

    char* op = (char *)malloc(i * sizeof(char));
    for(int j = 0; j < i; j++)
        op[j] = inst[j];
    op[i] = '\0';

    instruction instOp = parseOpcode(op, except);
    free(op);

    return instOp;
}

instruction parseOpcode(const char *str, int *except) 
{
    for(int i = 0; i < 26; i++)
    {
        if(strcmp(str, instructionSet[i].sOpcode) == 0)
            return instructionSet[i];
    }

    *except = UNKOWN_OP;
    return instructionSet[26];
}

instruction fetchOpcode(const int opcode, int *except) 
{
    for(int i = 0; i < 26; i++)
    {
        if(instructionSet[i].nOpcode == opcode)
            return instructionSet[i];
    }

    *except = UNKOWN_OP;
    return instructionSet[26];
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

void execADDI(int inst, int *except) 
{
    setRegisterValue(RT(inst), getRegisterValue(RS(inst)) + signedNBitsToMBits(IMM(inst), 16, 32));
}

void execADD(int inst, int *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RS(inst)) + getRegisterValue(RT(inst)));
}

void execAND(int inst, int *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RS(inst)) & getRegisterValue(RT(inst)));
}

void execBEQ(int inst, int *except) 
{
    if(getRegisterValue(RS(inst)) == getRegisterValue(RT(inst)))
        setPC(getPC() + (signedNBitsToMBits(IMM(inst), 16, 32) * 4));
}

void execBGTZ(int inst, int *except) 
{
    if(getRegisterValue(RS(inst)) > 0)
        setPC(getPC() + (signedNBitsToMBits(IMM(inst), 16, 32) * 4));
}

void execBLEZ(int inst, int *except) 
{
    if(getRegisterValue(RS(inst)) <= 0)
        setPC(getPC() + (signedNBitsToMBits(IMM(inst), 16, 32) * 4));
}

void execBNE(int inst, int *except) 
{
    if(getRegisterValue(RS(inst)) != getRegisterValue(RT(inst)))
        setPC(getPC() + (signedNBitsToMBits(IMM(inst), 16, 32) * 4));
}

void execDIV(int inst, int *except) 
{
    int rs = RS(inst);
    int rt = RT(inst);
    
    setLO(getRegisterValue(rs) / getRegisterValue(rt));
    setHI(getRegisterValue(rs) % getRegisterValue(rt));
}

void execJ(int inst, int *except) 
{
    
}

void execJAL(int inst, int *except) 
{
    
}

void execJR(int inst, int *except) 
{
    // int rs = (inst & 0x3E00000) >> 21;
    // int hint = 0;
    // setPC(getPC() + getRegisterValue(rs) * 4);
}

void execLUI(int inst, int *except) 
{
    setRegisterValue(RT(inst), signedNBitsToMBits(IMM(inst), 16, 32) << 16);
}

void execLW(int inst, int *except) 
{
    int base = getRegisterValue(RS(inst));
    int rt = RT(inst);
    int offset = IMM(inst);

    if(((offset + base) & 0x2) != 0)
        *except = INVALID_ADDRESS;
    else
        setRegisterValue(rt, load(offset + base, except));
}

void execMHFI(int inst, int *except) 
{
    setRegisterValue(RD(inst), getHI());
}

void execMHLO(int inst, int *except) 
{
    setRegisterValue(RD(inst), getLO());
}

void execMULT(int inst, int *except) 
{
    long int res = getRegisterValue(RS(inst)) * getRegisterValue(RT(inst));
    setLO(res & 0xFFFFFFFF);
    setHI(res >> 32);
}

void execNOP(int inst, int *except) 
{
    // do nothing
}

void execOR(int inst, int *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RS(inst)) | getRegisterValue(RT(inst)));
}

void execROTR(int inst, int *except) 
{
    
}

void execSLL(int inst, int *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RT(inst) << signedNBitsToMBits(SA(inst), 5, 32)));
}

void execSLT(int inst, int *except) 
{
    if(getRegisterValue(RS(inst)) < getRegisterValue(RT(inst)))
        setRegisterValue(RD(inst), 1);
    else
        setRegisterValue(RD(inst), 0);
}

void execSRL(int inst, int *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RT(inst) >> signedNBitsToMBits(SA(inst), 5, 32)));
}

void execSUB(int inst, int *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RD(inst)) - getRegisterValue(RT(inst)));
}

void execSW(int inst, int *except) 
{
    int base = getRegisterValue(RS(inst));
    int rt = RT(inst);
    int offset = IMM(inst);

    if(((offset + base) & 0x2) != 0)
        *except = INVALID_ADDRESS;
    else
    {
        store(base + offset, getRegisterValue(rt), except);
    }
}

void execSYSCALL(int inst, int *except) 
{
    
}

void execXOR(int inst, int *except) 
{
    setRegisterValue(RD(inst), getRegisterValue(RS(inst)) ^ getRegisterValue(RT(inst)));
}
