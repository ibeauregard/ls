#include "options.h"
#include <stdlib.h>

Options* initialize_options()
{
    Options* options = malloc (sizeof (Options));
    options->a = options->t = false;
    return options;
}
