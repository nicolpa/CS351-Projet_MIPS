#include <stdio.h>
#include "exceptions.h"

#ifndef REGISTER_H
#define REGISTER_H

#define N_REGISTER 32

/**
 * Initialize all registers
 */
void initRegisters();

/**
 * Get a value from a specified register
 * @param registerId The register
 */
int getRegisterValue(int registerId);

/**
 * Get the LO register value
 * @return The value of the register
 */
int getLO();

/**
 * Get the HI register value
 * @return The value of the register
 * 
 */
int getHI();

/**
 * Get the value from the program counter
 * @return The value of the PC
 */
int getPC();

/**
 * Set the value for a specified register
 * @param registerId The register
 * @param value The value to store in the register
 */
void setRegisterValue(int registerId, int value);

/**
 * Set the value of the LO register
 * @param value The value to store
 */
void setLO(int value);

/**
 * Set the value of the HI register
 * @param value The value to store
 */
void setHI(int value);

/**
 * Set the value of the PC
 * @param value The value to store
 */
void setPC(int value);

/**
 * Display the registers state
 */
void displayRegisters();

#endif