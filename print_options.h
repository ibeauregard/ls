#include "sort.h"
#include "options.h"
#include <stdbool.h>

#ifndef STRUCT_PRINT_OPTIONS
#define STRUCT_PRINT_OPTIONS
typedef struct
{
    SortKey* sortKey;
    bool showHidden;
} PrintOptions;
#endif

PrintOptions* convert(Options* options);