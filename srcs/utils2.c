/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 08:58:34 by kslik             #+#    #+#             */
/*   Updated: 2023/05/23 22:12:57 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (arr[i])
		i++;
	i += 2;
	new_expanded_arr = malloc(i * sizeof(char *));
	i = 0;
	while (arr[i])
	{
		new_expanded_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_expanded_arr[i] = ft_strdup(val);
	i++;
	new_expanded_arr[i] = NULL;
	free_arr(arr);
	return (new_expanded_arr);
}

static char	*cr_new_str(char *s, int indexes[2])
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

static char	*remove_quotes(char *s, int indexes[2],
	int *i, t_quotes *quote_stat)
{
	char	*new_s;

	new_s = NULL;
	if ((s[*i] == DOUBLE_QUOTE || s[*i] == SINGLE_QUOTE)
		&& *quote_stat == CLOSED_QUOTE)
	{
		indexes[0] = *i;
		*quote_stat = s[*i];
	}
	else if ((s[*i] == DOUBLE_QUOTE && *quote_stat == DOUBLE_QUOTE)
		|| (s[*i] == SINGLE_QUOTE && *quote_stat == SINGLE_QUOTE))
		indexes[1] = *i;
	if (indexes[0] != -1 && indexes[1] != -1)
	{
		new_s = cr_new_str(s, indexes);
		*quote_stat = CLOSED_QUOTE;
		indexes[0] = -1;
		indexes[1] = -1;
		*i -= 2;
		return (new_s);
	}
	return (s);
}

char	*get_removed_quotes_str(char *s)
{
	int			i;
	t_quotes	quote_stat;
	int			indexes[2];

	i = -1;
	quote_stat = CLOSED_QUOTE;
	indexes[0] = -1;
	indexes[1] = -1;
	while (s[++i])
		s = remove_quotes(s, indexes, &i, &quote_stat);
	if (indexes[0] != -1 && indexes[1] == -1)
	{
		free (s);
		return (NULL);
	}
	return (s);
}
