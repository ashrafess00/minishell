/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 23:15:50 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/15 22:15:14 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_special_char(t_token **head, char *line, t_tin *tin)
{
	tin->special_char_found = 0;
	if (check_add_pipe_token(head, line, tin))
		return (1);
	else if (check_add_heredoc_token(head, line, tin))
		return (1);
	else if (check_add_red_append_token(head, line, tin))
		return (1);
	else if (check_add_red_out_token(head, line, tin))
		return (1);
	else if (check_add_red_inp_token(head, line, tin))
		return (1);
	return (0);
}

void	change_quote_stat(t_tin *tin, char *line)
{
	int			i;
	t_quotes	quote_stat;

	i = tin->i;
	quote_stat = tin->quote_stat;
	if (line[i] == DOUBLE_QUOTE && quote_stat != \
		DOUBLE_QUOTE && quote_stat != SINGLE_QUOTE)
		tin->quote_stat = DOUBLE_QUOTE;
	else if (line[i] == SINGLE_QUOTE && quote_stat != \
		SINGLE_QUOTE && quote_stat != DOUBLE_QUOTE)
		tin->quote_stat = SINGLE_QUOTE;
	else if (line[i] == DOUBLE_QUOTE && quote_stat == DOUBLE_QUOTE)
		tin->quote_stat = CLOSED_QUOTE;
	else if (line[i] == SINGLE_QUOTE && quote_stat == SINGLE_QUOTE)
		tin->quote_stat = CLOSED_QUOTE;
	tin->i++;
	tin->size++;
}

void	fill_tin(t_tin	*tin)
{
	tin->i = -1;
	tin->quote_stat = CLOSED_QUOTE;
	tin->s_index = 0;
	tin->special_char_found = 0;
}

void	skip_spaces(char *line, t_tin *tin)
{
	while (line[tin->i] == ' ' && \
			tin->quote_stat == CLOSED_QUOTE && \
			line[tin->i])
			tin->i++;
	tin->s_index = tin->i;
}

t_token	*lets_tokenize(char *line)
{
	t_token				*head;
	t_tin				tin;

	head = NULL;
	fill_tin(&tin);
	while (line[++tin.i])
	{
		tin.size = 0;
		skip_spaces(line, &tin);
		while (line[tin.i])
		{
			is_special_char(&head, line, &tin);
			if (tin.special_char_found || (line[tin.i] == ' ' && \
				tin.quote_stat == CLOSED_QUOTE))
				break ;
			change_quote_stat(&tin, line);
		}
		if (!tin.special_char_found)
			add_token(&head, ft_substr(ft_strdup(line), \
				tin.s_index, tin.size), WORD);
		if (!line[tin.i])
			break ;
	}
	enter_a_pipe(&head);
	return (head);
}
