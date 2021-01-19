#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME_SEP '\t'
#define INVALID_ARG_MESSAGE "my_ls: cannot access '%s': No such file or directory\n"

#ifndef STRUCT_STAT
#define STRUCT_STAT
typedef struct stat Stat;
#endif

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct
{
    uint size;
    char** array;
} StringArray;
#endif

#ifndef STRUCT_FILE
#define STRUCT_FILE
typedef struct
{
    char* name;
    bool isdir;
    struct timespec mtim;
} File;
#endif

#ifndef STRUCT_FILE_NODE
#define STRUCT_FILE_NODE
typedef struct s_file_node
{
    File* file;
    struct s_file_node* next;
} FileNode;
#endif

#ifndef STRUCT_OPERANDS
#define STRUCT_OPERANDS
typedef struct
{
    uint n_dirs;
    uint n_nondirs;
    FileNode* first; 
} Operands;
#endif

Operands* initialize_operands();
File* get_file_from_stat(Stat fileStat, char* name);
void print(StringArray list);
StringArray sort(StringArray list);
void sort_partitions(StringArray list, uint i);
bool lower_than(char* s1, char* s2);
void swap(char** p1, char** p2);
