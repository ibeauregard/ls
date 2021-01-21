#include <stdlib.h>
#include "_string.h"

char* _strcpy(char* dest, const char* source)
{
    uint i;
    for (i = 0; source[i]; i++)
    {
        dest[i] = source[i];
    }
    dest[i] = 0;
    return dest;
}

char* _strcat(char* dest, const char* source)
{
    uint i, j;
    for (i = 0; dest[i]; i++);
    for (j = 0; source[j]; j++)
    {
        dest[i + j] = source[j];   
    }
    dest[i + j] = 0;
    return dest;
}

uint _strlen(const char* str)
{
    uint len;
    for (len = 0; str[len]; len++);
    return len;
}