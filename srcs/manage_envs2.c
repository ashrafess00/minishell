/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:29:12 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/30 17:13:24 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_pwd(void)
{
	char	s[100];
	char	*new_pwd;

	getcwd(s, sizeof(s));
	new_pwd = ft_strjoin(ft_strdup("PWD="), ft_strdup(s));
	return (new_pwd);
}

char	*get_old_pwd(char *old_env)
{
	char	*new_old_pwd;

	new_old_pwd = ft_strjoin(ft_strdup("OLDPWD="), old_env);
	return (new_old_pwd);
}

void	change_new_pwd(t_my_env **my_env, char **old_env)
{
	t_my_env	*tmp;

	tmp = *(my_env);
	while (tmp)
	{
		if (!ft_strncmp(tmp->val, "PWD", 3))
		{
			*old_env = ft_substr(tmp->val, 4, ft_strlen(tmp->val));
			tmp->val = get_new_pwd();
			return ;
		}
		tmp = tmp->next;
	}
}

void	change_old_pwd(t_my_env **my_env, char *old_env)
{
	t_my_env	*tmp;

	tmp = *(my_env);
	while (tmp)
	{
		if (!ft_strncmp(tmp->val, "OLDPWD", 6) && old_env)
		{
			free(tmp->val);
			tmp->val = get_old_pwd(old_env);
			return ;
		}
		tmp = tmp->next;
	}
}

void	update_envs(t_my_env **my_env)
{
	char	*old_env;

	old_env = NULL;
	change_new_pwd(my_env, &old_env);
	change_old_pwd(my_env, old_env);
}
