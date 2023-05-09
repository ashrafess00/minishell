#include "test_header.h"
#include <string.h>
int open_outfile(char *file)
{
    int fd;

    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    return (fd);
}

void ji(int fd)
{
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

int main(int argc, char **argv, char **envp)
{
    while (1)
    {
        char *s = readline("read_me\n");

        if (strcmp(s, "exit") == 0) {
            free(s);
            break;
        }

        int fd = open_outfile("aa");
        ji(fd);
        printf("hi-there\n");

        dup2(STDOUT_FILENO, fd);
        close(fd);
        free(s);
    }

    return 0;
}