#include <stdio.h>
#include "my_ls.h"
#include "print.h"

int main(int argc, char** argv)
{
    return my_ls(argc - 1, argv + 1);
}

int my_ls(int n_arguments, char** arguments)
{
    if (!n_arguments)
    {
        char* arguments[1] = {CURRENT_DIR};
        return my_ls(1, arguments);
    }
    Operands operands;
    initialize_operands(&operands);
    for (int i = 0; i < n_arguments; i++)
    {
        if (handle_operand(arguments[i], &operands))
        {
            return operand_error(arguments[i], &operands);
        }
    }
    
    FileArray directories;
    FileArray nondirectories;
    split_operands(
        &operands,
        initialize_file_array(&directories, operands.n_dirs),
        initialize_file_array(&nondirectories, operands.n_nondirs)
    );
    print(&nondirectories, true);
    print_dirs(&directories, nondirectories.size, true);
    return EXIT_SUCCESS;
}

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

void update_operand_counts(Operands* operands, const FileNode* node)
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

void update_links(Operands* operands, FileNode* node)
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

void free_operands(const Operands* operands)
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

int operand_error(const char* path, const Operands* operands)
{
    fprintf(stderr, INVALID_ARG_MESSAGE, path);
    free_operands(operands);
    return EXIT_FAILURE;
}