/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:33:18 by aessaoud          #+#    #+#             */
/*   Updated: 2023/06/09 14:04:20 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd(t_tree *tree, t_my_env **my_env)
{
	char	*path;
	char	**paths;
	char	**env;

	if (*tree->cmd_node->args)
		redirect_it(tree, REDIRECT);
	else
		redirect_it(tree, DONT_REDIRECT);
	env = from_lk_to_arr(my_env);
	free_my_env(my_env);
	paths = get_path_from_env(env);
	if (!*tree->cmd_node->args)
		exit(0);
	path = get_path(tree->cmd_node->args[0], paths);
	free_arr(paths);
	if (execve(path, tree->cmd_node->args, env) == -1)
	{
		free(path);
		free_arr(env);
		perror("ERROR");
		exit(2);
	}
}

int	is_built_in_or_not_single_cmd(t_tree *tree, int is_single_cmd,
t_my_env **my_env, int *exit_code)
{
	if (is_built_in(tree))
	{
		call_built_in(tree, my_env, exit_code);
		return (1);
	}
	else if (!is_single_cmd)
	{
		run_cmd(tree, my_env);
		return (1);
	}
	return (0);
}

void	cmd_part(t_tree *tree, int *exit_code,
	t_my_env **my_env, int is_single_cmd)
{
	int		status;
	pid_t	pid;

	if (!is_built_in_or_not_single_cmd(tree, is_single_cmd, my_env, exit_code))
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			signal(SIGQUIT, SIG_IGN);
			run_cmd(tree, my_env);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &status, 0);
			signal(SIGINT, ctrl_c_handler);
			signal(SIGQUIT, SIG_IGN);
			if (WIFEXITED(status))
				*exit_code = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				*exit_code = WTERMSIG(status) + 128;
		}
	}
}

void	lets_execute(t_tree *tree, t_my_env **my_env,
	int is_single_cmd, int *exit_code)
{
	int	fds[2];

	if (tree->type == CMD_NODE)
		cmd_part(tree, exit_code, my_env, is_single_cmd);
	else
	{
		pipe(fds);
		pipe_part(tree, exit_code, my_env, fds);
	}
}
