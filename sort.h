#include "file.h"
#include "file_array.h"

FileArray* sort(FileArray* files, bool time);
void sort_partitions(const FileArray* whole, uint i, bool time);
bool file_lower_than(const File* f1, const File* f2, bool time);
bool file_path_lower_than(const File* f1, const File* f2);
bool file_time_lower_than(const File* f1, const File* f2);
bool string_lower_than(const char* s1, const char* s2);
void swap(File** f1, File** f2);