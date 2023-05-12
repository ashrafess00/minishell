/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:02:45 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/12 10:49:39 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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


char	**our_real(char **arr, char *val)
{
	int i;

	i = 0;
	if (!arr)
	{
		arr = ft_calloc(2, sizeof(char *));
		arr[0] = ft_strdup(val);
	}
	while(arr[i])
		i++;
	i += 2;
	char **new = malloc(i * sizeof(char *));
	i = 0;
	while(arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = ft_strdup(val);
	i++;
	new[i] = NULL;
	return(new);
	
}

char	**from_lk_to_arr(t_my_env **my_env)
{
	char		**env;
	t_my_env	*current;

	current = (*my_env);
	env = NULL;
	while (current)
	{
		env = our_real(env, current->val);
		current = current->next;
	}
	return (env);
}