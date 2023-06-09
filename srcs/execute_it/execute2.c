/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:53:16 by aessaoud          #+#    #+#             */
/*   Updated: 2023/06/09 14:03:04 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_left_command(t_tree *tree, int fds[2],
t_my_env **my_env, int *exit_code)
{
	dup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	lets_execute(tree->left, my_env, 0, exit_code);
	exit(*exit_code);
}

static void	run_right_command(t_tree *tree, int fds[2],
t_my_env **my_env, int *exit_code)
{
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	close(fds[1]);
	lets_execute(tree->right, my_env, 0, exit_code);
	exit(*exit_code);
}

void	pipe_part(t_tree *tree, int *exit_code, t_my_env **my_env, int fds[2])
{
	int	status;
	int	l_pid;
	int	r_pid;

	l_pid = fork();
	if (l_pid == 0)
		run_left_command(tree, fds, my_env, exit_code);
	r_pid = fork();
	if (r_pid == 0)
		run_right_command(tree, fds, my_env, exit_code);
	close(fds[0]);
	close(fds[1]);
	waitpid(l_pid, &status, 0);
	waitpid(r_pid, &status, 0);
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		*exit_code = WTERMSIG(status) + 128;
	}
}
