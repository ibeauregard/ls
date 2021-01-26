#ifndef PRINT_OPTIONS_H
#define PRINT_OPTIONS_H

#include "sort.h"
#include "options.h"
#include <stdbool.h>

typedef struct
{
    SortKey* sortKey;
    bool showHidden;
} PrintOptions;

PrintOptions* convert(Options* options);
#endif