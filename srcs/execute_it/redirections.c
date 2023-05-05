/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:01:11 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/05 17:15:14 by aessaoud         ###   ########.fr       */
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

void	redirect_it(t_tree *tree)
{
	int	fd;

	while (tree->cmd_node->redir_list)
	{
		if (tree->cmd_node->redir_list->type == RED_OUTPUT)
		{
			fd = open_outfile(tree->cmd_node->redir_list->file_name);
			dup2(fd, STDOUT_FILENO);
		}
		else if (tree->cmd_node->redir_list->type == RED_OUTPUT_APPEND)
		{
			fd = open_outfile_append(tree->cmd_node->redir_list->file_name);
			dup2(fd, STDOUT_FILENO);
		}
		else if (tree->cmd_node->redir_list->type == RED_INPUT)
		{
			fd = open_infile(tree->cmd_node->redir_list->file_name);
			dup2(fd, STDIN_FILENO);
		}
		else if (tree->cmd_node->redir_list->type == HEREDOC)
			heredoc_it(tree);
		tree->cmd_node->redir_list = tree->cmd_node->redir_list->next;
	}
}
