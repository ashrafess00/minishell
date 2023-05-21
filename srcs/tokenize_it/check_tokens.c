/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:14:23 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/21 14:37:23 by aessaoud         ###   ########.fr       */
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

int	check_tokens(t_token *tokens, int *exit_code)
{
	while (tokens)
	{
		if (!tokens->s || (tokens->type != WORD && !tokens->next)
			|| (tokens->type != WORD && tokens->next->type != WORD))
		{
			printf("SYNTAX ERROR!!\n");
			*exit_code = 1;
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}
