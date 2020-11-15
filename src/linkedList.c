#include "linkedList.h"

void insert(List *l, int value, int address)
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
    }
}

void delete (List *l, int address)
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

int fetch(List *l, int address)
{
    Node *ptCurr = *l;

    while (ptCurr != NULL && ptCurr->address <= address)
        ptCurr = ptCurr->next;

    if (ptCurr != NULL && ptCurr->address == address)
        return ptCurr->value;

    return 0;
}

void print(List *l)
{
    Node *ptCurr = *l;

    int i = 0;
    while (ptCurr != NULL)
    {
        if (i != 0)
            printf("\t\t");
        printf("@%.8d : %d", ptCurr->address, ptCurr->value);
        if (i == 3)
            printf("\n");

        i = (i + 1) % 4;

        ptCurr = ptCurr->next;
    }
    if (i != 3 && i != 0)
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