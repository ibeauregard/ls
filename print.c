#include "print.h"
#include "_string.h"
#include "sort.h"
#include <stdio.h>
#include <dirent.h>

static void print_files(FileArray* files, bool timesort);
static void print_directories(FileArray* directories, bool nondirs, bool timesort);
static void print_dircontent(const File* directory, bool timesort);
static uint get_num_files_in_dir(const File* directory);
static void parse_folder(DIR* folder, const char* path, uint n_files, FileArray* output);
static void print_newline();
static char* build_path(char* fullpath, const char* dirpath, const char* name);

void print(FileArray* dircontent, FileArray* directories, Options* options)
{
    print_files(dircontent, options->t);
    print_directories(directories, dircontent->size, options->t);
    free(options);
}

static void print_files(FileArray* files, bool timesort)
{
    sort(files, timesort);
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

static void print_directories(FileArray* dirs, bool nondirs, bool timesort)
{
    if (nondirs && dirs->size)
    {
        print_newline();
    }
    sort(dirs, timesort);
    for (uint i = 0; i < dirs->size; i++)
    {
        if (nondirs || i >= 1)
        {
            printf("%s:\n", dirs->array[i]->path);
        }
        print_dircontent(dirs->array[i], timesort);
        free(dirs->array[i]);
        if (i < dirs->size - 1)
        {
            print_newline();
        }
    }
    free(dirs->array);
}

static void print_dircontent(const File* directory, bool timesort)
{
    uint n_files = get_num_files_in_dir(directory);
    FileArray files;
    DIR* folder = opendir(directory->path);
    parse_folder(folder, directory->path, n_files, &files);
    print_files(&files, timesort);
    closedir(folder);
}

static uint get_num_files_in_dir(const File* directory)
{
    uint n_files;
    DIR* folder = opendir(directory->path);
    for (n_files = 0; readdir(folder); n_files++);
    closedir(folder);
    return n_files;
}

static void parse_folder(DIR* folder, const char* path, uint n_files, FileArray* output)
{
    initialize_file_array(output, n_files);
    for (uint i = 0; i < n_files; i++)
    {
        Dirent* entry = readdir(folder);
        Stat fileStat;
        stat(entry->d_name, &fileStat);
        char fullpath[_strlen(path)
                    + _strlen(PATH_SEP)
                    + _strlen(entry->d_name)
                    + 1];
        stat(build_path(fullpath, path, entry->d_name), &fileStat);
        output->array[i] = get_file_from_stat(&fileStat, entry->d_name);
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