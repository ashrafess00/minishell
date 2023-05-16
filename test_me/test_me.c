
#include "test_header.h"



int	main(int c, char **args, char **env)
{
	char *s;
	while (1)
	{
		char *input = readline(">");
		add_history(input);
		s = remove_quotes(input);
		printf("%s\n", s);
	}
}