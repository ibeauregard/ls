#include "operands.h"
#include <stdio.h>

static void update_operand_counts(Operands* operands, const FileNode* node);
static void update_links(Operands* operands, FileNode* node);
static void free_operands(const Operands* operands);

void initialize_operands(Operands* operands)
{
    operands->n_dirs = operands->n_nondirs = 0;
    operands->first = operands->last = NULL;
}

int handle_operand(char* path, Operands* operands)
{
    Stat fileStat;
    if (stat(path, &fileStat) < 0)
    {
        return EXIT_FAILURE;
    }
    FileNode* node = get_file_node(&fileStat, path);
    update_operand_counts(operands, node);
    update_links(operands, node);
    return EXIT_SUCCESS;
}

static void update_operand_counts(Operands* operands, const FileNode* node)
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

static void update_links(Operands* operands, FileNode* node)
{
    if (!operands->first)
    {
        operands->first = operands->last = node;
        return;
    }
    operands->last = operands->last->next = node;
}

void split_operands(const Operands* operands, FileArray* directories, FileArray* nondirectories)
{
    uint dirIndex = 0;
    uint nondirIndex = 0;
    FileNode* node = operands->first;
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

int operand_error(const char* path, const Operands* operands)
{
    fprintf(stderr, INVALID_ARG_MESSAGE, path);
    free_operands(operands);
    return EXIT_FAILURE;
}

static void free_operands(const Operands* operands)
{
    FileNode* node = operands->first;
    while (node)
    {
        free(node->file);
        FileNode* current = node;
        node = node->next;
        free(current);
    }
}