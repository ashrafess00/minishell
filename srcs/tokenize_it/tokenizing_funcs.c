/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 23:15:50 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/23 14:50:57 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_special_char(t_token **head, char *line, int *i, int *s_index, int size, char q)
{
	int	index;

	index = 0;
	if (q == 'c' && line[*i] == '|')
	{
		add_pipe_token(head, line, i, s_index, size);
		return (1);
	}
	else if (q == 'c' && line[*i] == '<' && line[*i + 1] == '<')
	{
		add_heredoc_token(head, line, i, s_index, size);
		return (1);
	}
	else if (q == 'c' && line[*i] == '>' && line[*i + 1] == '>')
	{
		add_red_append_token(head, line, i, s_index, size);
		return (1);
	}
	else if (q == 'c' && line[*i] == '>')
	{
		add_red_out_token(head, line, i, s_index, size);
		return (1);
	}
	else if (q == 'c' && line[*i] == '<')
	{
		add_red_inp_token(head, line, i, s_index, size);
		return (1);
	}
	return (0);
}


t_token	*lets_tokenize(char *line)
{
	t_token	*head;
	int		i;
	int		s_index;
	int		size;
	char	q;
	int		br;


	head = NULL;
	i = -1;
	q = 'c';
	s_index = 0;
	while (line[++i])
	{
		br = 0;
		size = 0;
		while(line[i] == ' ' && q == 'c' && line[i])
			i++;
		// if (line[i] == '\0')
		// 	break;
		s_index = i;
		while (line[i])
		{
			if (is_special_char(&head, line, &i, &s_index, size, q) == 1)
			{
				br = 1;
				break;
			}
			if (line[i] == ' ' && q == 'c')
				break;
			else if (line[i] == D_QUOTE && q != D_QUOTE && q != S_QUOTE)
				q = D_QUOTE;
			else if (line[i] == S_QUOTE && q != S_QUOTE && q != D_QUOTE)
				q = S_QUOTE;
			else if (line[i] == D_QUOTE && q == D_QUOTE)
				q = 'c';
			else if (line[i] == S_QUOTE && q == S_QUOTE)
				q = 'c';
			i++;
			size++;
		}
		if (!br)
			add_token(&head, line, s_index, size, NORMAL);
		if (!line[i])
			break ;
	}

	return (head);
}

