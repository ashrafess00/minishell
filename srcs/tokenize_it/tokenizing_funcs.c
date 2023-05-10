/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 23:15:50 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/10 15:52:31 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_special_char(t_token **head, char *line, t_token_info_norm *token_info_norm)
{
	if (check_add_pipe_token(head, line, token_info_norm))
		return (1);
	else if (check_add_heredoc_token(head, line, token_info_norm))
		return (1);
	else if (check_add_red_append_token(head, line, token_info_norm))
		return (1);
	else if (check_add_red_out_token(head, line, token_info_norm))
		return (1);
	else if (check_add_red_inp_token(head, line, token_info_norm))
		return (1);
	return (0);
}

void	change_quote_stat(t_token_info_norm *token_info_norm, char *line)
{
	int	i;
	t_quotes	quote_stat;

	i = token_info_norm->i;
	quote_stat = token_info_norm->quote_stat;
	if (line[i] == DOUBLE_QUOTE && quote_stat != DOUBLE_QUOTE && quote_stat != SINGLE_QUOTE)
		token_info_norm->quote_stat = DOUBLE_QUOTE;
	else if (line[i] == SINGLE_QUOTE && quote_stat != SINGLE_QUOTE && quote_stat != DOUBLE_QUOTE)
		token_info_norm->quote_stat = SINGLE_QUOTE;
	else if (line[i] == DOUBLE_QUOTE && quote_stat == DOUBLE_QUOTE)
		token_info_norm->quote_stat = CLOSED_QUOTE;
	else if (line[i] == SINGLE_QUOTE && quote_stat == SINGLE_QUOTE)
		token_info_norm->quote_stat = CLOSED_QUOTE;
}

void	fill_token_info_norm(t_token_info_norm	*token_info_norm)
{
	token_info_norm->i = -1;
	token_info_norm->quote_stat = CLOSED_QUOTE;
	token_info_norm->s_index = 0;
}

t_token	*lets_tokenize(char *line)
{
	t_token			*head;
	t_token_info_norm	token_info_norm;

	head = NULL;
	fill_token_info_norm(&token_info_norm);
	
	while (line[++token_info_norm.i])
	{
		token_info_norm.br = 0;
		token_info_norm.size = 0;
		while(line[token_info_norm.i] == ' ' && \
			token_info_norm.quote_stat == CLOSED_QUOTE && \
			line[token_info_norm.i])
			token_info_norm.i++;
		token_info_norm.s_index = token_info_norm.i;
		while (line[token_info_norm.i])
		{
			if (is_special_char(&head, line, &token_info_norm))
				break;
			if (line[token_info_norm.i] == ' ' && token_info_norm.quote_stat == CLOSED_QUOTE)
				break;
			change_quote_stat(&token_info_norm, line);
			token_info_norm.i++;
			token_info_norm.size++;
		}
		if (!token_info_norm.br)
			add_token(&head, line, token_info_norm.s_index, token_info_norm.size, NORMAL);
		if (!line[token_info_norm.i])
			break ;
	}
	free(line);
	return (head);
}

