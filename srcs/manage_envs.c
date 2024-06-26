/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:02:45 by aessaoud          #+#    #+#             */
/*   Updated: 2023/06/08 16:03:49 by aessaoud         ###   ########.fr       */
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
