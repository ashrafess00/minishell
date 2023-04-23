/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 23:15:50 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/23 16:41:19 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_special_char(t_token **head, char *line, t_token_info *token_info)
{
	if (check_add_pipe_token(head, line, token_info))
		return (1);
	else if (check_add_heredoc_token(head, line, token_info))
		return (1);
	else if (check_add_red_append_token(head, line, token_info))
		return (1);
	else if (check_add_red_out_token(head, line, token_info))
		return (1);
	else if (check_add_red_inp_token(head, line, token_info))
		return (1);
	return (0);
}

t_token	*lets_tokenize(char *line)
{
	t_token			*head;
	t_token_info	token_info;

	head = NULL;
	token_info.i = -1;
	token_info.quote_stat = CLOSED_QUOTE;
	token_info.s_index = 0;
	while (line[++token_info.i])
	{
		token_info.br = 0;
		token_info.size = 0;
		while(line[token_info.i] == ' ' && token_info.quote_stat == CLOSED_QUOTE && line[token_info.i])
			token_info.i++;
		token_info.s_index = token_info.i;
		while (line[token_info.i])
		{
			if (is_special_char(&head, line, &token_info))
				break;
			if (line[token_info.i] == ' ' && token_info.quote_stat == CLOSED_QUOTE)
				break;
			else if (line[token_info.i] == DOUBLE_QUOTE && token_info.quote_stat != DOUBLE_QUOTE && token_info.quote_stat != SINGLE_QUOTE)
				token_info.quote_stat = DOUBLE_QUOTE;
			else if (line[token_info.i] == SINGLE_QUOTE && token_info.quote_stat != SINGLE_QUOTE && token_info.quote_stat != DOUBLE_QUOTE)
				token_info.quote_stat = SINGLE_QUOTE;
			else if (line[token_info.i] == DOUBLE_QUOTE && token_info.quote_stat == DOUBLE_QUOTE)
				token_info.quote_stat = CLOSED_QUOTE;
			else if (line[token_info.i] == SINGLE_QUOTE && token_info.quote_stat == SINGLE_QUOTE)
				token_info.quote_stat = CLOSED_QUOTE;
			token_info.i++;
			token_info.size++;
		}
		if (!token_info.br)
			add_token(&head, line, token_info.s_index, token_info.size, NORMAL);
		if (!line[token_info.i])
			break ;
	}
	return (head);
}

