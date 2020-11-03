#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

//instruction
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
#define ROTR    0x1     //<-
#define SLL     0x0     //<-
#define SLT     0x2A    //<-
#define SRL     0x2     //<-
#define SRL     0x2     //<-
#define SUB     0x22    //<-
#define SW      0x2B
#define SYSCALL 0xC     //<-
#define XOR     0x26    //<-

//exception
#define OK              0
#define UNKOWN_OP       1
#define OVERFLOW        2
#define SYNTAX_ERROR    3
#define REG_EXPECTED    4
#define IMM_EXPECTED    5

void assemblyToHex(const char* src, const char* dst);
int instructionHex(const char* inst, int *except);
char* getOpcode(const char* inst);
//reg = 1 the op is a register
int getOperande(const char* inst, int placement, int reg, int* except);
int getBase(const char* inst, int* except);
int getOffset(const char* inst, int* except);
#endif