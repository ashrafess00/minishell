/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_special_chars_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:47:49 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/22 13:25:23 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_add_pipe_token(t_token **head, char *line, t_tin *tin)
{
	char	*token_s;
	char	*token_s_sp;

	if (tin->quote_stat == CLOSED_QUOTE && line[tin->i] == '|')
	{
		token_s = ft_substr(ft_strdup(line), tin->s_index, tin->size);
		add_token(head, token_s, WORD);
		token_s_sp = ft_substr(ft_strdup(line), tin->i, 1);
		add_token(head, token_s_sp, PIPE);
		tin->special_char_found = 1;
		return (1);
	}
	return (0);
}

int	check_add_heredoc_token(t_token **head, char *line, t_tin *tin)
{
	char	*token_s;
	char	*token_s_sp;

	if (tin->quote_stat == CLOSED_QUOTE && line[tin->i] == '<'
		&& line[tin->i + 1] == '<')
	{
		token_s = ft_substr(ft_strdup(line), tin->s_index, tin->size);
		add_token(head, token_s, WORD);
		token_s_sp = ft_substr(ft_strdup(line), tin->i, 2);
		add_token(head, token_s_sp, HEREDOC);
		tin->i += 1;
		tin->special_char_found = 1;
		return (1);
	}
	return (0);
}

int	check_add_red_append_token(t_token **head, char *line, t_tin *tin)
{
	char	*token_s;
	char	*token_s_sp;

	if (tin->quote_stat == CLOSED_QUOTE && line[tin->i] == '>'
		&& line[tin->i + 1] == '>')
	{
		token_s = ft_substr(ft_strdup(line), tin->s_index, tin->size);
		add_token(head, token_s, WORD);
		token_s_sp = ft_substr(ft_strdup(line), tin->i, 2);
		add_token(head, token_s_sp, RED_OUTPUT_APPEND);
		tin->i += 1;
		tin->special_char_found = 1;
		return (1);
	}
	return (0);
}

int	check_add_red_out_token(t_token **head, char *line, t_tin *tin)
{
	char	*token_s;
	char	*token_s_sp;

	if (tin->quote_stat == CLOSED_QUOTE && line[tin->i] == '>')
	{
		token_s = ft_substr(ft_strdup(line), tin->s_index, tin->size);
		add_token(head, token_s, WORD);
		token_s_sp = ft_substr(ft_strdup(line), tin->i, 1);
		add_token(head, token_s_sp, RED_OUTPUT);
		tin->special_char_found = 1;
		return (1);
	}
	return (0);
}

int	check_add_red_inp_token(t_token **head, char *line, t_tin *tin)
{
	char	*token_s;
	char	*token_s_sp;

	if (tin->quote_stat == CLOSED_QUOTE && line[tin->i] == '<')
	{
		token_s = ft_substr(ft_strdup(line), tin->s_index, tin->size);
		add_token(head, token_s, WORD);
		token_s_sp = ft_substr(ft_strdup(line), tin->i, 1);
		add_token(head, token_s_sp, RED_INPUT);
		tin->special_char_found = 1;
		return (1);
	}
	return (0);
}
