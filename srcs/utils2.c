/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 08:58:34 by kslik             #+#    #+#             */
/*   Updated: 2023/05/16 17:58:44 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int stln(char **nature, int i)
{
	int j = 0;
	while (nature[i][j] != '\0')
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

char	*cr_new_str(char *s, int indexes[2])
{
	char	*new_s;
	int		i;
	int		new_s_i;

	i = -1;
	new_s = ft_calloc(ft_strlen(s), sizeof(char));
	new_s_i = 0;
	while (s[++i])
	{
		if (i != indexes[0] && i != indexes[1])
		{
			new_s[new_s_i] = s[i];
			new_s_i++;
		}
	}
	free(s);
	return (new_s);
}

char	*remove_quotes(char *s)
{
	int			i;
	t_quotes	quote_stat;
	int			indexes[2];

	i = -1;
	quote_stat = CLOSED_QUOTE;
	indexes[0] = -1;
	indexes[1] = -1;
	while (s[++i])
	{
		if ((s[i] == DOUBLE_QUOTE || s[i] == SINGLE_QUOTE) && quote_stat == CLOSED_QUOTE)
		{
			indexes[0] = i;
			quote_stat = s[i];
		}
		else if (s[i] == DOUBLE_QUOTE && quote_stat == DOUBLE_QUOTE)
			indexes[1] = i;
		else if (s[i] == SINGLE_QUOTE && quote_stat == SINGLE_QUOTE)
			indexes[1] = i;
		if (indexes[0] != -1 && indexes[1] != -1)
		{
			s = cr_new_str(s, indexes);
			quote_stat = CLOSED_QUOTE;
			indexes[0] = -1;
			indexes[1] = -1;
			i -= 2;
		}
	}
	if (indexes[0] != -1 && indexes[1] == -1)
		return (NULL);
	return (s);
}