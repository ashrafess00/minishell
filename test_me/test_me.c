#include "test_header.h"


int main(int c, char **argv)
{

	int f = open("tt", O_WRONLY, 0644);

	dup2(f, STDOUT_FILENO);
	printf("hi %d", f);

	// int ff = open("tt2", O_WRONLY, 0644);
	// dup2(ff, STDOUT_FILENO);
	// printf("hi %d\n", f);
}