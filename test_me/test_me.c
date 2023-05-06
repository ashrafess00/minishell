#include "test_header.h"


int main(int c, char **argv, char **env)
{
	char	s[100];
	getcwd(s, 100);
	printf("%s\n", s);
	chdir("~");
	getcwd(s, 100);
	printf("%s\n", s);
}