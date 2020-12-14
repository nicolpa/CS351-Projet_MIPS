#include <stdio.h>
#include "linkedList.h"
#include "exceptions.h"
#include <string.h>
#include <stdlib.h>

#ifndef MEMORY_H
#define MEMORY_H

#define LAST_ADDRESS 0xFFFFFFFC

/**
 * Initiaze an empty memory
 */
void initMemory();

/**
 * Load an element from memory at specified address
 * @param address The address of the element
 * @param except Return parameter for exception handling
 * @return The loaded value
 */
int load(unsigned int address, exception *except);

/**
 * Store an element into memory
 * @param address The address of the element
 * @param value The value to be stored
 * @param except Return parameter for exception handling
 */
void store(unsigned int address, int value, exception *except);

/**
 * Display the memory
 * @param lastAddress Don't display element in memory starting from this adress (used to hide the program loaded in memory from the user)
 */
void displayMemory(unsigned int lastAddress);

/**
 * Empty the entire memory
 */
void clearMemory();

/**
 * Translate the relative program address into an absolute on 
 * @param address The address to be translated
 * @return The translated memory address
 */
int translateProgramAddress(unsigned int address);

#endif