#ifndef FILE_NODE_H
#define FILE_NODE_H

#include "file.h"

typedef struct s_file_node
{
    File* file;
    struct s_file_node* next;
} FileNode;

FileNode* get_file_node(const Stat* fileStat, char* path);
#endif
