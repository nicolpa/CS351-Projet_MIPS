#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exceptions.h"
#include "str.h"

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



void assemblyToHex(const char *src, const char *dst);

int instructionHex(const char *inst, int *except);

char *getOpcode(const char *inst);

//reg = 1 the op is a register
int getOperande(const char *inst, int placement, int reg, int *except);

int getBase(const char *inst, int *except);

int getOffset(const char *inst, int *except);

int getRegister(const char *reg, int *except);

void execADDI   (int inst, int *execpt);
void execADD    (int inst, int *execpt);
void execAND    (int inst, int *execpt);
void execBEQ    (int inst, int *execpt);
void execBGTZ   (int inst, int *execpt);
void execBLEZ   (int inst, int *execpt);
void execBNE    (int inst, int *execpt);
void execDIV    (int inst, int *execpt);
void execJ      (int inst, int *execpt);
void execJAL    (int inst, int *execpt);
void execJR     (int inst, int *execpt);
void execLUI    (int inst, int *execpt);
void execLW     (int inst, int *execpt);
void execMHFI   (int inst, int *execpt);
void execMHLO   (int inst, int *execpt);
void execMULT   (int inst, int *execpt);
void execNOP    (int inst, int *execpt);
void execOR     (int inst, int *execpt);
void execROTR   (int inst, int *execpt);
void execSLL    (int inst, int *execpt);
void execSLT    (int inst, int *execpt);
void execSRL    (int inst, int *execpt);
void execSUB    (int inst, int *execpt);
void execSW     (int inst, int *execpt);
void execSYSCALL(int inst, int *execpt);
void execXOR    (int inst, int *execpt);

#endif