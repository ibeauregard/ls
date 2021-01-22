#include "operands.h"
#include "file_array.h"
#include "print_options.h"
#include "print.h"

int my_ls(int n_arguments, char** arguments)
{
    Operands operands;
    if (parse_arguments(n_arguments, arguments, &operands))
    {
        return EXIT_FAILURE;
    }
    FileArray directories;
    FileArray dircontent;
    split_operands(
        &operands,
        initialize_file_array(&directories, operands.n_dirs),
        initialize_file_array(&dircontent, operands.n_nondirs)
    );
    print(&dircontent, &directories, convert(operands.options));
    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    return my_ls(argc - 1, argv + 1);
}