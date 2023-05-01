#include "test_header.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int fds[2];

void    fun2()
{
    int f;

    f = fork();
    if (f == 0)
    {
        char *s = ft_calloc(100, 1);
        close(fds[1]);
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);
        execvp("sort", NULL);
    }
}

void    fun1()
{
    int f;

    f = fork();
    if (f == 0)
    {
        close(fds[0]);
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);
        execvp("cat", NULL);
    }

}

int main()
{
    pipe(fds);
    fun1();
    fun2();
}