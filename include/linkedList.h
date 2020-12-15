#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node Node;
struct Node
{
    int value;
    unsigned int address;
    char *sInstruction;     // Hold the string representation of a loaded instruction in memory
    Node *next;
};

typedef Node *List;

/**
 * Add an element to the lsit
 * @param l The list
 * @param value The value of the new element
 * @param address The address for the newe element
 * @param sIntruction The string representation of the instruction to load in memory (set to NULL if it not an instrucion)
 */
void insert(List *l, int value, unsigned int address, char *sIntruction);

/**
 * Delete an element at the specified address
 * @param l The list
 * @param address The address of the element to be removed
 */
void delete (List *l, unsigned int address);

/**
 * Fetch the value at a specified address
 * @param l The list
 * @param address The address of the element
 * @return The value at the specified address, 0 is the address was not found
 */
Node *fetch(List *l, unsigned int address);

/**
 * Print the list current state
 * @param l The list
 * @param lastAddress Don't print any element starting from this address
 */
void print(List *l, unsigned int lastAddress);

/**
 * Remove all element from the list
 * @param l The list
 */
void clear(List *l);

#endif