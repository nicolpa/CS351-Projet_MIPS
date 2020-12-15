#include "linkedList.h"

void insert(List *l, int value, unsigned int address, char *sIntruction)
{
    Node *ptCurr = *l;
    Node *ptPrev = NULL;
    while (ptCurr != NULL && ptCurr->address < address)
    {
        ptPrev = ptCurr;
        ptCurr = ptCurr->next;
    }

    if (ptCurr != NULL && ptCurr->address == address)
        ptCurr->value = value;
    else
    {
        Node *e = (Node *)malloc(sizeof(Node));
        e->value = value;
        e->address = address;

        if (ptPrev != NULL)
            ptPrev->next = e;
        else
            *l = e;

        e->next = ptCurr;
        if(sIntruction != NULL)
        {
            e->sInstruction = (char *)malloc(sizeof(char) * strlen(sIntruction));
            strcpy(e->sInstruction, sIntruction);
        }
    }
}

void delete (List *l, unsigned int address)
{
    Node *ptCurr = *l;
    Node *ptPrev = NULL;

    while (ptCurr != NULL && ptCurr->address < address)
    {
        ptPrev = ptCurr;
        ptCurr = ptCurr->next;
    }

    if (ptCurr != NULL && ptCurr->address == address)
    {
        if (ptPrev != NULL)
            ptPrev->next = ptCurr->next;
        else
            *l = ptCurr->next;
        free(ptCurr);
    }
}

Node *fetch(List *l, unsigned int address)
{
    Node *ptCurr = *l;

    while (ptCurr != NULL && ptCurr->address < address)
        ptCurr = ptCurr->next;

    if (ptCurr != NULL && ptCurr->address == address)
        return ptCurr;

    return NULL;
}

void print(List *l, unsigned int lastAddress)
{
    Node *ptCurr = *l;

    int i = 0;
    while (ptCurr != NULL && ptCurr->address < lastAddress)
    {
        if (i != 0)
            printf("\t\t");
        printf("   @%.8u: %d", ptCurr->address, ptCurr->value);
        if (i == 3)
            printf("\n");

        i = (i + 1) % 4;

        ptCurr = ptCurr->next;
    }

    if(i == 0)
        printf("   Memory is empty\n\n");

    if (i != 3 && i != 0)
        printf("\n");

    printf("\n");
}

void clear(List *l)
{
    Node *ptCurr = *l;

    while (ptCurr != NULL)
    {
        Node *tmp = ptCurr->next;
        free(ptCurr);
        ptCurr = tmp;
    }

    (*l) = NULL;
}