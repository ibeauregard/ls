#include <stdbool.h>

#ifndef STRUCT_OPTIONS
#define STRUCT_OPTIONS
typedef struct
{
    bool a;
    bool t;
} Options;
#endif

Options* initialize_options();