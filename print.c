#include "print.h"
#include "_string.h"
#include "sort.h"
#include <stdio.h>
#include <dirent.h>

static void print_nondirs (FileArray* files, bool timesort);
static void print_dirs(FileArray* directories, bool nondirs, bool timesort);
static void print_directory_content(const File* directory, bool timesort);
static void print_newline();
static char* build_path(char* fullpath, const char* dirpath, const char* name);

void print(FileArray* nondirectories, FileArray* directories, bool timesort)
{
    print_nondirs(nondirectories, timesort);
    print_dirs(directories, nondirectories->size, timesort);
}

static void print_nondirs(FileArray* files, bool timesort)
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

void print_dirs(FileArray* dirs, bool nondirs, bool timesort)
{
    if (nondirs && dirs->size)
    {
        print_newline();
    }
    sort(dirs, timesort);
    for (uint i = 0; i < dirs->size; i++)
    {
        if (nondirs || dirs->size > 1)
        {
            printf("%s:\n", dirs->array[i]->path);
        }
        print_directory_content(dirs->array[i], timesort);
        free(dirs->array[i]);
        if (i < dirs->size - 1)
        {
            print_newline();
        }
    }
    free(dirs->array);
}

static void print_directory_content(const File* directory, bool timesort)
{
    DIR* folder = opendir(directory->path);
    uint n_files;
    for (n_files = 0; readdir(folder); n_files++);
    closedir(folder);
    FileArray files;
    initialize_file_array(&files, n_files);
    folder = opendir(directory->path);
    for (uint i = 0; i < n_files; i++)
    {
        Dirent* entry = readdir(folder);
        Stat fileStat;
        stat(entry->d_name, &fileStat);
        char path[_strlen(directory->path)
                    + _strlen(PATH_SEP)
                    + _strlen(entry->d_name)
                    + 1];
        stat(build_path(path, directory->path, entry->d_name), &fileStat);
        files.array[i] = get_file_from_stat(&fileStat, entry->d_name);
    }
    print_nondirs(&files, timesort);
    closedir(folder);
}

static void print_newline()
{
    printf("%c", NEWLINE);
}

static char* build_path(char* fullpath, const char* dirpath, const char* name)
{
    return _strcat(_strcat(_strcpy(fullpath, dirpath), PATH_SEP), name);   
}