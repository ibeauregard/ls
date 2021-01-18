#include <stdio.h>

#define FILENAME_SEP '\t'

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        printf("%s%c", argv[i], FILENAME_SEP);
    }
    puts("");
    return 0;
}