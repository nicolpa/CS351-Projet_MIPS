#include <string.h>
#include <stdlib.h>

#ifndef STR_H
#define STR_H

char *removeSpaces(const char *str);

int strToInt(const char *str, int *except);

void removeComment(char *str);

#endif