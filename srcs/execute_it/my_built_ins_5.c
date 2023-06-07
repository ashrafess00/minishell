/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:58:38 by kslik             #+#    #+#             */
/*   Updated: 2023/06/07 20:23:40 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_home(t_my_env *env, int *exit_code)
{
	char		*home;
	t_my_env	*tmp;

	tmp = env;
	home = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->val, "HOME=", 5))
		{
			home = ft_substr(ft_strdup(tmp->val), 5, ft_strlen(tmp->val) - 5);
			chdir(home);
			free(home);
			return ;
		}
		tmp = tmp->next;
	}
	if (!home)
	{
		printf("/our@shell: cd: HOME not set\n");
		*exit_code = 1;
	}
}

void	my_cd(t_tree *tree, t_my_env **env, int *exit_code)
{
	int			i;

	i = -1;
	redirect_it(tree, DONT_REDIRECT);
	if (!tree->cmd_node->args[1])
		get_home(*env, exit_code);
	else
	{
		if (chdir(tree->cmd_node->args[1]))
		{
			write(2, "our@shell: cd: ", 15);
			perror(tree->cmd_node->args[1]);
			*exit_code = 1;
			return ;
		}
		*exit_code = 0;
	}
	update_envs(env);
}

int	check_node_exist(t_my_env *tmp, char *key)
{
	int	si;
	int	q;

	q = 0;
	si = 0;
	while (tmp->val[q] != '=' && si == 0)
	{
		if (tmp->val[q] != key[q])
			si = 10;
		q++;
	}
	if (key[q] != '\0')
		si = 10;
	if (si != 10)
		si = 69;
	return (si);
}
