/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:43:12 by kslik             #+#    #+#             */
/*   Updated: 2023/06/09 19:18:51 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dash_n(char *s, int dash_n_found, int *dash_n_exist)
{
	int	i;

	i = -1;
	if (dash_n_found || (s[0] != '-'))
		return (0);
	else
	{
		i += 1;
		while (s[++i])
		{
			if (s[i] != 'n')
				return (0);
		}
	}
	*dash_n_exist = 1;
	return (1);
}

typedef struct echo_data
{
	int	pid;
	int	status;
	int	dash_n;
	int	i;
	int	dash_n_exist;
}	t_echo_data;

void	fill_echo_data(t_echo_data *echo_data)
{
	echo_data->i = 0;
	echo_data->dash_n = 0;
	echo_data->dash_n_exist = 0;
	echo_data->pid = fork();
	if (echo_data->pid == -1)
		exit (1);
}

void	my_echo(t_tree *tree, int *exit_code)
{
	t_echo_data	echo_data;

	fill_echo_data(&echo_data);
	if (echo_data.pid == 0)
	{
		redirect_it(tree, 1);
		while (tree->cmd_node->args[++echo_data.i])
		{
			if (!is_dash_n(tree->cmd_node->args[echo_data.i],
					echo_data.dash_n, &echo_data.dash_n_exist))
			{
				echo_data.dash_n = 1;
				printf("%s", tree->cmd_node->args[echo_data.i]);
				if (tree->cmd_node->args[echo_data.i + 1])
					printf(" ");
			}
		}
		if (!echo_data.dash_n_exist)
			printf("\n");
		exit(0);
	}
	waitpid(echo_data.pid, &echo_data.status, 0);
	*exit_code = 0;
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
