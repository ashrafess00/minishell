/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 08:58:34 by kslik             #+#    #+#             */
/*   Updated: 2023/05/13 20:13:31 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
	int m;
	char **my_env;
	while(nature[i])
		i++;
	my_env = malloc(i * sizeof(char **));
	m = i;
	i =0;
	while(i < m)
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

int strlne(char *line)
{
	int i = 0;
	while(line[i])
		i++;
	return(i);
}

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
	free_arr(arr);
	return(new_expanded_arr);
}