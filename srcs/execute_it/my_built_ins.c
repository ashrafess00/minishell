/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:48:02 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/21 19:29:19 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	my_echo(t_tree *tree, int *exit_code)
{
	int	i;
	int	pid;
	int	status;

	i = 1;
	pid = fork();
	if (pid == -1)
	{
		perror("Fork Error");
		*exit_code = 1;
	}
	if (pid == 0)
	{
		redirect_it(tree, 1);
		if (!tree->cmd_node->args[1])
		{
			printf("\n");
			exit(0);
		}
		while (!ft_strcmp(tree->cmd_node->args[i], "-n"))
			i++;
		i--;
		while (tree->cmd_node->args[++i])
		{
			if (tree->cmd_node->args[i + 1])
				printf("%s ", tree->cmd_node->args[i]);
			else
				printf("%s", tree->cmd_node->args[i]);
		}
		if (ft_strcmp(tree->cmd_node->args[1], "-n"))
			printf("\n");
		exit(0);
	}
	waitpid(pid, &status, 0);
	*exit_code = WEXITSTATUS(status);
}


void	deleteNode(t_my_env **my_env, char *key)
{
	t_my_env	*tmp;
	t_my_env	*prev;
	int			i;
	int			si;

	prev = NULL;
	tmp = *my_env;
	while (tmp != NULL)
	{
		i = -1;
		si = 0;
		while (tmp->val[++i])
		{
			if (tmp->val[i] == '=')
				si = check_node_exist(tmp, key);
			if (si == 69)
				break ;
		}
		if (si != 10)
		{
			if (prev == NULL)
			{
				*my_env = tmp->next;
				freenode(tmp);
				tmp = *my_env;
			}
			else
			{
				prev->next = tmp->next;
				freenode(tmp);
				tmp = prev->next;
			}
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	my_unset(t_tree *tree, t_my_env **my_env, int *exit_code)
{
	int	i;

	i = 1;
	while (tree->cmd_node->args[i] != NULL)
	{
		if (unset_err(tree->cmd_node->args[i]) == 1)
			deleteNode(my_env, tree->cmd_node->args[i]);
		else
			*exit_code = 1;
		i++;
	}
	// print_envs(*my_env);
}
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|

void	call_built_in(t_tree *tree, t_my_env **my_env, int *exit_code)
{
	if (!ft_strcmp(tree->cmd_node->args[0], "echo"))
		my_echo(tree, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "cd"))
		my_cd(tree, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "exit"))
		my_exit(tree);
	else if (!ft_strcmp(tree->cmd_node->args[0], "pwd"))
		my_pwd(tree, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "export"))
		my_export(tree, my_env, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "unset"))
		my_unset(tree, my_env, exit_code);
}
