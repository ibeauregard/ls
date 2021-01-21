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

void initialize_operands(Operands* operands);
int handle_operand(char* path, Operands* operands);
void split_operands(const Operands* operands, FileArray* directories, FileArray* nondirectories);
int operand_error(const char* path, const Operands* operands);
