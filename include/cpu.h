#include <string.h>
#include "../include/instructions.h"
#include "../include/register.h"
#include "../include/memory.h"

#ifndef CPU_H
#define CPU_H

void initCPU();

int loadFile(char *src, int *except);

void loadInstruction(int instruct, int address, int *except);

void run(char* flag, char* src);

int readFromTerminal();

#endif