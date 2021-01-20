#include "my_ls.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    Operands operands;
    initialize_operands(&operands);
    FileNode* last = NULL;
    for (int i = 1; i < argc; i++)
    {
        if (handle_operand(argv[i], &operands, &last))
        {
            return operand_error(argv[i], &operands);
        }
    }
    
    FileArray directories;
    FileArray nondirectories;
    split_operands(
        &operands,
        initialize_file_array(&directories, operands.n_dirs),
        initialize_file_array(&nondirectories, operands.n_nondirs)
    );
    print(sort(&nondirectories, false));
    if (nondirectories.size && directories.size)
    {
        puts("");
    }
    print_dirs(sort(&directories, false), false);
    return EXIT_SUCCESS;
}

void initialize_operands(Operands* operands)
{
    operands->n_dirs = operands->n_nondirs = 0;
    operands->first = NULL;
}

int handle_operand(char* path, Operands* operands, FileNode** last)
{
    Stat fileStat;
    if (stat(path, &fileStat) < 0)
    {
        return EXIT_FAILURE;
    }
    FileNode* node = get_file_node(&fileStat, path);
    update_operand_counts(operands, node);
    update_links(operands, last, node);
    return EXIT_SUCCESS;
}

void update_operand_counts(Operands* operands, FileNode* node)
{
    if (node->file->isdir)
    {
        operands->n_dirs++;
    }
    else
    {
        operands->n_nondirs++;
    }
}

void update_links(Operands* operands, FileNode** last, FileNode* node)
{
    if (!operands->first)
    {
        operands->first = node;
        *last = node;
    }
    else
    {
        *last = (*last)->next = node;
    }
}

void split_operands(Operands* operands, FileArray* directories, FileArray* nondirectories)
{
    uint dirIndex = 0;
    uint nondirIndex = 0;
    FileNode* node = operands->first;
    while (node)
    {
        if (node->file->isdir)
        {
            directories->array[dirIndex++] = node->file;
        }
        else
        {
            nondirectories->array[nondirIndex++] = node->file;
        }
        FileNode* current = node;
        node = node->next;
        free(current);
    }
}

File* get_file_from_stat(Stat* fileStat, char* path)
{
    File* file = malloc(sizeof (File));
    file->path = path;
    file->isdir = S_ISDIR(fileStat->st_mode);
    file->mtim = fileStat->st_mtim;
    return file;
}

FileNode* get_file_node(Stat* fileStat, char* path)
{
    FileNode* node = malloc(sizeof (FileNode));
    node->file = get_file_from_stat(fileStat, path);
    node->next = NULL;
    return node;
}

FileArray* initialize_file_array(FileArray* files, uint size)
{
    files->size = size;
    files->array = malloc(size * sizeof (File*));
    return files;
}

FileArray* sort(FileArray* files, bool time)
{
    if (files->size <= 1)
    {
        return files;
    }
    uint i = 0;
    File* pivot = files->array[files->size - 1];
    for (uint j = 0; j < files->size - 1; j++)
    {
        if (file_lower_than(files->array[j], pivot, time))
        {
            swap(&files->array[i++], &files->array[j]);
        }
    }
    swap(&files->array[i], &files->array[files->size - 1]);
    sort_partitions(files, i, time);
    return files;
}

void sort_partitions(FileArray* whole, uint i, bool time)
{
    FileArray partition = *whole;
    partition.size = i;
    sort(&partition, time);
    partition.size = whole->size - (i + 1);
    partition.array = whole->array + i + 1;
    sort(&partition, time);
}

bool file_lower_than(File* f1, File* f2, bool time)
{
    if (time)
    {
        return file_time_lower_than(f1, f2);
    }
    return file_path_lower_than(f1, f2);
}

bool file_path_lower_than(File* f1, File* f2)
{
    return string_lower_than(f1->path, f2->path);
}

bool file_time_lower_than(File* f1, File* f2)
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

bool string_lower_than(char* s1, char* s2)
{
    for (; *s1 && *s2 && *s1 == *s2; s1++, s2++);
    return *s1 < *s2;
}

void swap(File** f1, File** f2)
{
    File* temp = *f1;
    *f1 = *f2;
    *f2 = temp;
}

void print(FileArray* files)
{
    uint i;
    for (i = 0; i < files->size; i++)
    {
        printf("%s%s", files->array[i]->path, FILENAME_SEP);
        free(files->array[i]);
    }
    free(files->array);
    if (i)
    {
        puts("");
    }
}

void print_dirs(FileArray* dirs, bool timesort)
{
    for (uint i = 0; i < dirs->size; i++)
    {
        print_directory_content(dirs->array[i], timesort);
        free(dirs->array[i]);
        if (i < dirs->size - 1)
        {
            puts("");
        }
    }
    free(dirs->array);
}

void print_directory_content(File* directory, bool timesort)
{
    printf("%s:\n", directory->path);
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
        //char* path = get_path(directory.path, entry->d_name);
        //printf("STAT %d\n", stat(path, &fileStat));
        //free(path);
        files.array[i] = get_file_from_stat(&fileStat, entry->d_name);
    }
    print(sort(&files, timesort));
    closedir(folder);
}

// char* get_path(char* dirpath, char* name)
// {
    
// }

void free_operands(Operands* operands)
{
    FileNode* node = operands->first;
    while (node)
    {
        free(node->file);
        FileNode* current = node;
        node = node->next;
        free(current);
    }
}

int operand_error(char* path, Operands* operands)
{
    fprintf(stderr, INVALID_ARG_MESSAGE, path);
    free_operands(operands);
    return EXIT_FAILURE;
}