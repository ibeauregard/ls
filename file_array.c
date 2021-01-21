#include "file_array.h"

FileArray* initialize_file_array(FileArray* files, uint size)
{
    files->size = size;
    files->array = malloc(size * sizeof (File*));
    return files;
}