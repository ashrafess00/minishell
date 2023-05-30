/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:02:45 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/30 16:53:37 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_my_env	*cr_my_env(char *env)
{
	t_my_env	*my_env;

	my_env = malloc(sizeof(t_my_env));
	my_env->val = ft_strdup(env);
	my_env->next = NULL;
	return (my_env);
}

void	add_my_env_node(t_my_env **head, char *env)
{
	t_my_env	*tmp;

	if (!(*head))
		(*head) = cr_my_env(env);
	else
	{
		tmp = (*head);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cr_my_env(env);
	}
}

void	copy_env(t_my_env **head, char **env)
{
	int			i;

	i = -1;
	while (env[++i])
		add_my_env_node(head, env[i]);
}

char	**from_lk_to_arr(t_my_env **my_env)
{
	char		**env;
	t_my_env	*current;

	current = (*my_env);
	env = NULL;
	while (current)
	{
		env = expand_arr(env, current->val);
		current = current->next;
	}
	return (env);
}

void	print_envs(t_my_env *my_env)
{
	while (my_env)
	{
		printf("%s\n", my_env->val);
		my_env = my_env->next;
	}
}
