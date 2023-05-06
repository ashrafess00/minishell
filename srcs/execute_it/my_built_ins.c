/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:48:02 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/06 15:02:21 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	my_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->args[1])
		return ;
	if (!ft_strcmp(cmd->args[1], "-n"))
		i = 1;
	while (cmd->args[++i])
	{
		if (cmd->args[i + 1])
			printf("%s ", cmd->args[i]);
		else
			printf("%s", cmd->args[i]);
	}
	if (ft_strcmp(cmd->args[1], "-n"))
		printf("\n");
}

void	my_cd(t_tree *tree)
{
	chdir(tree->cmd_node->args[1]);
}