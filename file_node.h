#include "file.h"

#ifndef STRUCT_FILE_NODE
#define STRUCT_FILE_NODE
typedef struct s_file_node
{
    File* file;
    struct s_file_node* next;
} FileNode;
#endif

FileNode* get_file_node(const Stat* fileStat, char* path);
