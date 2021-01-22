#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>

#ifndef STRUCT_STAT
#define STRUCT_STAT
typedef struct stat Stat;
#endif

#ifndef STRUCT_FILE
#define STRUCT_FILE
typedef struct
{
    char* path;
    bool isdir;
    struct timespec mtim;
} File;
#endif

File* get_file(const Stat* fileStat, char* path);