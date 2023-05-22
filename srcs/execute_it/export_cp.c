/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:35:07 by kslik             #+#    #+#             */
/*   Updated: 2023/05/22 10:53:38 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

char	*get_new_var(char *s, int equal_index)
{
	char	*new_var_with_declare;
	int		i;
	int		new_i;

	new_var_with_declare = ft_calloc(ft_strlen(s) + 3, sizeof(char));
	i = -1;
	new_i = 0;
	while (s[++i])
	{
		if (i == equal_index)
		{
			new_var_with_declare[new_i] = s[i];
			new_i++;
			new_var_with_declare[new_i] = '\"';
		}
		else
			new_var_with_declare[new_i] = s[i];
		new_i++;
	}
	if (equal_index != -1)
		new_var_with_declare[new_i] = '\"';
	return (new_var_with_declare);
}
char	**exp_no_opt(char **env)
{
	int		before_equal_index;
	int		i;
	char	**new_env;

	new_env = ft_calloc(100, sizeof(char *));
	i = -1;
	before_equal_index = 0;
	while (env[++i])
	{
		before_equal_index = get_before_equal_index(env[i]);
		// printf("env : %s | index : %d | char : %c\n", env[i],
				before_equal_index, env[i][before_equal_index];
		new_env[i] = get_new_var(env[i], before_equal_index);
	}
	// printf("%s\n", new_env[0]);
	// printf("%s\n", new_env[1]);
	return (new_env);
}
