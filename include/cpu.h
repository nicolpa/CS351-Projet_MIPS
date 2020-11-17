#include "../include/instructions.h"
#include "../include/register.h"
#include "../include/memory.h"

#ifndef CPU_H
#define CPU_H

void initCPU();

void loadFile(char *src, int *except);

void loadInstruction(int instruct, int *except);

void run(char* flag, char* src);

#endif