/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 23:15:50 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/10 02:27:39 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	cr_token(t_token **head, int c)
{
	t_token	*new_dl;
	t_token	*last;

	new_dl = malloc(sizeof(t_token));
	last = *head;
	new_dl->num = c;
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

void	lets_parse(char *line)
{
	int		i;
	int		count = 0;
	int		size;
	char	q;
	t_token	*head;

	i = -1;
	line = ft_strtrim(line, " ");
	q = 'n';
	while (line[++i])
	{
		size = 0;
		while(line[i] == ' ')
			i++;
		while (line[i])
		{
			if (line[i] == ' ' && q == 'n')
				break;
			else if (line[i] == D_QUOTE && q != D_QUOTE)
				q = D_QUOTE;
			else if (line[i] == S_QUOTE && q != S_QUOTE)
				q = S_QUOTE;
			else if (line[i] == D_QUOTE && q == D_QUOTE)
				q = 'n';
			else if (line[i] == S_QUOTE && q == S_QUOTE)
				q = 'n';
			i++;
			size++;
		}
		break;
	}
	printf("%d\n", size);
}

