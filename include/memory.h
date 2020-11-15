#include <stdint.h>
#include <stdio.h>
#include "linkedList.h"

#ifndef MEMORY_H
#define MEMORY_H

#define N_MEMORY 16

void initMemory();

int load(int address);

void store(int address, int32_t value);

void displayMemory();

#endif