#include "my_ls.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    Operands operands;
    initialize_operands(&operands);
    FileNode* last = NULL;
    for (int i = 1; i < argc; i++)
    {
        if (handle_operand(argv[i], &operands, &last))
        {
            return operand_error(argv[i], operands);
        }
    }
    
    FileArray directories;
    FileArray nondirectories;
    split_operands(
        operands,
        initialize_file_array(&directories, operands.n_dirs),
        initialize_file_array(&nondirectories, operands.n_nondirs)
    );
    
    free_all(directories, nondirectories);
    return EXIT_SUCCESS;
}

void initialize_operands(Operands* operands)
{
    operands->n_dirs = operands->n_nondirs = 0;
    operands->first = NULL;
}

int handle_operand(char* path, Operands* operands, FileNode** last)
{
    Stat fileStat;
    if (stat(path, &fileStat) < 0)
    {
        return 1;
    }
    FileNode* node = get_file_node(fileStat, path);
    update_operand_counts(operands, node);
    update_links(operands, last, node);
    return 0;
}

void update_operand_counts(Operands* operands, FileNode* node)
{
    if (node->file->isdir)
    {
        operands->n_dirs++;
    }
    else
    {
        operands->n_nondirs++;
    }
}

void update_links(Operands* operands, FileNode** last, FileNode* node)
{
    if (!operands->first)
    {
        operands->first = node;
        *last = node;
    }
    else
    {
        *last = (*last)->next = node;
    }
}

void split_operands(Operands operands, FileArray* directories, FileArray* nondirectories)
{
    uint dirIndex = 0;
    uint nondirIndex = 0;
    FileNode* node = operands.first;
    while (node)
    {
        if (node->file->isdir)
        {
            directories->array[dirIndex++] = node->file;
        }
        else
        {
            nondirectories->array[nondirIndex++] = node->file;
        }
        FileNode* current = node;
        node = node->next;
        free(current);
    }
}

File* get_file_from_stat(Stat fileStat, char* path)
{
    File* file = malloc(sizeof (File));
    file->path = path;
    file->isdir = S_ISDIR(fileStat.st_mode);
    file->mtim = fileStat.st_mtim;
    return file;
}

FileNode* get_file_node(Stat fileStat, char* path)
{
    FileNode* node = malloc(sizeof (FileNode));
    node->file = get_file_from_stat(fileStat, path);
    node->next = NULL;
    return node;
}

FileArray* initialize_file_array(FileArray* files, uint size)
{
    files->size = size;
    files->array = malloc(size * sizeof (File*));
    return files;
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

void free_operands(Operands operands)
{
    FileNode* node = operands.first;
    while (node)
    {
        free(node->file);
        FileNode* current = node;
        node = node->next;
        free(current);
    }
}

void free_all(FileArray directories, FileArray nondirectories) 
{
    free_files(directories);
    free_files(nondirectories);
}

void free_files(FileArray files)
{
    for (uint i = 0; i < files.size; i++)
    {
        printf("Freeing file %s\n", files.array[i]->path);
        free(files.array[i]);
    }
    free(files.array);
}

int operand_error(char* path, Operands operands)
{
    fprintf(stderr, INVALID_ARG_MESSAGE, path);
    free_operands(operands);
    return EXIT_FAILURE;
}