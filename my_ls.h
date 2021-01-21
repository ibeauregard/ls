#include <stdbool.h>
#include <dirent.h>
#include "file_array.h"
#include "file_node.h"

#define FILENAME_SEP "  "
#define PATH_SEP "/"
#define CURRENT_DIR "."
#define NEWLINE '\n'
#define INVALID_ARG_MESSAGE "my_ls: cannot access '%s': No such file or directory\n"

#ifndef STRUCT_DIRENT
#define STRUCT_DIRENT
typedef struct dirent Dirent;
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

void print(FileArray* files, bool timesort);
void print_dirs(FileArray* directories, bool nondirs, bool timesort);
void print_directory_content(const File* directory, bool timesort);
void print_newline();

//strings
char* build_path(char* fullpath, const char* dirpath, const char* name);

//free
void free_operands(const Operands* operands);

//errors
int operand_error(const char* path, const Operands* operands);
