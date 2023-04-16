/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:47:49 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/16 20:49:50 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_env(t_token **head,  char *line, int *i, int *s_index, int size, char *q)
{
	if ((*q == 'c' || *q == '\"') && line[*i] == '$' && line[*i + 1] == '?')
	{
		cr_token(head, line, *s_index, size, NORMAL);
		cr_token(head, line, *i, 2, EXIT_STATUS);
		*i += 1;
		return (1);
	}
	if ((*q == 'c' || *q == '\"') && line[*i] == '$')
	{
		int si;
	
		si = 0;
		cr_token(head, line, *s_index, size, NORMAL);
		*s_index = *i;
		*i += 1;
		while (line[*i] != ' ' && line[*i] != '$' && line[*i] != '>'
		&& line[*i] != '<' && line[*i] != D_QUOTE
		&& line[*i] != S_QUOTE && line[*i])
		{
			si++;
			*i += 1;
		}
		cr_token(head, line, *s_index, si + 1, ENV);
		*i -= 1;
		return (1);
	}
	return (0);
}