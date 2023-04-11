/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:47:49 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/11 21:16:26 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_pipe(char *s, char q)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (s[0] == '|')
	{
		count += 1;
		while (s[++i])
		{
			if (s[i] == '|')
				count ++;
			if (count == 2 && q == 'c')
			{
				printf("syntax error\n");
                exit(0);
				return (0);
			}
			if (s[i] != ' ')
				return (1);
		}
	}
	return (0);
}