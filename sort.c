#include "file.h"
#include "_string.h"
#include "sort.h"

static void swap(File** f1, File** f2);
static void sort_partitions(const FileArray* whole, uint i, SortKey* key);

FileArray* sort(FileArray* files, SortKey* key)
{
    if (files->size <= 1)
    {
        return files;
    }
    uint i = 0;
    File* pivot = files->array[files->size - 1];
    for (uint j = 0; j < files->size - 1; j++)
    {
        if (key(files->array[j], pivot))
        {
            swap(&files->array[i++], &files->array[j]);
        }
    }
    swap(&files->array[i], &files->array[files->size - 1]);
    sort_partitions(files, i, key);
    return files;
}

static void sort_partitions(const FileArray* whole, uint i, SortKey* key)
{
    FileArray partition = *whole;
    partition.size = i;
    sort(&partition, key);
    partition.size = whole->size - (i + 1);
    partition.array = whole->array + i + 1;
    sort(&partition, key);
}

static void swap(File** f1, File** f2)
{
    File* temp = *f1;
    *f1 = *f2;
    *f2 = temp;
}
