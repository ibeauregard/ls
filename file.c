#include <stdlib.h>
#include "file.h"

File* get_file(const Stat* fileStat, char* path)
{
    File* file = malloc(sizeof (File));
    file->path = path;
    file->isdir = S_ISDIR(fileStat->st_mode);
    file->mtim = fileStat->st_mtim;
    return file;
}