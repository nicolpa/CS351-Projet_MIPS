#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <ctype.h>

#ifndef STR_H
#define STR_H

char *trim(char *s);

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

/**
 * Remove all unecessary spaces and tabulation from the string
 */
void formatString(char *str);

/**
 * Check whether or not a character is an alpha-numeric value
 * @return 1 if it's alpha-numeric 0 otherwise
 */
int isAlphaNum(char c);

#endif