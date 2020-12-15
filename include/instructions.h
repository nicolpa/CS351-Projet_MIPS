#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "exceptions.h"
#include "str.h"
#include "memory.h"
#include "register.h"

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

//instruction set opcode
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

// Macro to extract each operand from an instruction

#define RS(inst)    ((inst & 0x3E00000   ) >> 21)
#define RD(inst)    ((inst & 0xF800      ) >> 11)
#define RT(inst)    ((inst & 0x1F0000    ) >> 16)
#define IMM(inst)    (inst & 0xFFFF)
#define SA(inst)    ((inst & 0x7E0       ) >> 6)

typedef struct
{
    char *sOpcode;                      // The string representation of the opcode
    int nOpcode;                        // The hexadecilam value of the opcode
    int bSpecial;                       // Whether or not it is a "special" opcode
    void (*exec)(int);     // Pointer to the function to execture for the instruction
}instruction;


/**
 * Parse a string instruction into its hexadecimal value
 * @param inst The instruction to parse
 */
int instructionHex(char *inst);

/**
 * Get the opcode from an instruction
 * @param inst The instruction
 * @return The opcode
 */
instruction getOpcode(const char *inst);

/**
 * Parse the string representation of the opcode into its associate instruction 
 * @param str The opcode to be parsed
 * @return The parsed opcode
 */
instruction parseOpcode(const char *str);

/**
 * Fetch the instruction with the specified opcode
 * @param opcode The instruction opcode to fetch
 * @param bSpecial // Whether or not it is a "special" opcode
 * @return The correct instruction
 */
instruction fetchOpcode(const int opcode, const int bSpecial);

/**
 * Get on operand from the instruction
 * @param inst The instruction
 * @param placement The index of the operand within the instruction
 * @param reg 1 if the operand is a register, 0 otherwise
 * @return The hexadecimal value of the operand
 */
int getOperande(const char *inst, int placement, int reg);

/**
 * Get the base of the address
 * @param inst The instruction
 * @return The hexadecimal value of the base
 * 
 */
int getBase(const char *inst);

/**
 * Get the offset of the address
 * @param inst The instruction
 * @return The hexadecimal value of the offset
 */
int getOffset(const char *inst);

/**
 * Parse the register into its hexadecimal value
 * @param reg The register to parse
 * @return The hexadecimal value of the register
 */
int getRegister(const char *reg);

/**
 * Convert a n bit signed integer to a m bit signed integer
 * @param value The value to be converted
 * @param n The number of bits of the variable
 * @param m The number of bits of the output variable
 * @return The converted value
 */
int signedNBitsToMBits(int value, int n, int m);

//Execute each instruction

void execADDI   (int inst);
void execADD    (int inst);
void execAND    (int inst);
void execBEQ    (int inst);
void execBGTZ   (int inst);
void execBLEZ   (int inst);
void execBNE    (int inst);
void execDIV    (int inst);
void execJ      (int inst);
void execJAL    (int inst);
void execJR     (int inst);
void execLUI    (int inst);
void execLW     (int inst);
void execMHFI   (int inst);
void execMHLO   (int inst);
void execMULT   (int inst);
void execNOP    (int inst);
void execOR     (int inst);
void execSLL    (int inst);
void execSLT    (int inst);
void execSRL    (int inst);
void execSUB    (int inst);
void execSW     (int inst);
void execSYSCALL(int inst);
void execXOR    (int inst);

#endif