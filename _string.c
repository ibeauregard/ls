#include "_string.h"

bool starts_with(const char* str, char c)
{
    return str && str[0] == c;
}

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

bool string_lower_than(const char* s1, const char* s2)
{
    for (; *s1 && *s2 && *s1 == *s2; s1++, s2++);
    return *s1 < *s2;
}
