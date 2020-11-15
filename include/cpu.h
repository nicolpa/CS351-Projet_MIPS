#include "../include/instructions.h"
#include "../include/register.h"
#include "../include/memory.h"

#ifndef CPU_H
#define CPU_H

void initCPU();

void loadInstructions();

void exec();

#endif