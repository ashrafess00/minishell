/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:58:16 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/09 22:25:39 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_strcmp(char *s, char *limiter)
{
	int	i;
	int	s_len;
	int	limiter_len;

	s_len = ft_strlen(s);
	limiter_len = ft_strlen(limiter);
	i = 0;
	while (s[i] || limiter[i])
	{
		if (limiter[i] == '\0' && s[i] == '\n')
			return (0);
		if (limiter[i] != s[i])
			return (1);
		i++;
	}
	return (0);
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
}