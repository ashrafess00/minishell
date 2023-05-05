/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:33:18 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/05 16:27:12 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
void	run_cmd(t_tree *tree, char **env)
{
	char	*path;
	char	**paths;
	int		pid;
	int		status;

	// pid = fork();
	// if (pid == 0)
	// {
		paths = get_path_from_env(env);
		path = get_path(tree->cmd_node->args[0], paths);
		redirect_it(tree);
		execve(path, tree->cmd_node->args, env);
	// }
	// else
	// 	waitpid(pid, &status, 0);
}

void	lets_execute(t_tree *tree, char **env, int *command_count)
{
	int		fds[2];
	int		l_pid;
	int		r_pid;
	int		status;
	int 	c;
	int		i;

	if (tree->type == CMD_NODE)
	{
		if (*command_count == 1)
		{
			l_pid = fork();
			if (l_pid == 0)
				run_cmd(tree, env);
			waitpid(l_pid, &status, 0);
			printf("l_pid %d exited with : %d\n", l_pid, WEXITSTATUS(status));
		}
		else
			run_cmd(tree, env);
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
			lets_execute(tree->left, env, command_count);
		}
		
		r_pid = fork();
		if (r_pid == 0)
		{
			close(fds[1]);
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			lets_execute(tree->right, env, command_count);
		}
		close(fds[0]);
		close(fds[1]);
		waitpid(l_pid, &status, 0);
		waitpid(r_pid, &status, 0);
		printf("exited with : %d\n", WEXITSTATUS(status));
		
	}
}