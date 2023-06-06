/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:48:02 by aessaoud          #+#    #+#             */
/*   Updated: 2023/06/06 14:59:55 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_prv_null(struct s_unset *un, t_my_env **my_env, int n)
{
	if (n == 1)
	{
		*my_env = un->tmp->next;
		freenode(un->tmp);
		un->tmp = *my_env;
	}
	else if (n == 0)
	{
		un->prev->next = un->tmp->next;
		freenode(un->tmp);
		un->tmp = un->prev->next;
	}
	else if (n == 2)
	{
		un->prev = un->tmp;
		un->tmp = un->tmp->next;
	}
}

void	deletenode(t_my_env **my_env, char *key)
{
	struct s_unset	un;

	unsetdata(&un, my_env, 0);
	while (un.tmp != NULL)
	{
		unsetdata(&un, my_env, 1);
		while (un.tmp->val[++un.i])
		{
			if (un.tmp->val[un.i] == '=')
				un.si = check_node_exist(un.tmp, key);
			if (un.si == 69)
				break ;
		}
		if (un.si != 10)
		{
			if (un.prev == NULL)
				if_prv_null(&un, my_env, 1);
			else
				if_prv_null(&un, my_env, 0);
		}
		else
			if_prv_null(&un, my_env, 2);
	}
}

void	my_unset(t_tree *tree, t_my_env **my_env, int *exit_code)
{
	int	i;

	i = 1;
	*exit_code = 0;
	while (tree->cmd_node->args[i] != NULL)
	{
		if (unset_err(tree->cmd_node->args[i]) == 1)
			deletenode(my_env, tree->cmd_node->args[i]);
		else
			*exit_code = 1;
		i++;
	}
}

void	my_envv(t_my_env **my_env, int *exit_code)
{
	print_envs(*my_env);
	*exit_code = 0;
}

void	call_built_in(t_tree *tree, t_my_env **my_env, int *exit_code)
{
	if (!ft_strcmp(tree->cmd_node->args[0], "echo"))
		my_echo(tree, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "cd"))
		my_cd(tree, my_env, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "exit"))
		my_exit(tree, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "pwd"))
		my_pwd(tree, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "export"))
		my_export(tree, my_env, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "unset"))
		my_unset(tree, my_env, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "env"))
		my_envv(my_env, exit_code);
}
