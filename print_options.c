#include "print_options.h"
#include "_string.h"

static bool file_time_lower_than(const File* f1, const File* f2);
static bool file_path_lower_than(const File* f1, const File* f2);

PrintOptions* convert(Options* options)
{
    PrintOptions* printOptions = malloc(sizeof (PrintOptions));
    printOptions->showHidden = options->a;
    printOptions->sortKey = options->t ? file_time_lower_than : file_path_lower_than;
    free(options);
    return printOptions;
}

static bool file_time_lower_than(const File* f1, const File* f2)
{
    if (f1->mtim.tv_sec == f2->mtim.tv_sec)
    {
        if (f1->mtim.tv_nsec == f2->mtim.tv_nsec)
        {
            return file_path_lower_than(f1, f2);
        }
        return f1->mtim.tv_nsec > f2->mtim.tv_nsec;
    }
    return f1->mtim.tv_sec > f2->mtim.tv_sec;
}

static bool file_path_lower_than(const File* f1, const File* f2)
{
    return string_lower_than(f1->path, f2->path);
}