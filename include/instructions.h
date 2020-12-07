#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exceptions.h"
#include "str.h"
#include "memory.h"
#include "register.h"

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

//instruction set
#define ADD     0x20    //<-
#define ADDI    0x8
#define AND     0x24    //<-
#define BEQ     0x4
#define BGTZ    0x7
#define BLEZ    0x6
#define BNE     0x5
#define DIV     0x1A    //<-
#define J       0x2
#define JAL     0x3
#define JR      0x8     //<-
#define LUI     0xF
#define LW      0x23
#define MFHI    0x10    //<-
#define MFLO    0x12    //<-
#define MULT    0x18    //<-
#define NOP     0x0     //<-
#define OR      0x25    //<-
#define ROTR    0x2     //<-
#define SLL     0x0     //<-
#define SLT     0x2A    //<-
#define SRL     0x2     //<-
#define SUB     0x22    //<-
#define SW      0x2B
#define SYSCALL 0xC     //<-
#define XOR     0x26    //<-

#define RS(inst)    ((inst & 0x3E00000   ) >> 21)
#define RD(inst)    ((inst & 0xF800      ) >> 11)
#define RT(inst)    ((inst & 0x1F0000    ) >> 16)
#define IMM(inst)    (inst & 0xFFFF)
#define SA(inst)    ((inst & 0x7E0        )      >> 6)

void assemblyToHex(const char *src, const char *dst);

int instructionHex(char *inst, int *except);

char *getOpcode(const char *inst);

//reg = 1 the op is a register
int getOperande(const char *inst, int placement, int reg, int *except);

int getBase(const char *inst, int *except);

int getOffset(const char *inst, int *except);

int getRegister(const char *reg, int *except);

void execADDI   (int inst, int *except);
void execADD    (int inst, int *except);
void execAND    (int inst, int *except);
void execBEQ    (int inst, int *except);
void execBGTZ   (int inst, int *except);
void execBLEZ   (int inst, int *except);
void execBNE    (int inst, int *except);
void execDIV    (int inst, int *except);
void execJ      (int inst, int *except);
void execJAL    (int inst, int *except);
void execJR     (int inst, int *except);
void execLUI    (int inst, int *except);
void execLW     (int inst, int *except);
void execMHFI   (int inst, int *except);
void execMHLO   (int inst, int *except);
void execMULT   (int inst, int *except);
void execNOP    (int inst, int *except);
void execOR     (int inst, int *except);
void execROTR   (int inst, int *except);
void execSLL    (int inst, int *except);
void execSLT    (int inst, int *except);
void execSRL    (int inst, int *except);
void execSUB    (int inst, int *except);
void execSW     (int inst, int *except);
void execSYSCALL(int inst, int *except);
void execXOR    (int inst, int *except);

#endif