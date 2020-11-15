#include <stdint.h>
#include <stdio.h>

#ifndef REGISTER_H
#define REGISTER_H

#define N_REGISTER 32

void initRegisters();

int32_t  getRegisterValue(int registerId);
int32_t getHO();
int32_t getHI();
int32_t getPC();

void setRegisterValue(int registerId, int32_t value);
void setHO(int32_t value);
void setHI(int32_t value);
void setPC(int32_t value);

void displayRegisters();

#endif