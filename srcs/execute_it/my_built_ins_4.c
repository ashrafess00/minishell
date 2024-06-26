/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:57:59 by kslik             #+#    #+#             */
/*   Updated: 2023/06/09 19:21:16 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit_arg(char *arg)
{
	int	i;

	i = -1;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
			write_error(arg, NUMERIC_ARGUMENT_REQUIRED, 255);
	}
}

void	my_exit(t_tree *tree, int *exit_code)
{
	unsigned char	u_exit_code;

	redirect_it(tree, DONT_REDIRECT);
	if (!tree->cmd_node->args[1])
	{
		printf("exit\n");
		exit(*exit_code);
	}
	else if (tree->cmd_node->args[1] && tree->cmd_node->args[2])
	{
		*exit_code = 1;
		ft_putstr_fd("our@shell: exit: too many arguments\n", 2);
	}
	else if (tree->cmd_node->args[1])
	{
		check_exit_arg(tree->cmd_node->args[1]);
		u_exit_code = ft_atoi(tree->cmd_node->args[1]);
		printf("exit\n");
		exit(u_exit_code);
	}
}

void	my_pwd(t_tree *tree, int *exit_code)
{
	char	cwd[512];
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		redirect_it(tree, REDIRECT);
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	*exit_code = WEXITSTATUS(status);
}

void	initialize_dt(struct s_export *info)
{
	info->i = -1;
	info->k = 0;
	info->fl = 0;
	info->si = 0;
	info->ps = 0;
	info->retu = 0;
	info->brak = 0;
}

int	is_built_in(t_tree *tree)
{
	if (!tree->cmd_node->args || !*tree->cmd_node->args)
		return (0);
	if (!ft_strcmp(tree->cmd_node->args[0], "cd")
		|| !ft_strcmp(tree->cmd_node->args[0], "echo")
		|| !ft_strcmp(tree->cmd_node->args[0], "exit")
		|| !ft_strcmp(tree->cmd_node->args[0], "pwd")
		|| !ft_strcmp(tree->cmd_node->args[0], "export")
		|| !ft_strcmp(tree->cmd_node->args[0], "unset"))
		return (1);
	return (0);
}
