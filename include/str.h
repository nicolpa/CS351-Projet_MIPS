#include <string.h>
#include <stdlib.h>

#ifndef STR_H
#define STR_H

/**
 * Remove the spaces from a string
 * @param str The string
 */
char *removeSpaces(const char *str);

/**
 * Convert a string into an integer
 * @param str The string to parse
 * @param except Return parameter from exception handling
 */
int strToInt(const char *str, int *except);

/**
 * Disguard the comment of a string
 * @param str Return parameter The string without the comments
 */
void removeComment(char *str);

#endif