#include "file_array.h"
#include <stdbool.h>

#define FILENAME_SEP "  "
#define PATH_SEP "/"
#define CURRENT_DIR "."
#define NEWLINE '\n'

#ifndef STRUCT_DIRENT
#define STRUCT_DIRENT
typedef struct dirent Dirent;
#endif

void print(FileArray* files, bool timesort);
void print_dirs(FileArray* directories, bool nondirs, bool timesort);