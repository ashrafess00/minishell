/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 23:15:50 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/22 20:27:04 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	cr_token(t_token **head, char *s, int s_index, int size, enum e_token type)
{
	t_token	*new_dl;
	t_token	*last;

	if (size == 0)
		return ;
	new_dl = malloc(sizeof(t_token));
	last = *head;
	new_dl->s_index = s_index;
	new_dl->s = ft_substr(s + s_index, 0, size);
	//fl function dyalk siftliha (ft_substr(s + s_index, 0, size)), substr ghadi tjiblik string kif mma hwwa like ("ec"h"o"), new_dl->s khas ydkhl fiha (echo)
	new_dl->size = size;
	new_dl->type = type;
	new_dl->next = NULL;
	if (*head == NULL)
	{
		new_dl->prev = NULL;
		*head = new_dl;
	}
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_dl;
		new_dl->prev = last;
	}
}

int	is_special(t_token **head, char *line, int *i, int *s_index, int size, char *q)
{
	int	index;

	index = 0;
	if (*q == 'c' && line[*i] == '|')
	{
		cr_token(head, line, *s_index, size, NORMAL);
		cr_token(head, line, *i, 1, PIPE);
		return (1);
	}
	else if (*q == 'c' && line[*i] == '<' && line[*i + 1] == '<')
	{
		cr_token(head, line, *s_index, size, NORMAL);
		cr_token(head, line, *i, 2, HEREDOC);
		*i += 1;
		return (1);
	}
	else if (*q == 'c' && line[*i] == '>' && line[*i + 1] == '>')
	{
		cr_token(head, line, *s_index, size, NORMAL);
		cr_token(head, line, *i, 2, RED_OUTPUT_APPEND);
		*i += 1;
		return (1);
	}
	else if (*q == 'c' && line[*i] == '>')
	{
		cr_token(head, line, *s_index, size, NORMAL);
		cr_token(head, line, *i, 1, RED_OUTPUT);
		return (1);
	}
	else if (*q == 'c' && line[*i] == '<')
	{
		cr_token(head, line, *s_index, size, NORMAL);
		cr_token(head, line, *i, 1, RED_INPUT);
		return (1);
	}
	// else if (is_env(head, line, i, s_index, size, q))
	// 	return (1);
	return (0);
}


t_token	*lets_tokenize(char *line)
{
	int		i;
	int		s_index;
	int		count = 0;
	int		size;
	char	q;
	t_token	*head;
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
		if (line[i] == '\0')
			break;
		s_index = i;
		while (line[i])
		{
			if (is_special(&head, line, &i, &s_index, size, &q) == 1)
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
			cr_token(&head, line, s_index, size, NORMAL);
		if (!line[i])
			break ;
	}

	return (head);
}

