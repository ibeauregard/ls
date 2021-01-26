#ifndef FILE_ARRAY_H
#define FILE_ARRAY_H

#include <stdlib.h>
#include "file.h"

typedef unsigned int uint;

typedef struct
{
    uint size;
    File** array;
} FileArray;

FileArray* initialize_file_array(FileArray* files, uint size);
#endif
