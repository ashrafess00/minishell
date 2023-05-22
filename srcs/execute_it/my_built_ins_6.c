/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:43:12 by kslik             #+#    #+#             */
/*   Updated: 2023/05/22 10:52:56 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	echo_err(int *exit_code, int c)
{
	if (c == 0)
	{
		perror("Fork Error");
		*exit_code = 1;
	}
	else if (c == 1)
	{
		printf("\n");
		exit(0);
	}
}

void	echo_dt(struct s_echo *echo, int c, int *exit_code)
{
	if (c == 0)
	{
		echo->i = 1;
		echo->pid = fork();
	}
	if (echo->pid == -1)
		echo_err(exit_code, 0);
}

void	my_echo(t_tree *tree, int *exit_code)
{
	struct s_echo	ech;

	echo_dt(&ech, 0, exit_code);
	echo_dt(&ech, 1, exit_code);
	if (ech.pid == 0)
	{
		redirect_it(tree, 1);
		if (!tree->cmd_node->args[1])
			echo_err(exit_code, 1);
		while (!ft_strcmp(tree->cmd_node->args[ech.i], "-n"))
			ech.i++;
		ech.i--;
		while (tree->cmd_node->args[++ech.i])
		{
			if (tree->cmd_node->args[ech.i + 1])
				printf("%s ", tree->cmd_node->args[ech.i]);
			else
				printf("%s", tree->cmd_node->args[ech.i]);
		}
		if (ft_strcmp(tree->cmd_node->args[1], "-n"))
			printf("\n");
		exit(0);
	}
	waitpid(ech.pid, &ech.status, 0);
	*exit_code = WEXITSTATUS(ech.status);
}

void	unsetdata(struct s_unset *unset, t_my_env **my_env, int n)
{
	if (n == 0)
	{
		unset->prev = NULL;
		unset->tmp = *my_env;
	}
	if (n == 1)
	{
		unset->i = -1;
		unset->si = 0;
	}
}
