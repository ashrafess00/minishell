/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 23:15:50 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/11 21:15:37 by aessaoud         ###   ########.fr       */
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



int	is_special(t_token **head, char *line, int *i, int *s_index, int size, int q)
{
	if (q == 'c' && is_pipe(line + *i, q))
	{
		cr_token(head, line, *s_index, size, NORMAL);
		cr_token(head, line, *i, 1, PIPE);
		*s_index = *i + 1;
		*i += 1;
		return(1);
	}
	return (0);
}


void	lets_tokenize(char *line)
{
	int		i;
	int		s_index;
	int		count = 0;
	int		size;
	char	q;
	t_token	*head;

	head = NULL;
	i = -1;
	
	q = 'c';
	s_index = 0;
	while (line[++i])
	{
		size = 0;
		while(line[i] == ' ' && line[i])
			i++;
		if (line[i] == '\0')
			break;
		s_index = i;
		while (line[i])
		{
			is_special(&head, line, &i, &s_index, size, q);
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
		cr_token(&head, line, s_index, size, NORMAL);
		if (!line[i])
			break ;
	}

	t_token *to = head;
	while (to)
	{
		printf("arg : %-10s| i : %-5d| size : %-5d| TYPE : %c\n", to->s, to->s_index, to->size, to->type);
		to = to->next;
	}
}

