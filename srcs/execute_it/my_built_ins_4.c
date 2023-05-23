/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:57:59 by kslik             #+#    #+#             */
/*   Updated: 2023/05/23 12:58:11 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	my_exit(t_tree *tree)
{
	redirect_it(tree, DONT_REDIRECT);
	if (tree->cmd_node->args[1])
		exit(255);
	exit(0);
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

char	**my_env_to_array(t_my_env **my_env)
{
	int			size;
	int			i;
	t_my_env	*current;
	char		**envp;

	size = 0;
	i = 0;
	current = *my_env;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	envp = (char **)malloc((size + 1) * sizeof(char *));
	current = *my_env;
	while (current != NULL)
	{
		envp[i] = current->val;
		current = current->next;
		i++;
	}
	envp[size] = NULL;
	return (envp);
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
