#ifndef _STRING_H
#define _STRING_H

#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int uint;

bool starts_with(const char* str, char c);
char* _strcpy(char* dest, const char* source);
char* _strcat(char* dest, const char* source);
uint _strlen(const char* str);
bool string_lower_than(const char* s1, const char* s2);
#endif
