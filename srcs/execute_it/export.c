/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:35:07 by kslik             #+#    #+#             */
/*   Updated: 2023/05/23 22:12:57 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_before_equal_index(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			return (i);
	}
	return (-1);
}

char	*get_new_var(char *s)
{
	char	*new_var_with_declare;
	int		i;
	int		new_i;
	int		first_equal;

	new_var_with_declare = ft_calloc(ft_strlen(s) + 3, sizeof(char));
	i = -1;
	new_i = 0;
	first_equal = 0;
	while (s[++i])
	{
		if (s[i] == '=' && !first_equal)
		{
			new_var_with_declare[new_i++] = s[i];
			new_var_with_declare[new_i++] = '\"';
			first_equal = 1;
		}
		else
			new_var_with_declare[new_i++] = s[i];
	}
	if (first_equal)
		new_var_with_declare[new_i] = '\"';
	new_var_with_declare = ft_strjoin(ft_strdup("declare -x "), \
	new_var_with_declare);
	return (new_var_with_declare);
}

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**exp_no_opt(char **env)
{
	int		i;
	char	**new_env;

	new_env = ft_calloc(env_len(env) + 1, sizeof(char *));
	i = -1;
	while (env[++i])
		new_env[i] = get_new_var(env[i]);
	free(env);
	return (new_env);
}
