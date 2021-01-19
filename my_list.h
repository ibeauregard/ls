#include <stdbool.h>
#include <stdlib.h>

#define FILENAME_SEP '\t'

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array
{
    uint size;
    char** array;
} string_array;
#endif

void print(string_array list);
string_array sort(string_array list);
void sort_partitions(string_array list, unsigned int i);
bool lower_than(char* s1, char* s2);
void swap(char** p1, char** p2);
