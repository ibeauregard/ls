#include "file_array.h"
#include "file_node.h"

#define INVALID_ARG_MESSAGE "my_ls: cannot access '%s': No such file or directory\n"

#ifndef STRUCT_OPERANDS
#define STRUCT_OPERANDS
typedef struct
{
    uint n_dirs;
    uint n_nondirs;
    FileNode* first;
    FileNode* last;
} Operands;
#endif

int parse_arguments(int n_arguments, char** arguments, Operands* operands);
void split_operands(const Operands* operands, FileArray* directories, FileArray* nondirectories);
