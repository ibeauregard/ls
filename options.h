#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

typedef struct
{
    bool a;
    bool t;
} Options;

Options* initialize_options();
#endif
