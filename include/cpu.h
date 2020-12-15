#include <string.h>
#include "../include/instructions.h"
#include "../include/register.h"
#include "../include/memory.h"
#include "../include/ANSIColor.h"

#ifndef CPU_H
#define CPU_H

/**
 * Initialize both the registers and memory
 */
void initCPU();

/**
 * Load a file into memory
 * @param src The file's path
 * @return The program length
 */
int loadFile(char *src);

/**
 * Read an execution the standard input stream
 * @return Whether or not the program should be stopped
 */
int readFromTerminal();

/**
 * Run a program
 * @param flag execution parameter
 * @param src The file's path of the program to run
 */
void run(char* flag, char* src);

#endif