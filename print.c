#include "print.h"
#include "_string.h"
#include "sort.h"
#include <stdio.h>
#include <dirent.h>

static void print_files(FileArray* files, bool timesort);
static void print_directories(FileArray* dirs, bool nondirs, Options* options);
static void print_dircontent(const File* directory, Options* options);
static uint count_files(const File* directory);
static void parse_folder(DIR* folder, const char* path, uint n_files, bool show_hidden, FileArray* output);
static void print_newline();
static char* build_path(char* fullpath, const char* dirpath, const char* name);
static bool file_time_lower_than(const File* f1, const File* f2);
static bool file_path_lower_than(const File* f1, const File* f2);
static SortKey* sort_key(bool timesort);

void print(FileArray* files, FileArray* directories, Options* options)
{
    print_files(files, options->t);
    print_directories(directories, files->size, options);
    free(options);
}

static void print_files(FileArray* files, bool timesort)
{
    sort(files, sort_key(timesort));
    uint i;
    for (i = 0; i < files->size; i++)
    {
        printf("%s%s", files->array[i]->path, FILENAME_SEP);
        free(files->array[i]);
    }
    free(files->array);
    if (i)
    {
        print_newline();
    }
}

static void print_directories(FileArray* dirs, bool nondirs, Options* options)
{
    if (nondirs && dirs->size)
    {
        print_newline();
    }
    sort(dirs, sort_key(options->t));
    for (uint i = 0; i < dirs->size; i++)
    {
        if (nondirs || i >= 1)
        {
            printf("%s:\n", dirs->array[i]->path);
        }
        print_dircontent(dirs->array[i], options);
        free(dirs->array[i]);
        if (i < dirs->size - 1)
        {
            print_newline();
        }
    }
    free(dirs->array);
}

static void print_dircontent(const File* directory, Options* options)
{
    uint n_files = count_files(directory);
    FileArray files;
    DIR* folder = opendir(directory->path);
    parse_folder(folder, directory->path, n_files, options->a, &files);
    print_files(&files, options->t);
    closedir(folder);
}

static uint count_files(const File* directory)
{
    uint n_files;
    DIR* folder = opendir(directory->path);
    for (n_files = 0; readdir(folder); n_files++);
    closedir(folder);
    return n_files;
}

static void parse_folder(DIR* folder, const char* path, uint n_files, bool show_hidden, FileArray* output)
{
    Dirent* entry;
    uint i = 0;
    initialize_file_array(output, n_files);
    while ((entry = readdir(folder)))
    {
        if (starts_with(entry->d_name, HIDDEN_FILE_CHAR) && !show_hidden)
        {
            output->size--;
            continue;
        }
        Stat fileStat;
        char fullpath[_strlen(path)
                    + _strlen(PATH_SEP)
                    + _strlen(entry->d_name)
                    + 1];
        stat(build_path(fullpath, path, entry->d_name), &fileStat);
        output->array[i++] = get_file_from_stat(&fileStat, entry->d_name);
    }
}

static void print_newline()
{
    printf("%c", NEWLINE);
}

static char* build_path(char* fullpath, const char* dirpath, const char* name)
{
    return _strcat(_strcat(_strcpy(fullpath, dirpath), PATH_SEP), name);   
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

static SortKey* sort_key(bool timesort)
{
    return timesort ? &file_time_lower_than : &file_path_lower_than;
}