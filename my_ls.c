#include "operands.h"
#include "file_array.h"
#include "print.h"

int my_ls(int n_arguments, char** arguments)
{
    if (!n_arguments)
    {
        char* arguments[1] = {CURRENT_DIR};
        return my_ls(1, arguments);
    }
    Operands operands;
    initialize_operands(&operands);
    for (int i = 0; i < n_arguments; i++)
    {
        if (handle_operand(arguments[i], &operands))
        {
            return operand_error(arguments[i], &operands);
        }
    }
    FileArray directories;
    FileArray nondirectories;
    split_operands(
        &operands,
        initialize_file_array(&directories, operands.n_dirs),
        initialize_file_array(&nondirectories, operands.n_nondirs)
    );
    print(&nondirectories, &directories, true);
    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    return my_ls(argc - 1, argv + 1);
}