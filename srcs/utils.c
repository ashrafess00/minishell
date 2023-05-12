/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:58:16 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/12 12:26:57 by aessaoud         ###   ########.fr       */
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

char	*get_input_from_usr(char *limiter)
{
	char	*input;
	char	*s;

	input = ft_calloc(1, 1);
	while (1)
	{
		ft_printf("> ");
		s = get_next_line(0);
		if (!s)
			break ;
		if (!ft_strcmp(s, limiter))
			break ;
		input = ft_strjoin(input, s);
			
	}
	free(s);
	return (input);
}