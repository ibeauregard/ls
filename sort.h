#ifndef SORT_H
#define SORT_H

#include <stdbool.h>
#include "file_array.h"

typedef bool SortKey(const File*, const File*);

FileArray* sort(FileArray* files, SortKey* key);
#endif
