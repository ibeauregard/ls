#include "my_list.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    Stat fileStat;
    Operands operands;
    operands.n_dirs = operands.n_nondirs = 0;
    operands.first = NULL;
    FileNode *lastSeen = NULL;
    for (int i = 1; i < argc; i++)
    {
        if (stat(argv[i], &fileStat) < 0)
        {
            fprintf(stderr, INVALID_ARG_MESSAGE, argv[i]);
            return 1;
        }
        FileNode* node = malloc(sizeof (FileNode));
        node->file = get_file_from_stat(fileStat, argv[i]);
        node->next = NULL;
        if (node->file->isdir)
        {
            operands.n_dirs++;
        }
        else
        {
            operands.n_nondirs++;
        }
        if (!operands.first)
        {
            operands.first = node;
            lastSeen = node;
        }
        else
        {
            lastSeen = lastSeen->next = node;
        }
    }
    printf("No of dirs: %u; no of nondirs: %u\n", operands.n_dirs, operands.n_nondirs);
    File *directories[operands.n_dirs], *nondirectories[operands.n_nondirs];
    uint dirIndex = 0, nondirIndex = 0;
    FileNode* node = operands.first;
    while (node)
    {
        if (node->file->isdir)
        {
            printf("Adding %s to directories at index %u\n", node->file->name, dirIndex);
            directories[dirIndex++] = node->file;
        }
        else
        {
            printf("Adding %s to non-directories at index %u\n", node->file->name, nondirIndex);
            nondirectories[nondirIndex++] = node->file;
        }
        FileNode* current = node;
        node = node->next;
        free(current);
    }
    printf("Final dir index: %u\n", dirIndex);
    printf("Final nondir index: %u\n", nondirIndex);
    for (uint i = 0; i < dirIndex; i++)
    {
        printf("Directory %s\n", directories[i]->name);
        free(directories[i]);
    }
    for (uint i = 0; i < nondirIndex; i++)
    {
        printf("Non-directory %s\n", nondirectories[i]->name);
        free(nondirectories[i]);
    }
    puts("");
    return 0;
}

File* get_file_from_stat(Stat fileStat, char* name)
{
    File* file = malloc(sizeof (File));
    file->name = name;
    file->isdir = S_ISDIR(fileStat.st_mode);
    file->mtim = fileStat.st_mtim;
    return file;
}

void print(StringArray list)
{
    for (uint i = 0; i < list.size; i++)
    {
        printf("%s%c", list.array[i], FILENAME_SEP);
    }
}

StringArray sort(StringArray list)
{
    if (list.size <= 1)
    {
        return list;
    }
    int i = 0;
    char* pivot = list.array[list.size - 1];
    for (uint j = 0; j < list.size - 1; j++)
    {
        if (lower_than(list.array[j], pivot))
        {
            swap(&list.array[i], &list.array[j]);
            i++;
        }
    }
    swap(&list.array[i], &list.array[list.size - 1]);
    sort_partitions(list, i);
    return list;
}

void sort_partitions(StringArray list, uint i)
{
    StringArray partition;
    partition.size = i;
    partition.array = list.array;
    sort(partition);
    partition.size = list.size - (i + 1);
    partition.array = list.array + i + 1;
    sort(partition);
}

bool lower_than(char* s1, char* s2)
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