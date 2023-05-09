/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:33:18 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/09 22:33:24 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
void	run_cmd(t_tree *tree, char **env)
{
	char	*path;
	char	**paths;
	int		pid;
	int		status;

	if (*tree->cmd_node->args)
		redirect_it(tree, 1);
	else
		redirect_it(tree, 0);
	paths = get_path_from_env(env);
	if (!*tree->cmd_node->args)
		exit(0) ;
	path = get_path(tree->cmd_node->args[0], paths);
	if (execve(path, tree->cmd_node->args, env) == -1)
	{
		free(path);
		free(paths);
		exit(2);
	}
}

void	lets_execute(t_tree *tree, char **env, int is_single_cmd)
{
	int		fds[2];
	int		l_pid;
	int		r_pid;
	int		status;

	if (tree->type == CMD_NODE)
	{
		if(is_built_in(tree))
			call_built_in(tree, env);
		else if (!is_single_cmd)
			run_cmd(tree, env);
		else
		{
			l_pid = fork();
			if (l_pid == 0)
				run_cmd(tree, env);
			else
			{
				waitpid(l_pid, &status, 0);
				// printf("exited code %d\n", WEXITSTATUS(status));
			}
		}
	}
	else
	{
		pipe(fds);
		l_pid = fork();
		if (l_pid == 0)
		{
			close(fds[0]);
			dup2(fds[1], STDOUT_FILENO);
			close(fds[1]);
			lets_execute(tree->left, env, is_single_cmd);
			exit(0);
		}
		
		r_pid = fork();
		if (r_pid == 0)
		{
			close(fds[1]);
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			lets_execute(tree->right, env, is_single_cmd);
			exit(0);
		}
		close(fds[0]);
		close(fds[1]);
		waitpid(l_pid, &status, 0);
		waitpid(r_pid, &status, 0);
	}
}
