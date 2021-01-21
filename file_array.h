#include <stdlib.h>
#include "file.h"

#ifndef STRUCT_FILE_ARRAY
#define STRUCT_FILE_ARRAY
typedef struct
{
    uint size;
    File** array;
} FileArray;
#endif

FileArray* initialize_file_array(FileArray* files, uint size);