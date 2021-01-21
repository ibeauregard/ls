#include <stdlib.h>
#include "file_node.h"

FileNode* get_file_node(const Stat* fileStat, char* path)
{
    FileNode* node = malloc(sizeof (FileNode));
    node->file = get_file_from_stat(fileStat, path);
    node->next = NULL;
    return node;
}