#include "_string.h"
#include "sort.h"

static void swap(File** f1, File** f2);
static bool file_path_lower_than(const File* f1, const File* f2);
static bool file_time_lower_than(const File* f1, const File* f2);
static bool file_lower_than(const File* f1, const File* f2, bool time);
static void sort_partitions(const FileArray* whole, uint i, bool time);

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

static void sort_partitions(const FileArray* whole, uint i, bool time)
{
    FileArray partition = *whole;
    partition.size = i;
    sort(&partition, time);
    partition.size = whole->size - (i + 1);
    partition.array = whole->array + i + 1;
    sort(&partition, time);
}

static bool file_lower_than(const File* f1, const File* f2, bool time)
{
    if (time)
    {
        return file_time_lower_than(f1, f2);
    }
    return file_path_lower_than(f1, f2);
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

static void swap(File** f1, File** f2)
{
    File* temp = *f1;
    *f1 = *f2;
    *f2 = temp;
}
