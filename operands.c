#include "operands.h"
#include "_string.h"
#include <stdio.h>

static int _parse_arguments(int n_arguments, char** arguments, Operands* operands);
static Operands* initialize_operands(Operands* operands);
static int handle_argument(char* path, Operands* operands);
static int handle_option(char* option, Operands* operands);
static void update_operand_counts(Operands* operands, const FileNode* node);
static void update_links(Operands* operands, FileNode* node);
static int operand_error(const char* operand, const Operands* operands);
static int option_error(char option, const Operands* operands);
static void free_operands(const Operands* operands);

int parse_arguments(int n_arguments, char** arguments, Operands* operands)
{
    return _parse_arguments(n_arguments, arguments, initialize_operands(operands));
}

static int _parse_arguments(int n_arguments, char** arguments, Operands* operands)
{
    for (int i = 0; i < n_arguments; i++)
    {
        if (handle_argument(arguments[i], operands))
        {
            return EXIT_FAILURE;
        }
    }
    if (operands->n_dirs + operands->n_nondirs == 0)
    {
        char* arguments[1] = {CURRENT_DIR};
        return _parse_arguments(1, arguments, operands);
    }
    return EXIT_SUCCESS;
}

static Operands* initialize_operands(Operands* operands)
{
    operands->options = initialize_options();
    operands->n_dirs = operands->n_nondirs = 0;
    operands->first = operands->last = NULL;
    return operands;
}

static int handle_argument(char* argument, Operands* operands)
{
    if (starts_with(argument, OPTION_ID) && _strlen(argument) > 1)
    {
        return handle_option(argument + 1, operands);   
    }
    Stat fileStat;
    if (stat(argument, &fileStat) < 0)
    {
        return operand_error(argument, operands);
    }
    FileNode* node = get_file_node(&fileStat, argument);
    update_operand_counts(operands, node);
    update_links(operands, node);
    return EXIT_SUCCESS;
}

static int handle_option(char* option, Operands* operands)
{
    if (!option[0])
    {
        return EXIT_SUCCESS;
    }
    switch (option[0])
    {
        case 'a':
            operands->options->a = true;
            return handle_option(option + 1, operands);
        case 't':
            operands->options->t = true;
            return handle_option(option + 1, operands);
        default:
            return option_error(option[0], operands);
    }
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

static int operand_error(const char* operand, const Operands* operands)
{
    fprintf(stderr, INVALID_OPERAND_MESSAGE, operand);
    free_operands(operands);
    return EXIT_FAILURE;
}

static int option_error(char option, const Operands* operands)
{
    fprintf(stderr, INVALID_OPTION_MESSAGE, option);
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
    free(operands->options);
}