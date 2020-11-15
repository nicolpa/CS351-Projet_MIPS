#include <stdio.h>
#include <stdlib.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node Node;
struct Node
{
    int value;
    int address;
    Node *next;
};

typedef Node *List;

void insert(List *l, int value, int address);

void delete(List *l, int address);

int fetch(List *l, int address);

void print(List *l);

void clear(List *l);

#endif