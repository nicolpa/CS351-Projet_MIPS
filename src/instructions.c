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
    { "NOP"      , NOP      , 1, execSLL    },
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

int instructionHex(char* inst) 
{
    setException(OK);
    instruction opcode = getOpcode(inst);
    if(strcmp(opcode.sOpcode, "NOP") == 0)
        return 0;
    
    char *operand = strchr(inst, ' ');
    if(operand == NULL)
    {
        setException(SYNTAX_ERROR);
        return 0;
    }
    operand++;
    
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
            res += (bROTR << 21) + (getOperande(operand, 1, 1) << 16) + (getOperande(operand, 0, 1) << 11) + signedNBitsToMBits(getOperande(operand, 2, 0) << 6, 32, 5) + opcode.nOpcode;
        }
        else if(opcode.nOpcode == MULT || opcode.nOpcode == DIV)
        {
            res += (getOperande(operand, 0, 1) << 21) + (getOperande(operand, 1, 1) << 16) + opcode.nOpcode;
        }
        else if(opcode.nOpcode == MFHI || opcode.nOpcode == MFLO)
        {
            res += (getOperande(operand, 0, 1) << 11) + opcode.nOpcode;
        }
        else if(opcode.nOpcode == JR)
        {
            int hint = 0;   // ?
            res += (getOperande(operand, 0, 1) << 21) + (hint << 6) + JR;
        }
        else if(opcode.nOpcode == SYSCALL)
        {
            int code = 0;   // ?
            res += (code << 6) + SYSCALL;
        }
        else
        {
            res += (getOperande(operand, 1, 1) << 21) + (getOperande(operand, 2, 1) << 16) + (getOperande(operand, 0, 1) << 11) + opcode.nOpcode;
        }
    }
    else
    {
        if(opcode.nOpcode == LW || opcode.nOpcode == SW)        
        {
            res += (opcode.nOpcode << 26) + (getBase(operand) << 21) + (getOperande(operand, 0, 1) << 16) + signedNBitsToMBits(getOffset(operand), 32, 16);
        }
        else if(opcode.nOpcode == BLEZ || opcode.nOpcode == BGTZ)
        {
            res += (opcode.nOpcode << 26) + (getOperande(operand, 0, 1) << 21) + signedNBitsToMBits(getOperande(operand, 1, 0), 32, 16);
        }
        else if(opcode.nOpcode == LUI)
        {
            res += (LUI << 26) + (getOperande(operand, 1, 0) << 16) + signedNBitsToMBits(getOperande(operand, 1, 0), 32, 16);
        }
        else if(opcode.nOpcode == J || opcode.nOpcode == JAL)
        {
            res += (opcode.nOpcode << 26) + signedNBitsToMBits(getOperande(operand, 0, 0), 32, 26);
        }
        else
        {
            res += (opcode.nOpcode << 26) + (getOperande(operand, 1, 1) << 21) + (getOperande(operand, 0, 1) << 16) + signedNBitsToMBits(getOperande(operand, 2, 0), 32, 16);
        }
    }
    return res;
}

instruction getOpcode(const char* inst) 
{
    char *tmp = (char *)malloc(sizeof(char) * strlen(inst));
    strcpy(tmp, inst);
    char *ptr = strtok(tmp, " ");
    
    instruction instOp = parseOpcode(ptr);
    free(tmp);

    return instOp;
}

instruction parseOpcode(const char *str) 
{
    for(int i = 0; i < 26; i++)
    {
        if(strcmp(str, instructionSet[i].sOpcode) == 0)
            return instructionSet[i];
    }

    setException(UNKOWN_OP);
    setExceptionMetaData(str);
    return instructionSet[26];
}

instruction fetchOpcode(const int opcode, const int bSpecial) 
{
    for(int i = 0; i < 26; i++)
    {
        if(instructionSet[i].nOpcode == opcode && instructionSet[i].bSpecial == bSpecial)
            return instructionSet[i];
    }

    setException(UNKOWN_OP);
    return instructionSet[26];
}

int getOperande(const char* inst, int placement, int reg) 
{
    if(getExceptionCode() != OK)
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
        setException(SYNTAX_ERROR);
        return 0;
    }
    
    if(reg && op[0] != '$')
    {
        setException(REG_EXPECTED);
        setExceptionMetaData(op);
        return 0;
    }
    if(!reg && op[0] == '$')
    {
        setException(IMM_EXPECTED);
        setExceptionMetaData(op);
        return 0;
    }

    int res;
    if(reg)
    {
        res = getRegister(++op);
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
            setException(SYNTAX_ERROR);
            return 0;
        }

        return n;
    }
}

int getBase(const char* inst) 
{
    char* base = strchr(inst, '(') + 1;
    if(base[0] != '$')
    {
        setException(REG_EXPECTED);
        setExceptionMetaData(base);
        return 0;
    }

    int i = 0;
    base += 1;
    while(base[i] != ')' && base[i] != '\0')
        i++;
    
    if(base[i] == '\0')
    {
        setException(SYNTAX_ERROR);
        return 0;
    }

    char res[i + 1];
    for(int j = 0; j < i; j++)
        res[j] = base[j];
    res[i] = '\0';
    return getRegister(res);

}

int getOffset(const char* inst) 
{
    char* offset = strchr(inst, ',') + 2;
    if(offset[0] == '$')
    {
        setException(SYNTAX_ERROR);
        return 0;
    }
    int i = 0;
    while(offset[i] != '(' && offset[i] != '\0')
        i++;
    
    if(offset[i] == '\0')
    {
        setException(SYNTAX_ERROR);
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
        setException(SYNTAX_ERROR);
        return 0;
    }

    return n;
}

int getRegister(const char* reg)
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

        setException(UNDEFINED_REG);
        setExceptionMetaData(reg);
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

void execADDI(int inst) 
{
    setRegisterValue(RT(inst), getRegisterValue(RS(inst)) + signedNBitsToMBits(IMM(inst), 16, 32));
}

void execADD(int inst) 
{
    setRegisterValue(RD(inst), getRegisterValue(RS(inst)) + getRegisterValue(RT(inst)));
}

void execAND(int inst) 
{
    setRegisterValue(RD(inst), getRegisterValue(RS(inst)) & getRegisterValue(RT(inst)));
}

void execBEQ(int inst) 
{
    if(getRegisterValue(RS(inst)) == getRegisterValue(RT(inst)))
        setPC(getPC() + (signedNBitsToMBits(IMM(inst), 16, 32) * 4));
}

void execBGTZ(int inst) 
{
    if(getRegisterValue(RS(inst)) > 0)
        setPC(getPC() + (signedNBitsToMBits(IMM(inst), 16, 32) * 4));
}

void execBLEZ(int inst) 
{
    if(getRegisterValue(RS(inst)) <= 0)
        setPC(getPC() + (signedNBitsToMBits(IMM(inst), 16, 32) * 4));
}

void execBNE(int inst) 
{
    if(getRegisterValue(RS(inst)) != getRegisterValue(RT(inst)))
        setPC(getPC() + (signedNBitsToMBits(IMM(inst), 16, 32) * 4));
}

void execDIV(int inst) 
{
    int rs = RS(inst);
    int rt = RT(inst);
    
    setLO(getRegisterValue(rs) / getRegisterValue(rt));
    setHI(getRegisterValue(rs) % getRegisterValue(rt));
}

void execJ(int inst) 
{
    printf("Gne\n");
    setPC(getPC() + (RS(inst) * 4));
}

void execJAL(int inst) 
{
    // TODO
}

void execJR(int inst) 
{
    setPC(getRegisterValue(RS(inst)));
}

void execLUI(int inst) 
{
    setRegisterValue(RT(inst), signedNBitsToMBits(IMM(inst), 16, 32) << 16);
}

void execLW(int inst) 
{
    int base = getRegisterValue(RS(inst));
    int rt = RT(inst);
    int offset = IMM(inst);

    setRegisterValue(rt, load((offset * 4) + base));
}

void execMHFI(int inst) 
{
    setRegisterValue(RD(inst), getHI());
}

void execMHLO(int inst) 
{
    setRegisterValue(RD(inst), getLO());
}

void execMULT(int inst) 
{
    long int res = getRegisterValue(RS(inst)) * getRegisterValue(RT(inst));
    setLO(res & 0xFFFFFFFF);
    setHI(res >> 32);
}

void execOR(int inst) 
{
    setRegisterValue(RD(inst), getRegisterValue(RS(inst)) | getRegisterValue(RT(inst)));
}

void execSLL(int inst) 
{
    setRegisterValue(RD(inst), getRegisterValue(RT(inst) << signedNBitsToMBits(SA(inst), 5, 32)));
}

void execSLT(int inst) 
{
    if(getRegisterValue(RS(inst)) < getRegisterValue(RT(inst)))
        setRegisterValue(RD(inst), 1);
    else
        setRegisterValue(RD(inst), 0);
}

void execSRL(int inst) 
{
    int tmp = 0;
    if((inst & 0x200000) == 0x200000)
        tmp = getRegisterValue(RT(inst)) << (32 - signedNBitsToMBits(SA(inst), 5, 32));

    setRegisterValue(RD(inst), tmp + (getRegisterValue(RT(inst)) >> signedNBitsToMBits(SA(inst), 5, 32)));
}

void execSUB(int inst) 
{
    setRegisterValue(RD(inst), getRegisterValue(RD(inst)) - getRegisterValue(RT(inst)));
}

void execSW(int inst) 
{
    int base = getRegisterValue(RS(inst));
    int offset = IMM(inst);

    store(base + (offset * 4), getRegisterValue(RT(inst)), NULL);
}

void execSYSCALL(int inst) 
{
    // TODO
    printf("SYSCALL\n");
}

void execXOR(int inst) 
{
    setRegisterValue(RD(inst), getRegisterValue(RS(inst)) ^ getRegisterValue(RT(inst)));
}
