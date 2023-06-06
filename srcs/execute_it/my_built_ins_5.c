/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:58:38 by kslik             #+#    #+#             */
/*   Updated: 2023/06/06 15:00:30 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_cd(t_tree *tree, t_my_env **env, int *exit_code)
{
	redirect_it(tree, DONT_REDIRECT);
	if (!tree->cmd_node->args[1])
		return ;
	if (chdir(tree->cmd_node->args[1]))
	{
		write(2, "our@shell: cd: ", 15);
		perror(tree->cmd_node->args[1]);
		*exit_code = 1;
		return ;
	}
	update_envs(env);
	*exit_code = 0;
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
