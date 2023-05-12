


#include "test_header.h"

char	**expand_arr(char **arr, char *val)
{
	int		i;
	char	**new_expanded_arr;

	i = 0;
	if (!arr)
	{
		new_expanded_arr = ft_calloc(2, sizeof(char *));
		new_expanded_arr[0] = ft_strdup(val);
		return (new_expanded_arr);
	}
	while(arr[i])
		i++;
	i += 2;
	new_expanded_arr = malloc(i * sizeof(char *));
	i = 0;
	while(arr[i])
	{
		new_expanded_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_expanded_arr[i] = ft_strdup(val);
	i++;
	new_expanded_arr[i] = NULL;
	free(arr);
	return(new_expanded_arr);
}

int	main(int c, char **args, char **env)
{
	char	**l;

	l = NULL;
	l = expand_arr(l, "hi");
	int i = -1;
	while (l[++i])
		printf("[%s]\n", l[i]);
	printf("-----------------------\n");
	l = expand_arr(l, "mo");
	i = -1;
	while (l[++i])
		printf("[%s]\n", l[i]);
	printf("-----------------------\n");
	l = expand_arr(l, "ki");
	i = -1;
	while (l[++i])
		printf("[%s]\n", l[i]);
}