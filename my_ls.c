#include "my_list.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    string_array files;
    files.size = argc - 1;
    files.array = argv + 1;
    print(sorted(files));
    puts("");
    return 0;
}

void print(string_array list)
{
    for (uint i = 0; i < list.size; i++)
    {
        printf("%s%c", list.array[i], FILENAME_SEP);
    }
}

string_array sorted(string_array list)
{
    if (list.size <= 1)
    {
        return list;
    }
    int i = 0;
    char* pivot = list.array[list.size - 1];
    for (uint j = 0; j < list.size - 1; j++)
    {
        if (smaller_than(list.array[j], pivot))
        {
            swap(&list.array[i], &list.array[j]);
            i++;
        }
    }
    swap(&list.array[i], &list.array[list.size - 1]);
    sort_partitions(list, i);
    return list;
}

void sort_partitions(string_array list, unsigned int i)
{
    string_array partition;
    partition.size = i;
    partition.array = list.array;
    sorted(partition);
    partition.size = list.size - (i + 1);
    partition.array = list.array + i + 1;
    sorted(partition);
}

bool smaller_than(char* s1, char* s2)
{
    for (; *s1 && *s2 && *s1 == *s2; s1++, s2++);
    return *s1 < *s2;
}

void swap(char** p1, char** p2)
{
    char* temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}