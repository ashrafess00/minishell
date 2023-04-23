/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:47:49 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/23 14:50:30 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	add_pipe_token(t_token **head, char *line, int *i, int *s_index, int size)
{
	add_token(head, line, *s_index, size, NORMAL);
	add_token(head, line, *i, 1, PIPE);
}

void	add_heredoc_token(t_token **head, char *line, int *i, int *s_index, int size)
{
	add_token(head, line, *s_index, size, NORMAL);
	add_token(head, line, *i, 2, HEREDOC);
	*i += 1;
}

void	add_red_append_token(t_token **head, char *line, int *i, int *s_index, int size)
{
	add_token(head, line, *s_index, size, NORMAL);
	add_token(head, line, *i, 2, RED_OUTPUT_APPEND);
	*i += 1;
}

void	add_red_out_token(t_token **head, char *line, int *i, int *s_index, int size)
{
	add_token(head, line, *s_index, size, NORMAL);
	add_token(head, line, *i, 1, RED_OUTPUT);
}

void	add_red_inp_token(t_token **head, char *line, int *i, int *s_index, int size)
{
	add_token(head, line, *s_index, size, NORMAL);
	add_token(head, line, *i, 1, RED_INPUT);
}