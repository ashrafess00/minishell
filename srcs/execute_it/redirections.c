/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:01:11 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/21 23:26:40 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	heredoc_it(t_tree *tree)
{
	int	heredoc_fds[2];

	pipe(heredoc_fds);
	write(heredoc_fds[1], tree->cmd_node->redir_list->here_doc_text,
		ft_strlen(tree->cmd_node->redir_list->here_doc_text));
	close(heredoc_fds[1]);
	dup2(heredoc_fds[0], STDIN_FILENO);
	close(heredoc_fds[0]);
}

void	dup_for_red_out(int fd, int redirect)
{
	if (fd == -1)
		return ;
	if (redirect)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	dup_for_red_in(int fd, int redirect)
{
	if (fd == -1)
		return ;
	if (redirect)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	redirect_it(t_tree *tree, int redirect)
{
	int	fd;

	while (tree->cmd_node->redir_list)
	{
		if (tree->cmd_node->redir_list->type == RED_OUTPUT)
		{
			fd = open_outfile(tree->cmd_node->redir_list->file_name);
			dup_for_red_out(fd, redirect);
		}
		else if (tree->cmd_node->redir_list->type == RED_OUTPUT_APPEND)
		{
			fd = open_outfile_append(tree->cmd_node->redir_list->file_name);
			dup_for_red_out(fd, redirect);
		}
		else if (tree->cmd_node->redir_list->type == RED_INPUT)
		{
			fd = open_infile(tree->cmd_node->redir_list->file_name);
			dup_for_red_in(fd, redirect);
		}
		else if (tree->cmd_node->redir_list->type == HEREDOC)
			heredoc_it(tree);
		tree->cmd_node->redir_list = tree->cmd_node->redir_list->next;
	}
}
