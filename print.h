#ifndef PRINT_H
#define PRINT_H

#include "file_array.h"
#include "print_options.h"
#include <stdbool.h>

#define FILENAME_SEP "  "
#define PATH_SEP "/"
#define NEWLINE '\n'
#define HIDDEN_FILE_CHAR '.'

typedef struct dirent Dirent;

void print(FileArray* dircontent, FileArray* directories, PrintOptions* options);
#endif

