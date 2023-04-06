#include "test_header.h"

int main()
{
    char *path = "/usr/bin/sort";
    char *argv[2] = {"sort", NULL};
    execve(path, argv, NULL);
}