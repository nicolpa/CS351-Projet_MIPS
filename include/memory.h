#include <stdio.h>
#include "linkedList.h"

#ifndef MEMORY_H
#define MEMORY_H

#define N_MEMORY 16

void initMemory();

int load(int address);

void store(int address, int value);

void displayMemory();

#endif