/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:48:02 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/09 21:06:59 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	my_echo(t_tree *tree)
{
	int	i;
	int	pid;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		redirect_it (tree, 1);
		if (!tree->cmd_node->args[1])
			return ;
		if (!ft_strcmp(tree->cmd_node->args[1], "-n"))
			i = 1;
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
	waitpid(pid, NULL, 0);
}

void	my_cd(t_tree *tree)
{
	redirect_it(tree, 0);
	if (!tree->cmd_node->args[1])
		return ;
	if (chdir(tree->cmd_node->args[1]))
	{
		write(2, "our@shell: cd: ", 11);
		perror(tree->cmd_node->args[1]);
	}
}

void	my_exit(t_tree *tree)
{
	redirect_it(tree, 0);
	exit(0);
}

void	my_pwd(t_tree *tree)
{
	char	cwd[512];
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		redirect_it(tree, 1);
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|
void	my_export(t_tree *tree, char **env)
{
	//tree->cmd_node->args
	int	i;

	i = -1;
	//hadi ghadi t printi l arguments lli ghayjiw m3a export
	while (tree->cmd_node->args[++i])
		printf("%s\n", tree->cmd_node->args[i]);
}

void	my_unset(t_tree *tree, char **env)
{
	//tree->cmd_node->args
	int	i;

	i = -1;
	//hadi ghadi t printi l arguments lli ghayjiw m3a export
	while (tree->cmd_node->args[++i])
		printf("%s\n", tree->cmd_node->args[i]);
}
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|

void	call_built_in(t_tree *tree, char **env)
{
	if (!ft_strcmp(tree->cmd_node->args[0], "echo"))
		my_echo(tree);
	else if (!ft_strcmp(tree->cmd_node->args[0], "cd"))
		my_cd (tree);
	else if (!ft_strcmp(tree->cmd_node->args[0], "exit"))
		my_exit (tree);
	else if (!ft_strcmp(tree->cmd_node->args[0], "pwd"))
		my_pwd (tree);
	else if (!ft_strcmp(tree->cmd_node->args[0], "export"))
		my_export (tree, env);
	else if (!ft_strcmp(tree->cmd_node->args[0], "unset"))
		my_unset (tree, env);
}


int	is_built_in(char *args)
{
	if (!ft_strcmp(args, "cd") || !ft_strcmp(args, "echo")
		|| !ft_strcmp(args, "exit") || !ft_strcmp(args, "pwd")
		|| !ft_strcmp(args, "export") || !ft_strcmp(args, "unset"))
		return (1);
	return (0);
}

