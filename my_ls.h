#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

#define FILENAME_SEP "  "
#define PATH_SEP "/"
#define CURRENT_DIR "."
#define NEWLINE '\n'
#define INVALID_ARG_MESSAGE "my_ls: cannot access '%s': No such file or directory\n"

#ifndef STRUCT_STAT
#define STRUCT_STAT
typedef struct stat Stat;
#endif

#ifndef STRUCT_DIRENT
#define STRUCT_DIRENT
typedef struct dirent Dirent;
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
void update_operand_counts(Operands* operands, const FileNode* node);
void update_links(Operands* operands, FileNode* node);
void split_operands(const Operands* operands, FileArray* directories, FileArray* nondirectories);

File* get_file_from_stat(const Stat* fileStat, char* path);
FileNode* get_file_node(const Stat* fileStat, char* path);
FileArray* initialize_file_array(FileArray* files, uint size);

//sorting
FileArray* sort(FileArray* files, bool time);
void sort_partitions(const FileArray* whole, uint i, bool time);
bool file_lower_than(const File* f1, const File* f2, bool time);
bool file_path_lower_than(const File* f1, const File* f2);
bool file_time_lower_than(const File* f1, const File* f2);
bool string_lower_than(const char* s1, const char* s2);
void swap(File** f1, File** f2);

void print(FileArray* files, bool timesort);
void print_dirs(FileArray* directories, bool nondirs, bool timesort);
void print_directory_content(const File* directory, bool timesort);
void print_newline();

//strings
char* build_path(char* fullpath, const char* dirpath, const char* name);
char* _strcpy(char* dest, const char* source);
char* _strcat(char* dest, const char* source);
uint _strlen(const char* str);

//free
void free_operands(const Operands* operands);

//errors
int operand_error(const char* path, const Operands* operands);
