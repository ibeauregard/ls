#include "file_array.h"
#include "print_options.h"
#include <stdbool.h>

#define FILENAME_SEP "  "
#define PATH_SEP "/"
#define NEWLINE '\n'
#define HIDDEN_FILE_CHAR '.'

#ifndef STRUCT_DIRENT
#define STRUCT_DIRENT
typedef struct dirent Dirent;
#endif

void print(FileArray* dircontent, FileArray* directories, PrintOptions* options);
