/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:33:18 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/03 18:31:20 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
		tree->cmd_node->redir_list = tree->cmd_node->redir_list->next;
	}
}

void	lets_execute(t_tree *tree, char **env, int *fds, int fds_count, int *count)
{
	char	*path;
	char	**paths;
	int		w_to;
	int		r_from;

	if (tree->type == PIPE_NODE)
	{
		lets_execute(tree->left, env, fds, fds_count, count);
		*count += 1;
		lets_execute(tree->right, env, fds, fds_count, count);
	}
	else
	{
		int f = fork();
		if (f == 0)
		{
			if (fds_count != 0)
			{
				r_from = (*count - 1) * 2;
				w_to = *count * 2 + 1;
				if (r_from < 0)
				{
					close_fds(fds, fds_count, w_to);
					dup2(fds[w_to], STDOUT_FILENO);
					close(fds[w_to]);
				}
				else if (w_to >= fds_count)
				{
					close_fds(fds, fds_count, r_from);
					dup2(fds[r_from], STDIN_FILENO);
					close(fds[r_from]);
				}
				else
				{
					close_fds(fds, fds_count, r_from, w_to);
					dup2(fds[w_to], STDOUT_FILENO);
					close(fds[w_to]);
					dup2(fds[r_from], STDIN_FILENO);
					close(fds[r_from]);
				}
			}
			paths = get_path_from_env(env);
			path = get_path(tree->cmd_node->args[0], paths);
			redirect_it(tree);
			execve(path, tree->cmd_node->args, env);
		}
		else
		{
			//to close file discriptors which were are not used, from parent process
			close_fds_from_parent(fds, fds_count, *count);
			wait(NULL);
			return;
		}
	}
}

// void	lets_execute_single_command(t_tree *tree, char **env)
// {
// 	char	**paths;
// 	char	*path;
// 	int		pid;

// 	paths = get_path_from_env(env);
// 	path = get_path(tree->cmd_node->args[0], paths);
// 	while (tree->cmd_node->redir_list)
// 	{
// 		if (tree->cmd_node->redir_list->type == RED_OUTPUT)
// 		{
// 			int fd = open_outfile(tree->cmd_node->redir_list->file_name);
// 			dup2(fd, STDOUT_FILENO);
// 		}
// 		tree->cmd_node->redir_list = tree->cmd_node->redir_list->next;
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 		execve(path, tree->cmd_node->args, env);
// 	else
// 		wait(NULL);
// }