/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_special_chars_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:47:49 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/23 16:38:50 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_add_pipe_token(t_token **head, char *line, t_token_info *token_info)
{
	if (token_info->quote_stat == CLOSED_QUOTE && line[token_info->i] == '|')
	{
		add_token(head, line, token_info->s_index, token_info->size, NORMAL);
		add_token(head, line, token_info->i, 1, PIPE);
		token_info->br = 1;
		return (1);
	}
	return (0);
}

int	check_add_heredoc_token(t_token **head, char *line, t_token_info *token_info)
{
	if (token_info->quote_stat == CLOSED_QUOTE && line[token_info->i] == '<' && line[token_info->i + 1] == '<')
	{
		add_token(head, line, token_info->s_index, token_info->size, NORMAL);
		add_token(head, line, token_info->i, 2, HEREDOC);
		token_info->i += 1;
		token_info->br = 1;
		return (1);
	}
	return (0);
}

int	check_add_red_append_token(t_token **head, char *line, t_token_info *token_info)
{
	if (token_info->quote_stat == CLOSED_QUOTE && line[token_info->i] == '>' && line[token_info->i + 1] == '>')
	{
		add_token(head, line, token_info->s_index, token_info->size, NORMAL);
		add_token(head, line, token_info->i, 2, RED_OUTPUT_APPEND);
		token_info->i += 1;
		token_info->br = 1;
		return (1);
	}
	return (0);
}

int	check_add_red_out_token(t_token **head, char *line, t_token_info *token_info)
{
	if (token_info->quote_stat == CLOSED_QUOTE && line[token_info->i] == '>')
	{
		add_token(head, line, token_info->s_index, token_info->size, NORMAL);
		add_token(head, line, token_info->i, 1, RED_OUTPUT);
		token_info->br = 1;
		return (1);
	}
	return (0);
}

int	check_add_red_inp_token(t_token **head, char *line, t_token_info *token_info)
{
	if (token_info->quote_stat == CLOSED_QUOTE && line[token_info->i] == '<')
	{
		add_token(head, line, token_info->s_index, token_info->size, NORMAL);
		add_token(head, line, token_info->i, 1, RED_INPUT);
		token_info->br = 1;
		return (1);
	}
	return (0);
}