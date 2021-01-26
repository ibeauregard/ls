#ifndef FILE_H
#define FILE_H

#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>

#if defined(__APPLE__) || defined(__NetBSD__)
#define st_mtim st_mtimespec
#endif

typedef struct stat Stat;

typedef struct
{
    char* path;
    bool isdir;
    struct timespec mtim;
} File;

File* get_file(const Stat* fileStat, char* path);
#endif
