#include <stdbool.h>
#include "file_array.h"

#ifndef SORT_KEY
#define SORT_KEY
typedef bool SortKey(const File*, const File*);
#endif

FileArray* sort(FileArray* files, SortKey* key);