#include "file_array.h"
#include "file_node.h"
#include <stdbool.h>

#define CURRENT_DIR "."
#define OPTION_ID '-'
#define INVALID_OPERAND_MESSAGE "my_ls: cannot access '%s': No such file or directory\n"
#define INVALID_OPTION_MESSAGE "my_ls: invalid option -- '%c'\n"

#ifndef STRUCT_OPERANDS
#define STRUCT_OPERANDS
typedef struct
{
    bool a_option;
    bool t_option;
    uint n_dirs;
    uint n_nondirs;
    FileNode* first;
    FileNode* last;
} Operands;
#endif

int parse_arguments(int n_arguments, char** arguments, Operands* operands);
void split_operands(const Operands* operands, FileArray* directories, FileArray* nondirectories);
