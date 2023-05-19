/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:14:23 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/19 15:18:11 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	enter_a_pipe(t_token **tokens)
{
	char	*line;
	t_token	*tmp;

	tmp = (*tokens);
	while (1)
	{
		while (tmp->next)
			tmp = tmp->next;
		if (tmp->type == PIPE)
		{
			line = readline("pipe> ");
			tmp->next = lets_tokenize(line);
			free(line);
		}
		else
			return ;
	}
}

int	check_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->s)
		{
			printf("SYNTAX ERROR!!\n");
			return (0);
		}
		if (tokens->type != WORD && tokens->next->type != WORD)
		{
			printf("SYNTAX ERROR [%c]\n", tokens->next->type);
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}