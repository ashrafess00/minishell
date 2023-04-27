/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:33:18 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/27 19:19:16 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*search_for_path(char **env, char *command)
{
	char *path_demo = ft_strdup("/usr/bin/sort");
	return (path_demo);
}

char	**get_path_from_env(char **env)
{
	char	**paths;
	int		i;

	paths = NULL;
	i = -1;
	if (!*env)
	{
		paths = ft_split(ft_strdup("/usr/bin:/bin:/usr/\
		sbin:/sbin:/usr/local/bin"), ':');
		if (!paths)
			return (0);
		return (paths);
	}
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			paths = ft_split(ft_strdup(env[i]), ':');
			if (paths)
				paths[0] = ft_strtrim(paths[0], "PATH=");
			break ;
		}
	}
	return (paths);
}

void	lets_execute(t_tree *tree, char **env)
{
	char	*path;
	char	**paths;

	if (tree->type == PIPE_NODE)
	{
		lets_execute(tree->left, env);
		lets_execute(tree->right, env);
	}
	else
	{
		int f = fork();
		if (f == 0)
		{
			paths = get_path_from_env(env);
			path = get_path(tree->cmd_node->args[0], paths);
			execve(path, tree->cmd_node->args, env);
		}
		else
			wait(NULL);
	}
}