/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_special_chars_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:47:49 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/11 22:48:01 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_add_pipe_token(t_token **head, char *line, t_token_info_norm *token_info_norm)
{
	char	*token_s;
	char	*token_s_sp;
	char	line_cp;

	if (token_info_norm->quote_stat == CLOSED_QUOTE && line[token_info_norm->i] == '|')
	{
		token_s = ft_substr(ft_strdup(line) , token_info_norm->s_index, token_info_norm->size);
		add_token(head, token_s, NORMAL);
		token_s_sp = ft_substr(ft_strdup(line) , token_info_norm->i, 1);
		add_token(head, token_s_sp, PIPE);
		token_info_norm->br = 1;
		return (1);
	}
	return (0);
}

int	check_add_heredoc_token(t_token **head, char *line, t_token_info_norm *token_info_norm)
{
	char	*token_s;
	char	*token_s_sp;

	if (token_info_norm->quote_stat == CLOSED_QUOTE && line[token_info_norm->i] == '<' && line[token_info_norm->i + 1] == '<')
	{
		token_s = ft_substr(ft_strdup(line), token_info_norm->s_index, token_info_norm->size);
		add_token(head, token_s, NORMAL);
		token_s_sp = ft_substr(ft_strdup(line) , token_info_norm->i, 2);
		add_token(head, token_s_sp, HEREDOC);
		token_info_norm->i += 1;
		token_info_norm->br = 1;
		return (1);
	}
	return (0);
}

int	check_add_red_append_token(t_token **head, char *line, t_token_info_norm *token_info_norm)
{
	char	*token_s;
	char	*token_s_sp;

	if (token_info_norm->quote_stat == CLOSED_QUOTE && line[token_info_norm->i] == '>' && line[token_info_norm->i + 1] == '>')
	{
		token_s = ft_substr(ft_strdup(line), token_info_norm->s_index, token_info_norm->size);
		add_token(head, token_s, NORMAL);
		token_s_sp = ft_substr(ft_strdup(line), token_info_norm->i, 2);
		add_token(head, token_s_sp, RED_OUTPUT_APPEND);
		token_info_norm->i += 1;
		token_info_norm->br = 1;
		return (1);
	}
	return (0);
}

int	check_add_red_out_token(t_token **head, char *line, t_token_info_norm *token_info_norm)
{
	char	*token_s;
	char	*token_s_sp;

	if (token_info_norm->quote_stat == CLOSED_QUOTE && line[token_info_norm->i] == '>')
	{
		token_s = ft_substr(ft_strdup(line), token_info_norm->s_index, token_info_norm->size);
		add_token(head, token_s, NORMAL);
		token_s_sp = ft_substr(ft_strdup(line), token_info_norm->i, 1);

		add_token(head, token_s_sp, RED_OUTPUT);
		token_info_norm->br = 1;
		return (1);
	}
	return (0);
}

int	check_add_red_inp_token(t_token **head, char *line, t_token_info_norm *token_info_norm)
{
	char	*token_s;
	char	*token_s_sp;

	if (token_info_norm->quote_stat == CLOSED_QUOTE && line[token_info_norm->i] == '<')
	{
		token_s = ft_substr(ft_strdup(line), token_info_norm->s_index, token_info_norm->size);
		add_token(head, token_s, NORMAL);
		token_s_sp = ft_substr(ft_strdup(line), token_info_norm->i, 1);
		add_token(head, token_s_sp, RED_INPUT);
		token_info_norm->br = 1;
		return (1);
	}
	return (0);
}