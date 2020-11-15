#include <stdio.h>

#ifndef REGISTER_H
#define REGISTER_H

#define N_REGISTER 32

void initRegisters();

int getRegisterValue(int registerId);

int getHO();

int getHI();

int getPC();

void setRegisterValue(int registerId, int value);

void setHO(int value);

void setHI(int value);

void setPC(int value);

void displayRegisters();

#endif