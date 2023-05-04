#include "test_header.h"

int stln(char **nature, int i)
{
	int j = 0;
	while(nature[i][j] != '\0')
		j++;
	return(j);
}

char **my_env(char **nature)
{
	int i = 0;
	int l = 0;
	int j = 0;
	char **my_env;
	while(nature[i])
		i++;
	my_env = malloc(i * sizeof(char **));
	i =0;
	while(nature[i][j] != '\0')
	{
		j = 0;
		l = stln(nature, i) + 1;
		my_env[i] = malloc(l * sizeof(char *));
		while(nature[i][j] != '\0')
		{
			my_env[i][j] = nature[i][j];
			j++;
		}
		my_env[i][j] = '\0';
		i++;
	}
	return (my_env);
}

int main(int c, char **argv, char **env)
{
	char **new_env = my_env(env);
	//lenv dyalhoum
	int i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	printf("----------------------------------------------------\n----------------------------------------------------\n");
	//env dyalna
	i = 0;
	while (new_env[i])
	{
		printf("%s\n", new_env[i]);
		i++;
	}
}