/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:33:18 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/12 15:34:17 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	run_cmd(t_tree *tree, t_my_env **my_env)
{
	char	*path;
	char	**paths;
	int		pid;
	int		status;
	char	**env;

	if (*tree->cmd_node->args)
		redirect_it(tree, 1);
	else
		redirect_it(tree, 0);
	env = from_lk_to_arr(my_env);
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

void	lets_execute(t_tree *tree, t_my_env **my_env, int is_single_cmd, int *exit_code)
{
	int		fds[2];
	int		l_pid;
	int		r_pid;
	int		status;

	*exit_code = 1420;

	if (tree->type == CMD_NODE)
	{
		if(is_built_in(tree))
			call_built_in(tree, my_env, exit_code);
		else if (!is_single_cmd)
			run_cmd(tree, my_env);
		else
		{
			l_pid = fork();
			if (l_pid == 0)
				run_cmd(tree, my_env);
			else
			{
				waitpid(l_pid, &status, 0);
				// printf("exited code aa %d\n", WEXITSTATUS(status));
				*exit_code = WEXITSTATUS(status);
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
			lets_execute(tree->left, my_env, is_single_cmd, exit_code);
			exit(0);
		}
		
		r_pid = fork();
		if (r_pid == 0)
		{
			close(fds[1]);
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			lets_execute(tree->right, my_env, is_single_cmd, exit_code);
			exit(0);
		}
		close(fds[0]);
		close(fds[1]);
		waitpid(l_pid, &status, 0);
		waitpid(r_pid, &status, 0);
		// printf("exited code po %d\n", WEXITSTATUS(status));
		*exit_code = WEXITSTATUS(status);
	}
}
