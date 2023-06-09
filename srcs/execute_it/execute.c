/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:33:18 by aessaoud          #+#    #+#             */
/*   Updated: 2023/06/09 13:13:28 by kslik            ###   ########.fr       */
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

void	cmd_part(t_tree *tree, int *exit_code,
	t_my_env **my_env, int is_single_cmd)
{
	int		status;
	pid_t	pid;

	if (is_built_in(tree))
		call_built_in(tree, my_env, exit_code);
	else if (!is_single_cmd)
		run_cmd(tree, my_env);
	else
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

void	close_fds(int fds[2])
{
	close(fds[0]);
	close(fds[1]);
}

void	pipe_part(t_tree *tree, int *exit_code, t_my_env **my_env, int fds[2])
{
	int	status;
	int	l_pid;
	int	r_pid;

	l_pid = fork();
	if (l_pid == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close_fds(fds);
		lets_execute(tree->left, my_env, 0, exit_code);
		exit(*exit_code);
	}	
	r_pid = fork();
	if (r_pid == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		close_fds(fds);
		lets_execute(tree->right, my_env, 0, exit_code);
		exit(*exit_code);
	}
	close_fds(fds);
	waitpid(l_pid, &status, 0);
	waitpid(r_pid, &status, 0);
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		*exit_code = WTERMSIG(status) + 128;
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
