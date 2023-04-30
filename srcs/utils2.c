/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 08:58:34 by kslik             #+#    #+#             */
/*   Updated: 2023/04/30 12:08:26 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

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
int strlne(char *line)
{
	int i = 0;
	while(line[i])
		i++;
	return(i);
}
char **our_realloc(char **arr, char *new)
{
	int i = 0;
	int l = 0;
	int j = 0;
	int q;
	char **new_arr;
	while(arr[i] != '\0')
		i++;
	q = i;
	i += 1;
	new_arr = malloc(i * sizeof(char **));
	i = 0;
	while(i < q)
	{
		l = stln(arr, i) + 1;
		new_arr[i] = malloc(l * sizeof (char *));
		while(arr[i][j] != '\0')
		{
			new_arr[i][j] = arr[i][j];
			j++;
		}
		new_arr[i][j] = '\0';
		j = 0;
		i++;
	}
	l = strlne(new);
	j = 0;
	new_arr[i] = malloc(l * sizeof (char *));
	while(new[j] != '\0')
	{
		new_arr[i][j] = new[j];
		j++;
	}
	new_arr[i][j] = '\0';
	return(new_arr);
}
