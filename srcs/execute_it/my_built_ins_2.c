/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:56:16 by kslik             #+#    #+#             */
/*   Updated: 2023/06/07 13:51:54 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_or_add_my_env_node(t_my_env **my_env, char *ljadid)
{
	t_my_env		*tmp;
	struct s_export	info;

	initialize_dt(&info);
	tmp = *my_env;
	update_node(tmp, ljadid, &info);
	if (info.k == 200)
		return ;
	new_node(my_env, ljadid);
}

int	ex_err(char *cmd, int c)
{
	int	i;

	i = 0;
	if (cmd[0] == '=' || cmd[0] == '$')
	{
		if (c == 2)
			ft_putstr_fd("our@shell: export: not a valid identifier\n", 2);
		return (0);
	}
	if (!((cmd[0] >= 97 && cmd[0] <= 122) || (cmd[0] >= 65 && cmd[0] <= 90)))
	{
		if (c == 2)
			ft_putstr_fd("our@shell: export: not a valid identifier\n", 2);
		return (0);
	}
	return (1);
}

int	unset_err(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '=' || cmd[0] == '$')
	{
		ft_putstr_fd("our@shell: unset: not a valid identifier\n", 2);
		return (0);
	}
	if (!((cmd[0] >= 97 && cmd[0] <= 122) || (cmd[0] >= 65 && cmd[0] <= 90)))
	{
		ft_putstr_fd("our@shell: unset: not a valid identifier\n", 2);
		return (0);
	}
	while (cmd[i] != '\0')
	{
		if (ft_isalpha(cmd[i]) == 1 || ft_isdigit(cmd[i]) == 1)
			printf("");
		else
		{
			printf("our@shell: unset \'%s\' : not a valid identifier\n", cmd);
			return (0);
		}
		i++;
	}
	return (1);
}

void	exp_nocmd(t_my_env **my_env)
{
	char	**en_tmp;
	int		i;

	i = -1;
	en_tmp = my_env_to_array(my_env);
	en_tmp = exp_no_opt(en_tmp);
	while (en_tmp[++i])
		printf("%s\n", en_tmp[i]);
	free_arr(en_tmp);
}

//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|
void	my_export(t_tree *tree, t_my_env **my_env, unsigned char *exit_code)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	*exit_code = 0;
	if (tree->cmd_node->args[1] == NULL)
		exp_nocmd(my_env);
	else
	{
		while (tree->cmd_node->args[c] != NULL)
			c++;
		i = 0;
		while (tree->cmd_node->args[++i] != NULL)
		{
			if (ex_err(tree->cmd_node->args[i], c) == 1)
				update_or_add_my_env_node(my_env, tree->cmd_node->args[i]);
			else
				*exit_code = 1;
		}
	}
}
