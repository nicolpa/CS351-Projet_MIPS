#include <stdio.h>
#include "linkedList.h"
#include "exceptions.h"

#ifndef MEMORY_H
#define MEMORY_H

#define N_MEMORY 16

void initMemory();

int load(int address, int *except);

void store(int address, int value, int *except);

void displayMemory();

void clearMemory();

#endif