#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

#define FILENAME_SEP "  "
#define PATH_SEP "/"
#define CURRENT_DIR "."
#define INVALID_ARG_MESSAGE "my_ls: cannot access '%s': No such file or directory\n"

#ifndef STRUCT_STAT
#define STRUCT_STAT
typedef struct stat Stat;
#endif

#ifndef STRUCT_DIRENT
#define STRUCT_DIRENT
typedef struct dirent Dirent;
#endif

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct
{
    uint size;
    char** array;
} StringArray;
#endif

#ifndef STRUCT_FILE
#define STRUCT_FILE
typedef struct
{
    char* path;
    bool isdir;
    struct timespec mtim;
} File;
#endif

#ifndef STRUCT_FILE_ARRAY
#define STRUCT_FILE_ARRAY
typedef struct
{
    uint size;
    File** array;
} FileArray;
#endif

#ifndef STRUCT_FILE_NODE
#define STRUCT_FILE_NODE
typedef struct s_file_node
{
    File* file;
    struct s_file_node* next;
} FileNode;
#endif

#ifndef STRUCT_OPERANDS
#define STRUCT_OPERANDS
typedef struct
{
    uint n_dirs;
    uint n_nondirs;
    FileNode* first;
    FileNode* last;
} Operands;
#endif

int my_ls(int n_arguments, char**arguments);

// operand parsing
void initialize_operands(Operands* operands);
int handle_operand(char* path, Operands* operands);
void update_operand_counts(Operands* operands, FileNode* node);
void update_links(Operands* operands, FileNode* node);
void split_operands(Operands* operands, FileArray* directories, FileArray* nondirectories);

File* get_file_from_stat(Stat* fileStat, char* path);
FileNode* get_file_node(Stat* fileStat, char* path);
FileArray* initialize_file_array(FileArray* files, uint size);

//sorting
FileArray* sort(FileArray* files, bool time);
void sort_partitions(FileArray* whole, uint i, bool time);
bool file_lower_than(File* f1, File* f2, bool time);
bool file_path_lower_than(File* f1, File* f2);
bool file_time_lower_than(File* f1, File* f2);
bool string_lower_than(char* s1, char* s2);
void swap(File** f1, File** f2);

void print(FileArray* files, bool timesort);
void print_dirs(FileArray* directories, bool nondirs, bool timesort);
void print_directory_content(File* directory, bool timesort);

//strings
char* build_path(char* dirpath, char* name);
char* my_strcpy(char* dest, const char* source);
char* my_strcat(char* dest, const char* source);

//free
void free_operands(Operands* operands);
void free_all(FileArray* directories, FileArray* nondirectories);
void free_files(FileArray* files);

//errors
int operand_error(char* path, Operands* operands);
