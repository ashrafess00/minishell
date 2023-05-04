/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:33:18 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/04 14:26:33 by aessaoud         ###   ########.fr       */
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

void	run_cmd(t_tree *tree, char **env)
{
	char	*path;
	char	**paths;
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		paths = get_path_from_env(env);
		path = get_path(tree->cmd_node->args[0], paths);
		redirect_it(tree);
		execve(path, tree->cmd_node->args, env);
	}
	else
		waitpid(pid, &status, 0);
}

void	lets_execute(t_tree *tree, char **env)
{
	
	int		w_to;
	int		r_from;
	int		fds[2];
	int		l_pid;
	int		r_pid;

	if (tree->type == PIPE_NODE)
	{
		pipe(fds);
		l_pid = fork();
		if (l_pid == 0)
		{
			close(fds[0]);
			dup2(fds[1], STDOUT_FILENO);
			close(fds[1]);
			lets_execute(tree->left, env);
			exit(0);
		}
		
		r_pid = fork();
		if (r_pid == 0)
		{
			close(fds[1]);
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			lets_execute(tree->right, env);
			exit(0);
		}
		close(fds[0]);
		close(fds[1]);
		waitpid(l_pid, NULL, 0);
		waitpid(r_pid, NULL, 0);
	}
	else
	{
		run_cmd(tree, env);
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