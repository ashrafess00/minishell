/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envs3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:22:03 by aessaoud          #+#    #+#             */
/*   Updated: 2023/06/09 15:55:47 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl(char **env)
{
	int	i;
	int	new_shlvl;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "SHLVL", 5) && env[i][5] == '=')
		{
			new_shlvl = ft_atoi((env[i] + 6)) + 1;
			env[i] = ft_strjoin(ft_strdup("SHLVL="), ft_itoa(new_shlvl));
		}
	}
}
